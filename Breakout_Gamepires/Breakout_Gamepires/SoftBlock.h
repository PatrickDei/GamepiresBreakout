#pragma once
#include "Block.h"

#define ID "S"

class SoftBlock : public Block
{
private:
	void loseHealth() {
		_blockHealth--;
		if (_blockHealth == 0)
			destroyBlock();
	}

public:
	SoftBlock() : Block(ID){}
};

