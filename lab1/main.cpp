#include <fstream>
#include <iostream>

#include "Game.h"
int main(int argc, char * argv[])
{
	if (argc == 2)
	{
		emulatedRandomGame(argv[1]);
	}
	else
	{
		std::cout << "wrong command line argument!";
	}
	std::cout << "press enter to exit";
	std::cin.get();
	return 0;
}