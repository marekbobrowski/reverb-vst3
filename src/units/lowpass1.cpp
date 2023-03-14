#include "lowpass1.h"

Lowpass1::Lowpass1(float g1, float g2) : Delay(1), g1(g1), g2(g2) {};

void Lowpass1::processSample(float& sampleIn, float& sampleOut)
{
	sampleOut = g1 * sampleIn + g2 * buffer[0];
	buffer[0] = sampleOut;
}

void Lowpass1::updateGains(float g1, float g2)
{
	this->g1 = g1;
	this->g2 = g2;
}
