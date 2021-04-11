#pragma once
#include "Block.h"
class ImpenetrableBlock : public Block
{
public:
	ImpenetrableBlock() : Block('I') {}

	bool loseHealth() override;
};

