#pragma once
#include <vector>
#include <iostream>

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

	virtual vector<Point> getEdgePoints();

public:
	float getPosX();

	void setPosX(float value);

	float getPosY();

	void setPosY(float value);

	void setPosition(float x, float y);

	float getHeight();

	float getWidth();

	void setWidth(float value);

	void setHeight(float value);

	virtual void getDirections(float& x, float& y);

	// if called as bool returns if objects are touching, if called as int, returns index of rectangle side
	template<class T>
	T isInCollision(BreakpointObject* object) {
		vector<Point> obj1Points = this->getEdgePoints();
		vector<Point> obj2Points = object->getEdgePoints();

		return checkCollisionByType<T>(obj1Points, obj2Points, object);
	}

	//currently only used for bool return type, be careful -> just checks if anything is touching
	template<class T>
	T checkCollisionByType(vector<Point> obj1Points, vector<Point> obj2Points, BreakpointObject* object) {
		for (Point point : obj1Points) {
			for (Point point2 : obj2Points) {
				if (point == point2) {
					return true;
				}
			}
		}

		return false;
	}

	// returns index of side that was touched
	template<>
	int checkCollisionByType(vector<Point> obj1Points, vector<Point> obj2Points, BreakpointObject* object) {
		for (size_t i = 0; i < obj1Points.size(); i++)
			for (size_t j = 0; j < obj2Points.size(); j++)
				if (obj1Points[i] == obj2Points[j]) {
					if (j < object->_width)
						return 1;
					if (j < object->_width + object->_height)
						return 2;
					if (j < 2 * object->_width + object->_height)
						return 3;
					return 4;
				}
		return 0;
	}

	template<>
	float checkCollisionByType(vector<Point> obj1Points, vector<Point> obj2Points, BreakpointObject* object) {
		for (Point point : obj1Points) {
			for (Point point2 : obj2Points) {
				if (point == point2) {
					return ((object->getPosX() + object->getWidth() - point.x) / object->getWidth()) * 180;
					// (objects far right point - point of touch) / object width * 180 -> degrees to launch at
					//return object->getWidth() / 2 + object->getPosX() - point2.x;
				}
			}
		}
		return 0;
	}

	virtual ~BreakpointObject(){
	}
};