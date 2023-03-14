#include "my_reverb.h"
#include <cmath>

MyReverb::MyReverb()
{
	for (int i = 0; i < inputDiffusorsGains.size(); i++)
	{
		inputDiffusors.push_back(new Allpass(inputDiffusorsGains[i], inputDiffusorsDelays[i]));
	}
	for (int i = 0; i < loopDiffusorsGains.size(); i++)
	{
		loopDiffusors.push_back(new Allpass(loopDiffusorsGains[i], loopDiffusorsDelays[i]));
	}
	for (int i = 0; i < modulatedLoopDiffusorsGains.size(); i++)
	{
		modulatedLoopDiffusors.push_back(new ModulatedInterpolatedAllpass(70, 0.5, modulatedLoopDiffusorsGains[i], modulatedLoopDiffusorsDelays[i]));
	}
}

MyReverb::~MyReverb()
{
	for (Unit* o : inputDiffusors)
	{
		delete o;
	}
	for (Unit* o : loopDiffusors)
	{
		delete o;
	}
	for (Unit* o : modulatedLoopDiffusors)
	{
		delete o;
	}
	delete preDelayUnit;
	inputDiffusors.clear();
	loopDiffusors.clear();
	modulatedLoopDiffusors.clear();
}

void MyReverb::processStereoSample(float& sampleInLeft, float& sampleInRight, float& sampleOutLeft, float& sampleOutRight)
{	
	float mixedInput = (sampleInLeft + sampleInRight) / 2;

	float in = mixedInput;

	float out = in;

	preDelayUnit->processSample(in, out);

	in = out;

	highcutUnit->processSample(in, out);

	for (int i = 0; i < inputDiffusors.size(); i++)
	{
		Unit* o = inputDiffusors[i];
		in = out;
		o->processSample(in, out);
	}


	in += out + feedbackTap * decay;

	out = in;

	for (int i = 0; i < loopDiffusors.size(); i++)
	{
		Unit* o = loopDiffusors[i];
		in = out;
		o->processSample(in, out);
	}

	for (int i = 0; i < modulatedLoopDiffusors.size(); i++)
	{
		Unit* o = modulatedLoopDiffusors[i];
		in = out;
		o->processSample(in, out);
		if (fabsf(out) > 10 || fabsf(out) > 10)
		{
			float stopkurr = 0;
		}
	}

	in = out;

	dampeningUnit->processSample(in, out);
	
	in = out;

	dampeningUnit2->processSample(in, out);

	feedbackTap = out;
	
	sampleOutLeft = (out + loopDiffusors[4]->getTap(45) +
					loopDiffusors[6]->getTap(65) -
					loopDiffusors[8]->getTap(78) -
					loopDiffusors[9]->getTap(13)) * wet + sampleInLeft * dry;
	sampleOutRight = (out + loopDiffusors[3]->getTap(71) +
					loopDiffusors[5]->getTap(31) -
					loopDiffusors[7]->getTap(54) -
					loopDiffusors[9]->getTap(79)) * wet + sampleInRight * dry;


}


void MyReverb::setSize(float size)
{
	size = fmaxf(0.1, size);
	this->size = size;
	for (int i = 0; i < inputDiffusors.size(); i++)
	{
		this->inputDiffusors[i]->updateDelayLength((unsigned)(inputDiffusorsDelays[i] * size));
	}
	for (int i = 0; i < loopDiffusors.size(); i++)
	{
		this->loopDiffusors[i]->updateDelayLength((unsigned)(loopDiffusorsDelays[i] * size));
	}
	for (int i = 0; i < modulatedLoopDiffusors.size(); i++)
	{
		this->modulatedLoopDiffusors[i]->setCenterDelayLength(modulatedLoopDiffusorsDelays[i] * size);
	}
}

float MyReverb::getSize()
{
	return size;
}

void MyReverb::setDecay(float decay)
{
	this->decay = decay;
}

float MyReverb::getDecay()
{
	return decay;
}

void MyReverb::setDampening(float dampening)
{
	this->dampening = fmaxf(0.005, fminf(0.995, dampening));
	this->dampeningUnit->updateGains(1 - this->dampening, this->dampening);
	this->dampeningUnit2->updateGains(1 - this->dampening, this->dampening);
}

float MyReverb::getDampening()
{
	return dampening;
}

void MyReverb::setHighcut(float highcut)
{
	this->highcut = fmaxf(0.005, fminf(0.995, highcut));
	this->highcutUnit->updateGains(this->highcut, 1-this->highcut);
}

float MyReverb::getHighcut()
{
	return highcut;
}

void MyReverb::setDiffusion(float diffusion)
{
	this->diffusion = diffusion;
	this->scaleGains(diffusion);
}

float MyReverb::getDiffusion()
{
	return diffusion;
}

void MyReverb::scaleGains(float scale)
{
	for (int i = 0; i < loopDiffusors.size(); i++)
	{
		this->loopDiffusors[i]->g = loopDiffusorsGains[i] * scale;
	}
}

void MyReverb::setDry(float dry)
{
	this->dry = dry;
}

float MyReverb::getDry()
{
	return dry;
}

void MyReverb::setWet(float wet)
{
	this->wet = wet;
}

float MyReverb::getWet()
{
	return wet;
}

void MyReverb::setPredelay(float preDelay)
{
	this->preDelay = preDelay;
	this->preDelayUnit->updateDelayLength((unsigned)(44099 * preDelay));
}

float MyReverb::getPreDelay()
{
	return preDelay;
}

void MyReverb::setModulationDepth(float depth)
{
	this->moddepth = depth;
	for (int i = 0; i < modulatedLoopDiffusors.size(); i++)
	{
		this->modulatedLoopDiffusors[i]->setModulationDepth(depth * 140);
	}
}

float MyReverb::getModulationDepth()
{
	return moddepth;
}

void MyReverb::setModulationFrequency(float frequency)
{
	this->modfreq = frequency;
	for (int i = 0; i < modulatedLoopDiffusors.size(); i++)
	{
		this->modulatedLoopDiffusors[i]->setModulationFrequency(frequency * 2);
	}
}

float MyReverb::getModulationFrequency()
{
	return modfreq;
}
