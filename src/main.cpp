#include <iostream>
#include <functional> //< std::hash<>
#include <string> //< std::string
#include <utility> //< std::pair
#include "hashtbl.h"
using pair_s_i = std::pair< std::string, int >;
int main()
{
	std::string nome = "Aline Souza";
	int conta = 45794;
	std::cout << (std::hash< std::string >()( nome ) xor std::hash< int >()( conta )  ) << std::endl;
	return 0;
}