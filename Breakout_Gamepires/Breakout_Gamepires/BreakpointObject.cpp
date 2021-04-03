#include "BreakpointObject.h"

float BreakpointObject::getPosX() {
	return _positionX;
}

void BreakpointObject::setPosX(float value)
{
	if (value > 0)
		_positionX = value;
}

float BreakpointObject::getPosY() {
	return _positionY;
}

void BreakpointObject::setPosY(float value)
{
	if (value > 0)
		_positionY = value;
}

void BreakpointObject::setPosition(float x, float y)
{
	if (x > 0 && y > 0) {
		_positionX = x;
		_positionY = y;
	}
}
