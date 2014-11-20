#include "crypto.hpp"

crypto::crypto() 
{
    top_alpha = "etaoinshr";
	std::ifstream infile("dictionary.txt");
	std::string word;
	while (getline(infile, word))
		dict.insert(std::make_pair(word, word.size()*word.size()));
	infile.close();

	/*infile.open("memo.txt");
	map_key key;
	while (!infile.peek() == std::ifstream::traits_type::eof())
	{
		infile >> key.first >> key.second;
		memo.insert(key);
	}
	//printf("Dictionary is %d items large\n\n", dict.size());/**/
}

crypto::~crypto()
{
	/*if (!memo.empty())
	{
		std::ofstream outfile("memo.txt");
		for (auto it = memo.begin(); it != memo.end(); ++it)
		{
			outfile << it->first << " " << it->second << std::endl;			
		}
	}/**/
}

char crypto::incr(char c)
{	return (char)('a' + ((c-'a'+1) % 26));	}

std::string crypto::str_inc(const std::string& input)
{
	std::string str;
	std::transform(input.begin(), input.end(), std::back_inserter(str), incr);	
	return str;
}

std::vector<std::string> crypto::shift(const std::string& str)
{
	std::vector<std::string> str_vec;
	auto temp = str;
	for (int i = 0; i < 26; ++i)
	{
		temp = str_inc(temp);
		str_vec.push_back(temp);
	}
		
	return str_vec;
}


bool crypto::comp(const score &x, const score &y)
{
    return x.first > y.first;
}

bool crypto::comp2(map_key x, map_key y)
{
	return  x.second < y.second;
}


void crypto::merge(scores &ret, std::vector<map_key> &other)
{
	auto it = ret.find(other.front().first);
	if (it == ret.end())
		ret.insert(other.front());
	else
		ret[other.front().first] = std::max(other.front().second, ret[other.front().first]);
	std::pop_heap(other.begin(), other.end(), comp2);
	other.pop_back();
}

crypto::scores crypto::top(scores &sub, scores &whole, size_t n)
{
	scores ret;
	std::vector<std::pair<std::string, int>> whole_que, sub_que;	
	for (auto it = whole.begin(); it != whole.end(); it++)	
		whole_que.push_back(*it);			
	std::make_heap(whole_que.begin(), whole_que.end(), comp2);

	for (auto it = sub.begin(); it != sub.end(); it++)
		sub_que.push_back(*it);
	std::make_heap(sub_que.begin(), sub_que.end(), comp2);

	while (ret.size() < n && !whole_que.empty()  && !sub_que.empty())
	{		
		if (comp2(whole_que.front(), sub_que.front()))
			merge(ret, whole_que);		
		else
			merge(ret, sub_que);		
	}

	while (ret.size() < n && !whole_que.empty())
		merge(ret, whole_que);

	while (ret.size() < n && !sub_que.empty())
		merge(ret, sub_que);

	return ret;
}


std::vector<int> crypto::get_freq(const std::string& str)
{
	std::vector<int> freq(26, 0);
	for (int i = 0; i < str.size(); ++i)
		++freq[str[i] - 'a'];
	return freq;
}



crypto::scores crypto::freq_list(const std::string &s)
{
	scores freq;
	std::string str = "a";	
	for (int i = 0; i < 26; ++i, ++str[0])
        freq.insert(std::make_pair(str,0));

	for (int i = 0; i < s.size(); ++i)
		++freq[s.substr(i,1)];	
	return freq;
}

int crypto::get_scores(const std::string& str)
{
	std::map<std::string, size_t> memo;
	return get_scores(str, memo, 0); 
}


/* This needs multi threading !!!!!*/
int crypto::get_scores(const std::string& str, std::map<std::string, size_t> &memo, size_t pos)
{
	if (pos >= str.size())
		return 0;
	int ret= 0;                             // return value
    int temp = 0;                           // temp value for calc
    int m = 1; 	                            // window size

    std::string window = str.substr(pos, m);
	//lock hash
	auto it = memo.find(str.substr(pos, str.size())); //<-- not thread safe
	bool in_hash = (it != memo.end()); //<-- not thread safe	
	if (!in_hash)  //<-- not thread safe
	{
		//unlock memo
		while (m <= (str.size() - pos))
		{			
			if (dict.find(window) != dict.end())
			{
				temp = (m*m + get_scores(str, memo, pos + m));
				if (ret < temp)
					ret = temp;
			}
			++m;
			window = str.substr(pos, m);									
		}
				
		//lock memo
		it = memo.find(str.substr(pos, str.size())); //<-- not thread safe
		if (it == memo.end() || (it->second < ret))
			memo.insert(std::make_pair(str.substr(pos, str.size()), ret));  //<-- not thread safe. need a mutex
		//unlock memo
	}
	else
	{
		ret = it->second;
		//unlock memo
	}	

	return std::max(ret, get_scores(str, memo, pos+1));
}

void crypto::columnar_decryption(std::string cipher)
{
	static int count = 0;
	std::ofstream file("perms.txt", std::ofstream::app);	
	scores ord, writer;
	for (int columns = 1; columns <= 8; columns++)
	{
		std::vector<size_t> indexes;
		for (int i = 0; i < columns; ++i)
			indexes.push_back(i);
		int rows = cipher.size() / columns;
		int extra = cipher.size() % columns;
		std::vector<std::string> pqr(indexes.size());
		while (std::next_permutation(indexes.begin(), indexes.end()))
		{
			int start = 0;
			int end;
			for (int i = 0; i < columns; ++i)
			{
				end = rows + (extra > indexes[i]);
				pqr[indexes[i]] = cipher.substr(start, end);
				start += end;
			}
			std::string word;
			for (int i = 0; i < rows + (extra > 0); ++i)
			{
				auto offset = i*columns;
				for (int j = 0; j < columns; ++j)
				{
					auto index = j + offset;
					if (index < cipher.size())
						word += pqr[j][i];
				}
			}
			auto score = get_scores(word);
			if (ord.find(word) != ord.end())
				ord[word] = std::max(ord[word], score);
			else
				ord[word] = score;
		} // end while			
		writer = top(ord, writer, 1000);		
	}
	auto ret = flip_map(writer);
	for (auto it = ret.begin(); it != ret.end(); ++it)
		file << it->first << " " << it->second << std::endl;
	file.close();
	++count;
	printf("Finished %d \n", count);
}

