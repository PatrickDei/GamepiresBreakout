#pragma once
#include "BreakpointObject.h"

class Wall : public BreakpointObject
{
private:
	float _endPositionX;
	float _endPositionY;

public:
	Wall(float x, float y, float endX, float endY) : _endPositionX(endX), _endPositionY(endY), BreakpointObject(x, y) {}

	//void getVertices(float& a, float& b, float& c, float& d);

	float distanceFromPoint(float x, float y);

	float getEndX();

	float getEndY();
};