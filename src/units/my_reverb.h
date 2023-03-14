#pragma once

#include "unit.h"
#include "delay.h"
#include "modulated_interpolated_allpass.h"
#include "lowpass1.h"
#include "allpass.h"
#include <vector>

class MyReverb : public Unit
{
public:
	MyReverb();
	~MyReverb();
	void processStereoSample(float& sampleInLeft, float& sampleInRight, float& sampleOutLeft, float& sampleOutRight);
	void setDecay(float decay);
	float getDecay();
	void setHighcut(float highcut);
	float getHighcut();
	void setDampening(float dampening);
	float getDampening();
	void setDiffusion(float diffusion);
	float getDiffusion();
	void setSize(float size);
	float getSize();
	void setDry(float dry);
	float getDry();
	void setWet(float wet);
	float getWet();
	void setPredelay(float preDelay);
	float getPreDelay();
	void setModulationDepth(float depth);
	float getModulationDepth();
	void setModulationFrequency(float frequency);
	float getModulationFrequency();
protected:
	void scaleGains(float scale);

	std::vector<unsigned> inputDiffusorsDelays = { 391, 503, 141, 199 }; 
	std::vector<float> inputDiffusorsGains = { 0.7, 0.5, 0.7, 0.7 };
	std::vector<Allpass*> inputDiffusors;

	std::vector<unsigned> loopDiffusorsDelays = { 6199, 2791, 6573, 2929, 4589, 3159, 5513, 2947, 3383, 2429 };
	std::vector<float> loopDiffusorsGains = { 0.5, 0.7, 0.7, 0.5, 0.7, 0.7, 0.5, 0.7, 0.7, 0.5 };
	std::vector<Allpass*> loopDiffusors;

	std::vector<float> modulatedLoopDiffusorsDelays = { 889, 1549 }; 
	std::vector<float> modulatedLoopDiffusorsGains = { 0.5, 0.5 };
	std::vector<ModulatedInterpolatedAllpass*> modulatedLoopDiffusors;

	Delay* preDelayUnit = new Delay(0);

	Lowpass1* highcutUnit = new Lowpass1(0.8, 0.2);
	Lowpass1* dampeningUnit = new Lowpass1(0.995, 0.005);
	Lowpass1* dampeningUnit2 = new Lowpass1(0.995, 0.005);

	float dampening = 0.005;
	float decay = 0.7;
	float diffusion = 1;
	float dry = 1;
	float highcut = 0.8;
	float moddepth = 0.5;
	float modfreq = 0.25;
	float preDelay = 0;
	float size = 0.8;
	float wet = 0.3;

	// store the latest sample that came out of the cascaded all-passes
	float feedbackTap = 0;
};
