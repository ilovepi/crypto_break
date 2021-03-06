#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <map>
#include <utility>
#include <algorithm>

//from http://stackoverflow.com/questions/5056645/sorting-stdmap-using-value

template<typename A, typename B>
std::pair<B, A> flip_pair(const std::pair<A, B> &p)
{
	return std::pair<B, A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B, A> flip_map(const std::map<A, B> &src)
{
	std::multimap<B, A> dst;
	std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
		flip_pair<A, B>);
	return dst;
}

#endif // !UTILITY_HPP_
