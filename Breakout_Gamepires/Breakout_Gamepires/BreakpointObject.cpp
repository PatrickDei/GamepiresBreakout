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

float BreakpointObject::getHeight()
{
	return _height;
}

float BreakpointObject::getWidth()
{
	return _width;
}

void BreakpointObject::setWidth(float value)
{
	if (value > 0)
		_width = value;
}

void BreakpointObject::setHeight(float value)
{
	if (value > 0)
		_height = value;
}

vector<Point> BreakpointObject::getEdgePoints() {
	vector<Point> points;
	// horizontal top points add
	for (int i = (int)_positionX; i <= _width + _positionX; i++)
		points.push_back(Point(i, _positionY));
	// vertical left points add
	for (int i = (int)_positionY; i <= _height + _positionY; i++)
		points.push_back(Point(_positionX, i));
	// horizontal bottom points add
	for (int i = (int)_positionX; i <= _width + _positionX; i++)
		points.push_back(Point(i, _positionY + _height));
	// vertical right points add
	for (int i = (int)_positionY; i <= _height + _positionY; i++)
		points.push_back(Point(_positionX + _width, i));

	return points;
}