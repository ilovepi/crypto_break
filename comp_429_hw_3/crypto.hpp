#ifndef _CRYTO_HPP_
#define _CRYTO_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <fstream>
//#include <future>
#include <array>
#include <unordered_map>
//#include <set>
//#include <mutex>


class crypto
{
	typedef std::pair<int, std::string> score;
	typedef std::vector<score> scores;

private:
	/*
#pragma region List
	 const static std::vector<std::string> lst = { "the",
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
		"what",
		"so",
		"up",
		"out",
		"if",
		"about",
		"who",
		"get",
		"which",
		"go",
		"me",
		"when",
		"make",
		"can",
		"like",
		"time",
		"no",
		"just",
		"him",
		"know",
		"take",
		"people",
		"into",
		"year",
		"your",
		"good",
		"some",
		"could",
		"them",
		"see",
		"other",
		"than",
		"then",
		"now",
		"look",
		"only",
		"come",
		"its",
		"over",
		"think",
		"also",
		"back",
		"after",
		"use",
		"two",
		"how",
		"our",
		"work",
		"first",
		"well",
		"way",
		"even",
		"new",
		"want",
		"because",
		"any",
		"these",
		"give",
		"day",
		"most",
		"us",
		"hello",
		"world" };
#pragma endregion List

*/

	
	std::string top_alpha;// = "etaoinshr"; //{{ 'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r' } };
	std::unordered_map<std::string, size_t> hash, dict;
	
	
	
	
	static std::string str_inc(const std::string& input, int i);
	static std::vector<int> prime_factors(int n);
	//static std::vector<std::future<bool>> make_vec(std::vector<std::string> vec, std::string str);
	static scores top(scores &sub, scores &whole, size_t n);
	bool check_tops(const std::vector<int> &freqs);
	int get_scores(const std::string& str);
	int get_scores(const std::string& str, size_t n);





public:
	crypto();
	static std::vector<std::string> shift(const std::string& str);
	static std::vector<int> get_freq(const std::string& str);
	void transpose(const std::string& str);
	static scores freq_list(const std::string& s);
	std::vector<std::string> remapper(const std::string& str);

};





#endif