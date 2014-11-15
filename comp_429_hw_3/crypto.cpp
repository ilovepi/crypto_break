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

/*
std::string crypto::str_inc(const std::string& input, int i)
{
	auto increment = [i](char c){return (char)('a' + ((c - 'A' + i) % 26)); };

	std::string str;
	std::transform(input.begin(), input.end(), std::back_inserter(str), increment);
	//std::cout << str << std::endl;
	return str;
}
*/
/*
std::vector<std::string> crypto::shift(const std::string& str)
{
	std::vector<std::string> str_vec;
	for (int i = 0; i < 26; ++i)
		str_vec.push_back(str_inc(str, i));
	return str_vec;
}
*/

std::vector<int> crypto::prime_factors(int n)
{
	std::vector<int> factor;
	auto limit = sqrt(n);
	for (auto i = 2; i < limit; ++i)
	{
		if (n % i == 0)
		{
			factor.push_back(i);
			factor.push_back(n / i);
			return factor;
		}
	}
	factor.push_back(1);
	factor.push_back(n);
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

crypto::scores crypto::top(scores &sub, scores &whole, size_t n)
{
	auto ret = &whole;

	int i = 0;
	if (whole.size() < n)
	{
		while (whole.size() < n && i < sub.size())
			whole.push_back(sub[i++]);
	}
	else
	{
		auto x = whole;
		for (int j = 0, k = 0; i < n; i++)
		{
			x[i] = comp(whole[j], sub[k]) ? whole[j++] : sub[k++];
		}
		ret = &x;
	}
	std::sort(ret->begin(), ret->end(), comp);
	return *ret;
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
	static int count = 0;
	auto freqs = get_freq(str);
	if (!check_tops(freqs))
		return;


	std::ofstream file("perms.txt", std::ofstream::app);
	size_t size = str.size();
	auto factors = prime_factors(size);
	std::vector<std::pair<int, std::string>> ord, writer;
	for (auto it = factors.begin(); it != factors.end(); ++it)
	{
        auto rows = (*it);
		std::vector<int> indexes;
		for (int i = 0; i < size / rows; ++i)
			indexes.push_back(i);

		std::vector<std::string> pqr(size / rows);
		for (int i = 0; i < size / rows; ++i)
		{
			for (int j = 0; j < rows; ++j)
				pqr[i] += str[j + i*rows];
		}
		
		while (std::next_permutation(indexes.begin(), indexes.end()))
		{			
			std::string word;
			for (int i = 0; i < indexes.size(); ++i)
				word += pqr[i];

			auto score = get_scores(word);
			if (score > 0)
				ord.push_back(std::make_pair(score, word));

		} // end while	
		std::sort(ord.begin(), ord.end(), comp);
		writer = top(ord, writer, 1000);
	}
	for (auto it = writer.begin(); it != writer.end(); ++it)
		file << it->second << std::endl;
	file.close();
	++count;
	printf("Finished %d \n", count);
}



crypto::scores crypto::freq_list(const std::string &s)
{
	scores freq;
	std::string str = "a";
	
	for (int i = 0; i < 26; ++i, ++str[0])
        freq.push_back(std::make_pair(0, str));

	for (int i = 0; i < s.size(); ++i)
		++freq[s[i] - 'a'].first;
	std::sort(freq.begin(), freq.end(), comp);
	return freq;
}

/* can we multi thread this?? maybe write it to file???*/
std::vector<std::string> crypto::remapper(const std::string& str)
{
	//std::string alpha = "abcdefghijklmnopqrstuvwxyz";
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
		auto limit = std::min(top_alpha.size(), str.size());
		for (int i = 0; good_dist && i < limit; ++i)
		{
			if (top_alpha.find(freqs[i].second) == std::string::npos)
				good_dist = false;
		}
		if (good_dist)
			words.push_back(temp);		
	}
	return words;
}

int crypto::get_scores(const std::string& str)
{ return get_scores(str, 0); }


/* This needs multi threading !!!!!*/
int crypto::get_scores(const std::string& str, size_t pos)
{
	int ret= 0;                             // return value
    int temp = 0;                           // temp value for calc
    int m = 1; 	                            // window size

    std::string window = str.substr(pos, m);
	//lock hash
	auto it = hash.find(str.substr(pos, str.size())); //<-- not thread safe
	bool in_hash = it== hash.end(); //<-- not thread safe	
	if (!in_hash)  //<-- not thread safe
	{
		//unlock hash
		while (m < (str.size() - pos))
		{			
			if (dict.find(window) != dict.end())
			{
				temp = (m*m + get_scores(str, pos + m));
				if (ret < temp)
					ret = temp;
			}
			++m;
			window += str[pos + m];
		}
				
		//lock hash
		it = hash.find(str.substr(pos, str.size())); //<-- not thread safe
		if (it == hash.end() || (it->second < ret))
			hash.insert(std::make_pair(str.substr(pos, str.size()), ret));  //<-- not thread safe. need a mutex
		//unlock hash
	}
	else
	{
		ret = it->second;
		//unlock hash
	}	
	return ret;
}
