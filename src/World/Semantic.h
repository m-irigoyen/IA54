#ifndef SEMANTIC_H_
#define SEMANTIC_H_

#include "Tags.h"

/*
*   A Semantic is a type definition for a PhysicalObject.
*/

class Semantic
{
private:
	std::string semantic;
public:
	Semantic(std::string semantic);

	~Semantic(void);
	std::string getSemantic();
	void setSemantic(std::string semantic);
};

#endif
