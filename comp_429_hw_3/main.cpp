#include "crypto.hpp"

int main()
{
	std::ofstream f("perms.txt");
	f.close();
	crypto solver;
	std::string   msg = "DRPWPWXHDRDKDUBKIHQVQRIKPGWOVOESWPKPVOBBDVVVDXSURWRLUEBKOLVHIHBKHLHBLNDQRFLOQ";/**/
		
	std::transform(msg.begin(), msg.end(), msg.begin(), ::tolower);
	auto mapped = solver.remapper(msg);
	
	//system("pause");

	//auto shifted = crypto::shift(msg);	

	for (auto it = mapped.begin(); it != mapped.end(); ++it)
		solver.transpose(msg);
		//for (auto it = shifted.begin(); it != shifted.end(); ++it)
		//solver.get_scores((*it));

	system("pause");
	return EXIT_SUCCESS;
}
