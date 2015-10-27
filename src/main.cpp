#include "Simulator/Simulator.h"

using namespace std;

int main(int argc, char* argv[])
{
	Simulator simulator;

	//simulator.CreateWorld();
	simulator.run(sf::milliseconds(17));

	return EXIT_SUCCESS;
}

 