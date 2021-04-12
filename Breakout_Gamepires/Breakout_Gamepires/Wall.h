#pragma once
#include "BreakpointObject.h"

/// <summary>
/// Wall class behaves exactly like base BreakpointObject
/// </summary>
class Wall : public BreakpointObject
{
public:
	Wall(float x, float y, float width, float height) : BreakpointObject(x, y, width, height) {}
};