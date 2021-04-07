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

/*bool BreakpointObject::isInCollision(BreakpointObject* object)
{
	vector<pair<float, float>> obj1Points = this->getEdgePoints();
	vector<pair<float, float>> obj2Points = object->getEdgePoints();

	for (pair<float, float> point : obj1Points)
		for (pair<float, float> point2 : obj2Points)
			if (point == point2)
				return true;

	return false;
}*/

/*vector<pair<float, float>> BreakpointObject::getEdgePoints()
{
	vector<pair<float, float>> points;
	// horizontal points add
	for (int i = _positionX; i <= _width; i++) {
		points.push_back(make_pair(i, _positionY));
		points.push_back(make_pair(i, _positionY + _height));
	}
	// vertical points add
	for (int i = _positionY; i <= _height; i++) {
		points.push_back(make_pair(_positionX, i));
		points.push_back(make_pair(_positionX + _width, i));
	}

	return points;
}*/