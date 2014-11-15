#include "crypto.hpp"

int main()
{
	std::ofstream f("perms.txt");
	f.close();
	crypto solver;
	std::string   msg = "GDKKNVNQKC";// "DRPWPWXHDRDKDUBKIHQVQRIKPGWOVOESWPKPVOBBDVVVDXSURWRLUEBKOLVHIHBKHLHBLNDQRFLOQ";/**/
		
	std::transform(msg.begin(), msg.end(), msg.begin(), ::tolower);
	
	//auto mapped = solver.remapper(msg);
	

	//system("pause");

	//auto shifted = shift(msg);	
	//for (auto it = mapped.begin(); it != mapped.end(); ++it)
		//solver.transpose((*it));

	system("pause");
	return EXIT_SUCCESS;
}
