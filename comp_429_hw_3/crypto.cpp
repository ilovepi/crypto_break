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

void crypto::insert_hash(const map_key& item)
{
	/*auto it = memo.find(item.first);
	if (it == memo.end() || it->second < item.second)
		memo.insert(item);	/**/
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
/**/

std::set<int> crypto::prime_factors(int n)
{
	std::set<int> factor;
	auto limit = sqrt(n);
	for (auto i = 2; i < limit; ++i)
	{
		if (n % i == 0)
		{
			factor.insert(i);
			factor.insert(n / i);
			
		}
	}
	if (factor.empty())	
		factor.insert(n);

	return factor;
}

/*
std::string column_switch(std::vector<std::string> words, std::vector<int> indexes)
{
std::string str;
for (auto idx : indexes)
for (auto i = 0; i < words.size(); ++i)
str.push_back(words[i][idx]);
return str;
}
*/

/*
std::vector<std::future<bool>> crypto::make_vec(std::vector<std::string> vec, std::string str)
{
	//std::function<std::atomic<bool(std::string, std::string)>> f

	auto f = [](std::string str1, std::string str2){ return (std::string::npos != str2.find(str1)); };
	std::vector<std::future<bool>> futs;
	futs.reserve(vec.size());
	for (auto word : vec)
		futs.push_back(std::async(std::launch::async, std::bind(f, word, str)));
	
	//for (auto f = futs.begin(); f != futs.end(); ++f)
	//f->get();
	
	return futs;
}
*/


bool crypto::comp(const score &x, const score &y)
{
    return x.first > y.first;
}

bool crypto::comp2(map_key x, map_key y)
{
	return  x.second > y.second;
}


void crypto::merge(scores &ret, std::vector<map_key> &other)
{
	auto it = ret.find(other.front().first);
	if (it == ret.end())
		ret.insert(other.front());
	else
		ret[other.front().first] = std::max(other.front().second, ret[other.front().first]);
	std::pop_heap(other.begin(), other.end());
	other.pop_back();
}

crypto::scores crypto::top(scores &sub, scores &whole, size_t n)
{
	scores ret;
	std::vector<std::pair<std::string, int>> whole_que, sub_que;	
	for (auto it = whole.begin(); it != whole.end(); it++)	
		whole_que.push_back(*it);			
	std::make_heap(whole_que.begin(), whole_que.end());

	for (auto it = sub.begin(); it != sub.end(); it++)
		sub_que.push_back(*it);
	std::make_heap(sub_que.begin(), sub_que.end());

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


bool crypto::check_tops(const std::vector<int>& freqs)
{
	auto m = std::max_element(freqs.begin(), freqs.end());
    char c = (*m) + 'a';
	return (top_alpha.find(c) != std::string::npos);
}


void crypto::transpose(const std::string& str)
{
	std::ofstream file("perms.txt", std::ofstream::app);
	static int count = 0;
	auto freqs = get_freq(str);
	//if (!check_tops(freqs))
		//return;

	size_t size = str.size();
	//auto factors = prime_factors(size);		
	scores ord, writer;
	//for (auto it = factors.begin(); it != factors.end(); ++it)
	for (auto rows = 1; rows < str.size(); ++rows)
	{
        //auto rows = (*it);
		std::vector<int> indexes;
		for (int i = 0; i < size / rows; ++i)
			indexes.push_back(i);
		auto columns = std::ceil((double)size / rows);
		std::vector<std::string> xyz(rows);
		for (auto i = 0; i < str.size(); ++i)
		{
			//xyz
		}

		std::vector<std::string> pqr(columns);
		for (int i = 0; i < columns; ++i)
		{
			for (int j = 0; (j < rows) && ((i + j*(columns)) < str.size()); ++j)
				pqr[i] += str[i + j*(columns)];
		}
		
		while (std::next_permutation(indexes.begin(), indexes.end()))
		{			
			std::string word;
			for (int i = 0; i < indexes.size(); ++i)
				word += pqr[indexes[i]];

			auto score = get_scores(word);
			if (ord.find(word) != ord.end())
				ord[word] = std::max(ord[word], score);
			else
				ord[word] =  score;

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

/* can we multi thread this?? maybe write it to file???*/
std::vector<std::string> crypto::remapper(const std::string& str)
{	
	std::string code = "abcdefghijklmnopqrstuvwxyz";
	scores freqs;
	std::vector<std::string> words;
	std::string temp;
	while (std::next_permutation(code.begin(), code.end()))
	{
		temp = str;
		for (int j = 0; j < str.size(); ++j)		
			temp[j] = code[temp[j] - 'a'];		
		freqs = freq_list(temp);				
		bool good_dist = true; //true if freq dist is close to english (same top 9 letters-ish)
		int size = str.size();
		if (size > 30)
		{
			auto limit = std::min((int)top_alpha.size(), (size-28));			
			auto it = freqs.begin();
			for (int i = 0; good_dist && i < limit && it != freqs.end(); ++i, ++it)
			{
				if (top_alpha.find(it->first) == std::string::npos)
					good_dist = false;
			}
		}
		/**/
		if (good_dist)
			words.push_back(temp);		
	}
	return words;
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
	for (int columns = 1; columns <= 3; columns++)
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

