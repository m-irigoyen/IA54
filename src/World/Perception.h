#ifndef PERCEPTION_H_
#define PERCEPTION_H_

/*
*   A PerceptionWave object is constructed by the environment to represent all the wavelengths that a Body percieves.
*/

#include <iostream>
#include <map>
#include <vector>
#include <SFML/System/Time.hpp>

#include "Semantic.h"

using namespace std;

class Perception
{
public:
    Perception();

	struct BODY
	{
		Semantic type;
		float posX;
		float posY;
	};

	vector<BODY>& getPerceptions();

private:
	vector<BODY> bodies;
};

#endif
