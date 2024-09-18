#pragma once
#include "IABrain.h"

class IAGolemBrain : public IABrain
{
public:
	virtual void Execute(Mob* possessedMob) override;
};

