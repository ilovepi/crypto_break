#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <fstream>
#include <future>

//#include<sstream>

std::vector<std::string> lst = { "the", 
								"be", 
								"to", 
								"of", 
								"and", 								 
								"in", 
								"that", 
								"have", 								
								"it", 
								"for", 
								"not", 
								"on", 
								"with", 
								"he", 
								"as", 
								"you", 
								"do", 
								"at",
								"this",
								"but",
								"his",
								"by",
								"from",
								"they",
								"we",
								"say",
								"her",
								"she",
								"or",
								"an",
								"will",
								"my",
								"one",
								"all",
								"would",
								"there",
								"their",
								"what" };

std::string str_inc(const std::string& input, int i)
{
	auto increment = [i](char c){return (char)('a' + ((c - 'A' + i) % 26)); };
	
	std::string str;
	std::transform(input.begin(), input.end(), std::back_inserter(str), increment);
	//std::cout << str << std::endl;
	return str;
}
std::vector<std::string> shift(std::string str)
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


std::vector<int> prime_factors(int n)
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

std::string column_switch(std::vector<std::string> words, std::vector<int> indexes)
{
	std::string str;
	for (auto idx : indexes)
		for (auto i = 0; i < words.size(); ++i)
			str.push_back(words[i][idx]);
	return str;
}



std::vector<std::future<std::atomic<bool>>> make_vec(std::vector<std::string> vec, std::string str, std::function<std::atomic<bool(std::string, std::string)>> f)
{	

	std::vector<std::future<std::atomic<bool>>> futs;
	futs.reserve(vec.size());
	for (auto word : vec)	
		futs.push_back( std::async(std::launch::async, std::bind(f, word, str)));

	for (auto f = futs.begin(); f != futs.end(); ++f)
		f->get();
	
	
	return futs;
}




void transpose(std::string str)
{
	std::ofstream file("perms.txt", std::ofstream::ate);
	auto size = str.size();	
	auto factors = prime_factors(size);
	for (auto rows : factors)
	{
		std::vector<int> indexes;
		for (int i = 0; i < size / rows; ++i)		
			indexes.push_back(i);
		
		std::vector<std::string> words(rows), perms;
		int j;
		for (int i = 0; i < size; ++i)
		{
			j = i % rows;
			words[j].push_back(str[i]);
		}

		while (std::next_permutation(indexes.begin(), indexes.end()))
		{
			auto p = column_switch(words, indexes);
			
			//auto checker = ;
			/*
			auto sync = [](std::string str){
				for (auto word : lst)
					auto h = std::async(std::launch::async, [str, word](){
						return (std::string::npos != str.find(word));
				});

			};
			*/

			for (auto word : lst)
			{
				if (std::string::npos != p.find(word))
				{
					file << p << std::endl;;
					break;
				}
			}
		}			
	}
	file.close();	
}




int main()
{
	std::ofstream f("perms.txt");
	f.close();

	std::string   msg = "DRPWPWXHDRDKDUBKIHQVQRIKPGWOVOESWPKPVOBBDVVVDXSURWRLUEBKOLVHIHBKHLHBLNDQRFLOQ";
	auto shifted = shift(msg);	
		
	/*
	for (auto s : shifted)
	{
		transpose(s);		
	}
	*/
	transpose(shifted[0]);
	return EXIT_SUCCESS;
}

/*for (auto rows = 1; rows < size; ++rows)
	{
		std::vector<std::string> words(rows);
		int j;
		for (int i = 0; i < size; ++i)
		{
			j = i % rows;
			words[j].push_back(str[i]);
		}
		
		for (auto s : words)
			str_vec[rows-1] += s;
	}
	*/

/*
std::string s;
s.reserve(str.size());
int k = 0;
int index = 0;
bool even = false;
//auto m = rows % size;
for (auto j = 0; j < size; j++)
{
s.push_back(str[k]);
if (!even && ((k + rows) >= size) && (size % (k + rows) == 0))
even = true;
k = (k + rows) % size;
if (even && k == index)
{
k++;
index++;
}
}
str_vec[rows] = s;
*/