#include "RWArticle.h"

const char * hint = "Input format:wf.exe -c file_name\n" 
	"If the file name contains space, please use this format: Input format:wf.exe -c \"file_name\"\n";

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		std::cout << "Please excute in cmd mode!\n";
	}
	else if (argc == 2) {
		std::cout << hint;
	}
	else if (argc == 3) {
		
		
	}

	return std::cin.get();
}