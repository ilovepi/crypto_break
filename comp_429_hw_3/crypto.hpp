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
#include <assert.h>
#include "utility.hpp"

class crypto
{
public:
	//typedefs for convenience
	typedef std::map<std::string, int> scores;
	typedef std::pair<std::string, int> map_key;

	/**
	* basic constructor. Reads in an english dictionary from 'dictionary.txt' to dict
	*/
	crypto();


	/**
	*  Basic destructor. It useed to write out to file, now does nothing (no dynamic memory to clean up.)
	*/
	~crypto();

	/**
	* shift cipher
	* @return a vector with all possible shift ciphers of the input string (onlly 26)
	*/
	static std::vector<std::string> shift(const std::string& str);


	/**
	* @return the frequency distriubution of characters in the string
	* @param str the string to analy the frequency distribution on
	*/
	static std::vector<int> get_freq(const std::string& str);

	/**
	* @return the list of the times a characters appears in strign s
	* @param s a string to check the frequency distribution of characters 
	*/
	static scores freq_list(const std::string& s);

	/**
	* scores a string on how well it superficially matches english based on the number and length of dictionary words
	* @return an integer score based on the number and length of english words in a string
	* @param str a string to check the score of
	*/
	int get_scores(const std::string& str);
	
	/**
	* merges the maximum element from other into ret, and removes the element from other
	* @param ret the list to be merged into
	* @param other a heap containing the data to be merged
	*/
	static void merge(scores &ret, std::vector<map_key> &other);

	/**
	* uses a key attack to try and decrypt a cipher text with columnar transposition
	* @return none
	* @param cipher the cipher text as a string
	*/
	void columnar_decryption(std::string cipher);


	/**
	* a basic comparitor for score. compares the integer portion of 2 std::pair<int std::string>
	* @return true if x.second < y.second
	*/
	static bool comp_map_key(map_key x, map_key y);
	
private:

    /**
    * Holds a string of the most frequent letters in the alphabet, "etaoinshr"
    */
	std::string top_alpha;
   
    /**
    * A dictionary of english words read in from file in the constructor
    */
    std::unordered_map<std::string, size_t> dict;
		
	/**
	* increments a character (only works with lower case)
	* @return a character incremented by 1 and moded by 26: 'a'+1 = b; 'z'+1 = 'a'
	*/
	static char incr(char c);

	/**
	* increments all the letters in a string by 1  and then mod 26: 'a' +1 = 'b', 'z' +1 = 'a'
	* @param input the string to increment
	* @return the 
	*/
	static std::string str_inc(const std::string& input);
    
    /**
    * takes 2  sorted lists of scores and merges them into a new list with a maximum size
    * @return a vector of the top scores, a new master list
	* @param sub the sub list you wish to get items from
	* @param whole the previous master_list list you'd like to put items into
	* @param n the maximum size of the master list.
    */
	static scores top(scores &sub, scores &whole, size_t n);

	/**
	* scores a string on how well it superficially matches english based on the number and length of dictionary words
	* @returns an integer score based on the number and length of english words in a string
	* @param str the string to try and match
	* @param n the index of the starting position in the string to begin scoring
	*/
	int get_scores(const std::string& str, std::map<std::string, size_t> &memo, size_t n);

};

#endif