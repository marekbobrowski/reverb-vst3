#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

enum Params : Steinberg::Vst::ParamID
{
	dampening = 0,
	decay = 1,
	diffusion = 2,
	dry = 3,
	highcut = 4,
	moddepth = 5,
	modfreq = 6,
	predelay = 7,
	size = 8,
	wet = 9
};

static const Steinberg::FUID kProcessorUID (0x14A8680C, 0x13FD561C, 0xA0AC2181, 0x7A0EE48B);
static const Steinberg::FUID kControllerUID (0x81FD9A3A, 0x581C5B89, 0x802E686B, 0x7A992101);