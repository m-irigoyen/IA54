#include "Semantic.h"

Semantic::Semantic(std::string semantic) : semantic(semantic)
{
}

Semantic::~Semantic(void)
{
}

std::string Semantic::getSemantic()
{
	return this->semantic;
}

void Semantic::setSemantic(std::string semantic)
{
	this->semantic = semantic;
}