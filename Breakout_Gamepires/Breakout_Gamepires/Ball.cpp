#include "Ball.h"

float Ball::getSpeed() {
	return _speed;
}

void Ball::setSpeed(float value) {
	if (value > 0)
		_speed = value;
}

float Ball::getDirectionAngle() {
	return _direction;
}

void Ball::getDirections(float& x, float& y) {
	x = (float) cos(_direction * PI / 180);
	y = (float) -sin(_direction * PI / 180);
}

void Ball::setDirection(float angle) {
	while (angle < 0)
		angle += 360;
	while (angle >= 360)
		angle -= 360;
	_direction = angle;
}

void Ball::invertDirectionVector(const char* axis)
{
	float x, y;
	getDirections(x, y);
	if (strcmp(axis, "x") == 0)
		x = -x;
	else
		y = -y;
	_direction = atan(y / x) * 180 / PI;
	if ((x < 0) ? (y > 0) : (y < 0))
		_direction += 180;
	if (y < 0)
		_direction = 180 - _direction;
	else if (y > 0)
		_direction = 360 - _direction;
	setDirection(_direction);
}

vector<Point> Ball::getEdgePoints() {
	vector<Point> points;
	for (int i = 0; i < 360; i++)
		points.push_back(Point(_positionX + cos(i) * _width, _positionY + sin(i) * _height));
	return points;
}