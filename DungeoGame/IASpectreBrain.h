#pragma once
#include "IABrain.h"
class IASpectreBrain: public IABrain
{
public:
	virtual void Execute(Mob* possessed) override;
};

