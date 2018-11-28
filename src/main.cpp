#include <iostream>
#include <functional> //< std::hash<>
#include <string> //< std::string
#include <utility> //< std::pair
#include "hashtbl.h"
using pair_s_i = std::pair< std::string, int >;
int main()
{
	ac::HashTbl<int, int> h1;
	std::cout << "Tamanho? " << h1.tam()  << std::endl;
	std::cout << "Empty? " << (h1.empty()?  "Sim":"Não" ) << std::endl;
	std::cout << "Size? " << h1.size()  << std::endl;
	h1.insert(1,2);
	std::cout << "Empty? " << (h1.empty()?  "Sim":"Não" ) << std::endl;
	std::cout << "Size? " << h1.size()  << std::endl;
	h1.insert(1,2);
	std::cout << "Empty? " << (h1.empty()?  "Sim":"Não" ) << std::endl;
	std::cout << "Size? " << h1.size()  << std::endl;
	h1.insert(2,2);
	std::cout << "Empty? " << (h1.empty()?  "Sim":"Não" ) << std::endl;
	std::cout << "Size? " << h1.size()  << std::endl;
	h1.insert(15,323);
	for (int i = 0; i < h1.tam(); ++i)
	{
		std::cout << i << " -> " << h1.count(i) << std::endl;
	}
	h1.erase(15);
	std::cout << std::endl;
	for (int i = 0; i < h1.tam(); ++i)
	{
		std::cout << i << " -> " << h1.count(i) << std::endl;
	}

	h1.erase(2);
	std::cout << std::endl;
	for (int i = 0; i < h1.tam(); ++i)
	{
		std::cout << i << " -> " << h1.count(i) << std::endl;
	}

	std::cout << std::endl;
	ac::HashTbl<int, int> h2;
	std::cout << "Tamanho? " << h2.tam()  << std::endl;
	std::cout << "Empty? " << (h2.empty()?  "Sim":"Não" ) << std::endl;
	std::cout << "Size? " << h2.size()  << std::endl;
	for (int i = 0; i < 100 ; ++i)
	{
		h2.insert(i, i*i);
	}
	std::cout << "Tamanho? " << h2.tam()  << std::endl;
	std::cout << "Empty? " << (h2.empty()?  "Sim":"Não" ) << std::endl;
	std::cout << "Size? " << h2.size()  << std::endl;
	for (int i = 0; i < h2.tam(); ++i)
	{
		std::cout << i << " -> " << h2.count(i) << std::endl;
	}

	int num = 0;
	h2.retrieve(199, num);
	std::cout << num << std::endl;

	std::cout << "h1.Operator[]: " << h2[2] << std::endl;
	std::cout << "h1.Operator[]: " << h2[101] << std::endl;
	h2.clear();
	for (int i = 0; i < h2.tam(); ++i)
	{
		std::cout << i << " -> " << h2.count(i) << std::endl;
	}
	return 0;
}