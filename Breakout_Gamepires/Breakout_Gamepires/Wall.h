#pragma once
#include "BreakpointObject.h"

class Wall : public BreakpointObject
{
private:

public:
	Wall(float x, float y, float width, float height) : BreakpointObject(x, y, width, height) {}

	float distanceFromPoint(float x, float y);
};