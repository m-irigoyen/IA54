#ifndef SEMANTIC_H_
#define SEMANTIC_H_

#include <string>

#include "Tags.h"

using namespace std;

/*
*   A Semantic is a type definition for a PhysicalObject.
*/

class Semantic
{
private:
	std::string semantic;
public:
	Semantic(std::string semantic = Tags::object);

	~Semantic(void);
	std::string getSemantic();
	void setSemantic(std::string semantic);
};

#endif
