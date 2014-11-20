#include "crypto.hpp"



int main()
{
	std::ofstream f("perms.txt");
	f.close();
	crypto solver;

	std::string   msg = "DRPWPWXHDRDKDUBKIHQVQRIKPGWOVOESWPKPVOBBDVVVDXSURWRLUEBKOLVHIHBKHLHBLNDQRFLOQ";/**/
	//"LWLHLODEOR";// 
	std::transform(msg.begin(), msg.end(), msg.begin(), ::tolower);

	
	//solver.transpose(msg);
	//auto mapped = solver.remapper(msg);
	
	//system("pause");

	auto shifted = crypto::shift(msg);	
	
	//solver.transpose(msg);
	//solver.transpose(shifted[22]);
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
	
	
	for (auto it = shifted.begin(); it != shifted.end(); ++it)		
		solver.columnar_decryption(msg);
	/**/
		
	//system("pause");
	return EXIT_SUCCESS;
}
