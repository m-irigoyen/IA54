#include "Problem.h"

Problem::Problem(float waveAmplLossPerSec, bool useAttenuation) : waveAmplLossPerSec(waveAmplLossPerSec), problemLive(true), useWaveAttenuation(useAttenuation)
{
}

float Problem::getAmplitudeLoss()
{
	return this->waveAmplLossPerSec;
}

bool Problem::getProblemLive()
{
	return this->problemLive;
}

bool Problem::isUsingAttenuation()
{
	return this->useWaveAttenuation;
}