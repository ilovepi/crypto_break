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
#include <map>
//#include <mutex>


class crypto
{
	typedef std::pair<int, std::string> score;
	typedef std::vector<score> scores;
	typedef std::pair<std::string, int> map_key;

private:

    /**
    * Holds a string of the most frequent letters in the alphabet
    */
	std::string top_alpha;// = "etaoinshr"; //{{ 'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r' } };

    /**
    * A hash used for memoization of strings and their scores... could be better
    */
	std::map<std::string, size_t> memo;

    /**
    * A dictionary of english words
    */
    std::unordered_map<std::string, size_t> dict;

    /**
    * increments all the letters in a string by i: 'a' +1 = 'b'
    */
	static std::string str_inc(const std::string& input, int i);


    /**
    * @return a vector of the first 2 factors of an integer
    */
	static std::vector<int> prime_factors(int n);

    /**
    * parallely makes a vector acording to some rules
    */
	//static std::vector<std::future<bool>> make_vec(std::vector<std::string> vec, std::string str);

    /**
    * takes 2 lists of scores and merges them into a new list with a maximum size
    * @return a vector of the top scores
    */
	static scores top(scores &sub, scores &whole, size_t n);

    /**
    * checks if the top letter frequencies in a cypher text  match english
    */
	bool check_tops(const std::vector<int> &freqs);

    


    /**
    * a basic comparitor for score. compares the integer portion of 2 std::pair<int std::string>
    */
    static bool comp(const score &x, const score &y);


public:
    /**
    * basic constructor
    */
	crypto();

	~crypto();


    /**
    * ceasar cypher shift
    * returns a vector with all possible caesar cyphers of the input string
    */
	static std::vector<std::string> shift(const std::string& str);


    /**
    * returns the frequency distriubution of characters in the string
    */
	static std::vector<int> get_freq(const std::string& str);

    /**
    * tries to use columnar transposition to  decrypt str. Writes to a file all the most plausible decryptions    *
    */
	void transpose(const std::string& str);

    /**
    * returns the frequency list for s
    */
	static scores freq_list(const std::string& s);

    /**
    * substitution
    */
	std::vector<std::string> remapper(const std::string& str);

	void insert_hash(const map_key& item);

	/**
	* scores a string on how well it superficially matches english based on the number and length of dictionary words
	* @returns an integer score based on the number and length of english words in a string
	*/
	int get_scores(const std::string& str);



	/**
	* scores a string on how well it superficially matches english based on the number and length of dictionary words
	* @returns an integer score based on the number and length of english words in a string
	* @param str the string to try and match
	* @param n the index of the starting position in the string to begin scoring
	*/
	int get_scores(const std::string& str, size_t n);

};

#endif