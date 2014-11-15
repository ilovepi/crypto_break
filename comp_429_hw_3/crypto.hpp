#ifndef _CRYTO_HPP_
#define _CRYTO_HPP_
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <fstream>
#include <cmath>
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
	
	std::string top_alpha;// = "etaoinshr"; //{{ 'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r' } };
	std::unordered_map<std::string, size_t> hash, dict;

	//static std::string str_inc(const std::string& input, int i);
	static std::vector<int> prime_factors(int n);
	//static std::vector<std::future<bool>> make_vec(std::vector<std::string> vec, std::string str);
	static scores top(scores &sub, scores &whole, size_t n);
	bool check_tops(const std::vector<int> &freqs);
	int get_scores(const std::string& str);
	int get_scores(const std::string& str, size_t n);
    static bool comp(const score &x, const score &y);


public:
	crypto();
	//static std::vector<std::string> shift(const std::string& str);
	static std::vector<int> get_freq(const std::string& str);
	void transpose(const std::string& str);
	static scores freq_list(const std::string& s);
	std::vector<std::string> remapper(const std::string& str);

};

#endif