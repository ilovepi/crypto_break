#ifndef _CRYTO_HPP_
#define _CRYTO_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <map>
#include "utility.hpp"

class crypto
{
public:
	typedef std::pair<int, std::string> score;
	typedef std::map<std::string, int> scores;
	typedef std::pair<std::string, int> map_key;

private:

    /**
    * Holds a string of the most frequent letters in the alphabet
    */
	std::string top_alpha;// = "etaoinshr"; //{{ 'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r' } };

   
    /**
    * A dictionary of english words
    */
    std::unordered_map<std::string, size_t> dict;

	
	/**
	*increments a character
	*/
	static char incr(char c);

	/**
	* increments all the letters in a string by 1: 'a' +1 = 'b', 'z' +1 = 'a'
	*/
	static std::string str_inc(const std::string& input);
    
    /**
    * takes 2  sorted lists of scores and merges them into a new list with a maximum size
    * @return a vector of the top scores
    */
	static scores top(scores &sub, scores &whole, size_t n);


   

public:
    /**
    * basic constructor
    */
	crypto();

	
	/**
	 *  Basic destructor. useed to write out to file, now does nothing (no dynamic memory to clean up.
	 */
	~crypto();
	
    /**
    * shift cipher 
    * returns a vector with all possible shift ciphers of the input string (onlly 26)
    */
	static std::vector<std::string> shift(const std::string& str);


    /**
    * returns the frequency distriubution of characters in the string
    */
	static std::vector<int> get_freq(const std::string& str);
	   
    /**
    * returns the frequency list for s
    */
	static scores freq_list(const std::string& s);
    	
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
	int get_scores(const std::string& str, std::map<std::string, size_t> &memo, size_t n);

	
	
	/**
	merges 2 sorted lists into a single list of some maximum size
	*/
	static void merge(scores &ret, std::vector<map_key> &other);

	/**
	*uses a key attack to try and decrypt a cipher text with columnar transposition
	*@return none
	*@param cipher the cipher text as a string
	*/
	void columnar_decryption(std::string cipher);

	/**
	* a basic comparitor for score. compares the integer portion of 2 std::pair<int std::string>
	*/
	static bool comp(const score &x, const score &y);

	/**
	* a basic comparitor for score. compares the integer portion of 2 std::pair<int std::string>
	*/
	static bool comp2(map_key x, map_key y);

};

#endif