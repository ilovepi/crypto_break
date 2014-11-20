#include "crypto.hpp"



int main()
{
	std::ofstream f("perms.txt");
	f.close();
	crypto solver;

	std::string   msg = "LWLHLODEOR";//"DRPWPWXHDRDKDUBKIHQVQRIKPGWOVOESWPKPVOBBDVVVDXSURWRLUEBKOLVHIHBKHLHBLNDQRFLOQ";/**/
	// 
	std::transform(msg.begin(), msg.end(), msg.begin(), ::tolower);


	/*std::pair<std::string,int> item;
	std::ifstream file("perms.txt");
	std::vector<std::pair<std::string, int>> heap;
	while (file.peek() != EOF)
	{
		file >> item.second >> item.first;
		heap.push_back(item);
	}

	for (auto it : heap)
		std::cout << it.first << " : " << it.second << std::endl;
	std::cout << std::endl;

	std::make_heap(heap.begin(), heap.end(), crypto::comp2);
	for (auto it : heap)
		std::cout << it.first << " : " << it.second << std::endl;
	std::cout << std::endl;

	std::pop_heap(heap.begin(), heap.end(), crypto::comp2);
	for (auto it : heap)
		std::cout << it.first << " : " << it.second << std::endl;
	std::cout << std::endl;
	
	

	/*
	std::vector<int> x = {5,7,2,1,9,6,3,11,22,59};
	for (auto item : x)
		std::cout << item << " ";
	std::cout << std::endl;

	std::make_heap(x.begin(), x.end());
	for (auto item : x)
		std::cout << item << " ";
	std::cout << std::endl;

	std::pop_heap(x.begin(), x.end());
	for (auto item : x)
		std::cout << item << " ";
	std::cout << std::endl;

	/**/

	

	auto shifted = crypto::shift(msg);	
	
	//solver.columnar_decryption(msg);
	solver.columnar_decryption(shifted[22]);
	/*for (auto item : shifted)
	{
		auto freqs = solver.freq_list(item);
		auto sorted = flip_map(freqs);
		bool good_dist = true; //true if freq dist is close to english (same top 9 letters-ish)
		int size = item.size();
		if (size > 30)
		{
			auto limit = 4;//std::min((int)solver.top_alpha.size(), (size - 28));
			auto it = sorted.rbegin();
			std::cout << "limit: " << limit << std::endl;
			for (int i = 0; good_dist && i < limit && it != sorted.rend(); ++i, ++it)
			{
				auto str = it->second;
				std::cout << it->second << " : " << it->first << std::endl;
				if (solver.top_alpha.find(it->second) == std::string::npos)
					good_dist = false;
			}
		}
		
		if (good_dist)
			++count;
}/**/
	
	//std::cout << count << std::endl;
	
	
	/*for (auto it = shifted.begin(); it != shifted.end(); ++it)		
		solver.columnar_decryption(*it);
	/**/
		
	//system("pause");
	return EXIT_SUCCESS;
}
