#pragma once
#include "Block.h"

/// <summary>
/// Soft block class - passes char ID to base class
/// </summary>
class SoftBlock : public Block
{
private:

public:
	SoftBlock() : Block('S'){}
};

