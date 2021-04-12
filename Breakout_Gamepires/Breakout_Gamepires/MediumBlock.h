#pragma once
#include "Block.h"

/// <summary>
/// Medium block class - passes char ID to base class
/// </summary>
class MediumBlock : public Block
{
public:
	MediumBlock() : Block('M') {}
};

