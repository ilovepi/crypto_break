#include "crypto.hpp"



int main()
{
	std::ofstream f("perms.txt");
	f.close();
	crypto solver;

	std::string   msg = "DRPWPWXHDRDKDUBKIHQVQRIKPGWOVOESWPKPVOBBDVVVDXSURWRLUEBKOLVHIHBKHLHBLNDQRFLOQ";/**/
	
	std::transform(msg.begin(), msg.end(), msg.begin(), ::tolower);
	
	auto shifted = crypto::shift(msg);	
	
	//I checked the frequency distributions earlier and picked out the best to try first
	//If that failed I would just let all 26 run
	solver.columnar_decryption(shifted[22]);

	/*for (auto it = shifted.begin(); it != shifted.end(); ++it)	// as back up try all the shifts	
		solver.columnar_decryption(*it);
	/**/
		
	//system("pause");
	return EXIT_SUCCESS;
}
