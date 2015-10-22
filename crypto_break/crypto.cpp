#include "crypto.hpp"

crypto::crypto() 
{
    top_alpha = "etaoinshr";
	std::ifstream infile("dictionary.txt");
	std::string word;
	while (getline(infile, word))
		dict.insert(std::make_pair(word, word.size()*word.size()));
	infile.close();
}

crypto::~crypto(){}

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


bool crypto::comp_map_key(map_key x, map_key y)
{	return  x.second < y.second;	}


void crypto::merge(scores &ret, std::vector<map_key> &other)
{
	assert(std::is_heap(other.begin(), other.end()));
	auto it = ret.find(other.front().first);// look for the top item from other in ret
	if (it == ret.end())
		ret.insert(other.front());// if its not there, add it to ret
	else//otherwise look for it in ret, and only choose the larger of the 2( shouldn't be necessary, but ...)
		ret[other.front().first] = std::max(other.front().second, ret[other.front().first]);
	std::pop_heap(other.begin(), other.end(), comp_map_key);// reduce the size of the heap
	other.pop_back();// remove the item from the vector
}

crypto::scores crypto::top(scores &sub, scores &whole, size_t n)
{
	scores ret;
	//make 2 heaps out of whole and sub
	std::vector<std::pair<std::string, int>> whole_que, sub_que;	
	for (auto it = whole.begin(); it != whole.end(); it++)	
		whole_que.push_back(*it);			
	std::make_heap(whole_que.begin(), whole_que.end(), comp_map_key);

	for (auto it = sub.begin(); it != sub.end(); it++)
		sub_que.push_back(*it);
	std::make_heap(sub_que.begin(), sub_que.end(), comp_map_key);

	// while they're both not empty and ret isn't full take the top items from each heap
	while (ret.size() < n && !whole_que.empty()  && !sub_que.empty())
	{		
		if (comp_map_key(whole_que.front(), sub_que.front()))
			merge(ret, whole_que);		
		else
			merge(ret, sub_que);		
	}

	// if sub runs out first, take the rest of the items from whole
	while (ret.size() < n && !whole_que.empty())
		merge(ret, whole_que);

	//if whole ran out, take the rest of the items from sub
	while (ret.size() < n && !sub_que.empty())
		merge(ret, sub_que);

	return ret;//return the new master list
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
	//recursive base case check
	if (pos >= str.size())
		return 0;
	int ret= 0;                             // return value
    int temp = 0;                           // temp value for calc
    int m = 1; 	                            // window size

    std::string window = str.substr(pos, m);
	// look for the current string in the memo, if its there just use its value, if not calculate it
	//lock hash
	auto it = memo.find(str.substr(pos, str.size())); //<-- not thread safe
	bool in_hash = (it != memo.end()); //<-- not thread safe	
	if (!in_hash)  //<-- not thread safe
	{
		//unlock memo
		while (m <= (str.size() - pos))
		{	
			//look up the substring in the dictionary
			if (dict.find(window) != dict.end())
			{
				//if we find them, give them a score and look at the rest of the string for more words
				temp = (m*m + get_scores(str, memo, pos + m));
				if (ret < temp)
					ret = temp;
			}
			++m;//increase the window size
			window = str.substr(pos, m);//update window to be the proper substring									
		}
		
		//insert the new score and substring pair into the memo if its not there or update it with the high score
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
	static int count = 0; //static count for printing, not really useful in general
	std::ofstream file("perms.txt", std::ofstream::app);	//open the file to append to
	scores ord, writer;								// 2 vectors of scores writer is the master list, ord is the temp list
	// attack all key lengths up to 10 (should probably avoid a magic number and make max_key_len a parameter)
	for (int columns = 1; columns <= 10; columns++)
	{
		//create a vector of the indexes based on the key length
		std::vector<size_t> indexes;
		for (int i = 0; i < columns; ++i)
			indexes.push_back(i);
		
		//number of columns for all rows(integer division is ok here)
		int rows = cipher.size() / columns;
		
		//number of columns that will be in the final row (if it exists)
		int extra = cipher.size() % columns;

		// the columns of the message
		std::vector<std::string> pqr(indexes.size());
		//decrypt the columnar transposition for each permutation of column orderings
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
			auto score = get_scores(word);// get the score for the decrypted message
			if (ord.find(word) != ord.end())
				ord[word] = std::max(ord[word], score);//only keep the max scores
			else
				ord[word] = score;//add a new score if we don't have it yet
		} // end while			
		writer = top(ord, writer, 1000);//only keep the top 1000 scores for the future		
	}
	// order the list by score instead of string so we need to use a multimap
	auto ret = flip_map(writer);
	//write the scores to a file
	for (auto it = ret.begin(); it != ret.end(); ++it)
		file << it->first << " " << it->second << std::endl;
	file.close();
	++count;
	printf("Finished %d \n", count);
}

