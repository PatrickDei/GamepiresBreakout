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

vector<Point> Ball::getEdgePoints()
{
	return vector<Point>();
}
