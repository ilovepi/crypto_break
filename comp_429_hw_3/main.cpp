#include "crypto.hpp"

int main()
{
	std::ofstream f("perms.txt");
	f.close();
	crypto solver;

	std::string   msg = "DRPWPWXHDRDKDUBKIHQVQRIKPGWOVOESWPKPVOBBDVVVDXSURWRLUEBKOLVHIHBKHLHBLNDQRFLOQ";/**/
	
	std::transform(msg.begin(), msg.end(), msg.begin(), ::tolower);

	//solver.transpose(msg);
	//auto mapped = solver.remapper(msg);
	
	//system("pause");

	auto shifted = crypto::shift(msg);	

	solver.transpose(shifted[22]);
	
	
	/*for (auto it = shifted.begin(); it != shifted.end(); ++it)		
		solver.transpose(*it);
	/**/
	
	
	//system("pause");
	return EXIT_SUCCESS;
}
