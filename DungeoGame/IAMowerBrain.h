#pragma once
#include "IABrain.h"
class IAMowerBrain : public IABrain
{
public:
	virtual void Execute(Mob* possessedMob) override;
};

