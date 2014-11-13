#include "crypto.hpp";



//#include<sstream>


crypto::crypto() 
{
	
}

std::string crypto::str_inc(const std::string& input, int i)
{
	auto increment = [i](char c){return (char)('a' + ((c - 'A' + i) % 26)); };

	std::string str;
	std::transform(input.begin(), input.end(), std::back_inserter(str), increment);
	//std::cout << str << std::endl;
	return str;
}

std::vector<std::string> crypto::shift(std::string str)
{
	auto increment = [](char c, int i){return (char)('a' + ((c - 'A' + i) % 26)); };
	std::vector<std::string> str_vec;
	for (int i = 0; i < 26; ++i)
	{
		//if (std::string::npos == vowel.find(increment('V', i)))
		//continue;
		str_vec.push_back(str_inc(str, i));
	}
	return str_vec;
}


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


std::vector<std::future<bool>> crypto::make_vec(std::vector<std::string> vec, std::string str)
{
	//std::function<std::atomic<bool(std::string, std::string)>> f

	auto f = [](std::string str1, std::string str2){ return (std::string::npos != str2.find(str1)); };
	std::vector<std::future<bool>> futs;
	futs.reserve(vec.size());
	for (auto word : vec)
		futs.push_back(std::async(std::launch::async, std::bind(f, word, str)));
	/*
	for (auto f = futs.begin(); f != futs.end(); ++f)
	f->get();
	*/
	return futs;
}

crypto::scores crypto::top(scores &sub, scores &whole, size_t n)
{
	auto ret = &whole;
	auto comp = [](const score &x, const score &y){return x.first > y.first; };
	int i = 0;
	if (whole.size() < n)
	{
		while (whole.size() < n && i < sub.size())
			whole.push_back(sub[i++]);
	}
	else
	{
		auto x = whole;
		for (int i = 0, j = 0, k = 0; i < n; i++)
		{
			x[i] = comp(whole[j], sub[k]) ? whole[j++] : sub[k++];
		}
		ret = &x;
	}
	std::sort(ret->begin(), ret->end(), comp);
	return *ret;
}


std::vector<int> crypto::get_freq(std::string str)
{
	std::vector<int> freq(26, 0);
	for (int i = 0; i < str.size(); ++i)
		++freq[str[i] - 'a'];
	return freq;
}

bool crypto::check_tops(std::vector<int> freqs)
{
	auto m = std::max_element(freqs.begin(), freqs.end());
	for (char c : top_alpha)
	{
		if ((*m) == (c - 'a'))
			return true;
	}
	return false;
}

void crypto::transpose(std::string str)
{
	static int count = 0;
	auto freqs = get_freq(str);
	if (!check_tops(freqs))
		return;


	std::ofstream file("perms.txt", std::ofstream::app);
	int size = str.size();
	auto factors = prime_factors(size);
	std::vector<std::pair<int, std::string>> ord, writer;
	for (auto rows : factors)
	{
		std::vector<int> indexes;
		for (int i = 0; i < size / rows; ++i)
			indexes.push_back(i);

		std::vector<std::string> pqr(size / rows), perms;
		for (int i = 0; i < size / rows; ++i)
		{
			for (int i = 0; i < pqr.size(); ++i)
				pqr[i] += str[i + rows];
		}




		while (std::next_permutation(indexes.begin(), indexes.end()))
		{
			//auto p = column_switch(pqr, indexes);
			std::string word;
			for (int i = 0; i < indexes.size(); ++i)
				word += pqr[i];

			auto hits = 0;
			auto x = make_vec(lst, word);

			for (auto it = x.begin(); it != x.end(); ++it)
			{
				bool go = false;
				if (it->get())
				{
					go = true;
					++hits;
				}//end if

				if (go)
					ord.emplace_back(hits, word);
			}//end for

		} // end while	
		std::sort(ord.begin(), ord.end(), [](const std::pair<int, std::string> &x, const std::pair<int, std::string> &y){return x.first > y.first; });
		writer = top(ord, writer, 1000);
	}
	for (auto pair : writer)
		file << pair.second << std::endl;
	file.close();
	++count;
	printf("Finished %d \n", count);
}

/*
std::vector<std::string> maper(std::string s)
{
auto freqs = get_freq(s);
std::max_element(freqs.begin(), freqs.end());
for (char c : top_alpha)
{

}
}
*/

crypto::scores crypto::freq_list(std::string s)
{
	auto comp = [](score x, score y){return x.first > y.first; };
	scores freq;
	char c = 'a';
	for (int i = 0; i < 26; ++i, ++c)
		freq.emplace_back(c, 0);
	for (int i = 0; i < s.size(); ++i)
		++freq[s[i] - 'a'].first;
	std::sort(freq.begin(), freq.end(), comp);
	return freq;
}


std::vector<std::string> crypto::remapper(std::string str)
{

	auto freqs = freq_list(str);
	std::vector<std::string> words;
	std::string temp;
	while (std::next_permutation(top_alpha.begin(), top_alpha.end()))
	{
		/*
		for (char c : top_alpha)
		std::cout << c;
		std::cout << std::endl <<std::endl;
		*/
		temp = str;
		for (int i = 0; i < top_alpha.size(); ++i)
		{
			for (int j = 0; j < str.size(); ++j)
			{
				if (freqs[i].first == str[j])
					temp[j] = top_alpha[i];
			}
		}
		words.push_back(temp);
	}
	return words;
}



size_t crypto::get_scores(const char* str, size_t n)
{


}



size_t crypto::get_scores(const std::string& str)
{
	return get_scores(str.c_str, str.size());
}
