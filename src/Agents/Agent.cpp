#include "Agents/Agent.h"

// Converts given value from its range to the given range
float Agent::convertToRange(float value, float valueOffset, float valueRange, float targetOffset, float targetRange)
{
	if (value < 0 || valueOffset < 0 || valueRange <= 0 || targetOffset < 0 || targetRange <= 0
		||  value < valueOffset || value > valueRange+valueOffset)
	{
		cout << "ERROR : Agent::convertToRange : invalid parameters" << endl;
		cout << "    Parameters were : " << value << ", " << valueOffset << ", " << valueRange << ", " << targetOffset << ", " << targetRange << endl;

		if (value < 0)
			return -1.0f;
		if (value > valueOffset + valueRange)
			value = valueOffset + valueRange;
		else if (value < valueOffset)
			value = valueOffset;
	}

	//valueOffset		-> value				-> valueRange+valueOffset
	// 0				-> value-valueOffset	-> valueRange
	//float translatedValue = (value * valueRange) / (valueRange + valueOffset);
	float translatedValue = value - valueOffset;

	// 0		-> translatedValue		-> valueRange
	// 0		-> result - offset		-> range
	float translatedResult = (translatedValue * (targetRange)) / valueRange;
	//cout << "translated " << translatedResult << endl;

	// 0		-> translatedOffset		-> range
	//offset	-> result				-> range+offset
	return translatedResult + targetOffset;
}

Agent::Agent(Problem* problem, Body* body) : problem(problem), body(body)
{

}

Agent::~Agent(void)
{
}

void Agent::connect(Body* body)
{
	this->body = body;
}

// Checks if agent is linked to a body
bool Agent::isLinked()
{
	if (this->body == NULL)
		return false;
	return true;
}

// Cheks if agent is correctly linked to a problem
bool Agent::isProblemLinked()
{
	if (this->problem != NULL)
		return true;
	return false;
}

void Agent::disconnect()
{
	this->body = NULL;
}

void Agent::setProblem(Problem* problem)
{
	this->problem = problem;
}

Problem* Agent::getProblem()
{
	return this->problem;
}