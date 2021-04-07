#pragma once
#include <vector>

using namespace std;

struct Point {
public:
	int x;
	int y;

	Point(int _x, int _y) : x(_x), y(_y) {}

	bool operator==(const Point& point) const {
		return (x == point.x && y == point.y);
	}
};

class BreakpointObject
{
protected:
	float _positionX;
	float _positionY;
	float _height;
	float _width;

	BreakpointObject(float x = 0, float y = 0, float width = 0, float height = 0) : _positionX(x), _positionY(y), _width(width), _height(height) {}

	vector<Point> getEdgePoints() {
		vector<Point> points;
		// horizontal points add
		for (int i = (int)_positionX; i <= _width; i++) {
			points.push_back(Point(i, _positionY));
			points.push_back(Point(i, _positionY + _height));
		}
		// vertical points add
		for (int i = (int)_positionY; i <= _height; i++) {
			points.push_back(Point(_positionX, i));
			points.push_back(Point(_positionX + _width, i));
		}

		return points;
	}

public:
	float getPosX();

	void setPosX(float value);

	float getPosY();

	void setPosY(float value);

	void setPosition(float x, float y);

	float getHeight();

	float getWidth();

	bool isInCollision(BreakpointObject* object) {
		vector<Point> obj1Points = this->getEdgePoints();
		vector<Point> obj2Points = object->getEdgePoints();

		for (Point point : obj1Points)
			for (Point point2 : obj2Points)
				if (point == point2)
					return true;

		return false;
	}
};