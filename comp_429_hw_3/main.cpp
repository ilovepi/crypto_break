#include "crypto.hpp"







int main()
{
	std::ofstream f("perms.txt");
	f.close();
	
	std::string   msg = /*"GDKKNVNQKC"*/ "DRPWPWXHDRDKDUBKIHQVQRIKPGWOVOESWPKPVOBBDVVVDXSURWRLUEBKOLVHIHBKHLHBLNDQRFLOQ";/**/
		
	std::transform(msg.begin(), msg.end(), msg.begin(), ::tolower);
	auto comp = [](std::pair<char, int> x, std::pair<char, int> y){return x.second > y.second; };
	
	/*
	auto fl = freq_list(msg);
	std::sort(fl.begin(), fl.end(), comp);
	for (auto item : fl)
		std::cout << item.first << " " << item.second << std::endl;
		*/
	auto mapped = remapper(msg);
	

	//system("pause");

	//auto shifted = shift(msg);	
	for (auto s : mapped)
	{
		/*
		if (s == "helloworld")
		{
			std::cout << "Success!!!!" << std::endl;
			system("pause");
		}
		else
			std::cout << s << std::endl;
		*/
		transpose(s);		
	}
	
	//transpose(shifted[0]);
	system("pause");
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