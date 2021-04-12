#pragma once
#include "Block.h"

/// <summary>
/// Hard block class - passes char ID to base class
/// </summary>
class HardBlock : public Block
{
public:
	HardBlock() : Block('H') {}
};

