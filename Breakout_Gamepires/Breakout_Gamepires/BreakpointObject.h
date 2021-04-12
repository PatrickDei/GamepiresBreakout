#pragma once
#include <vector>

using std::vector;

/**
* Struct used instead of std::pair with overloaded operator
*/
struct Point {
public:
	int x;
	int y;

	Point(int _x, int _y) : x(_x), y(_y) {}

	bool operator==(const Point& point) const {
		return (x == point.x && y == point.y);
	}
};

/**
* Base class for all custom elements for Breakpoint
* 
* Inherited by Ball, Block & Wall
* 
* Members usd for positioning, collision calculation and help with the SFML library
* @param _positionX Coordinate x of object
* @param _positionY Coordinate y of object
* @param _height Height of object
* @param _width Width of object
*/
class BreakpointObject
{
protected:
	float _positionX;
	float _positionY;
	float _height;
	float _width;

	BreakpointObject(float x = 0, float y = 0, float width = 0, float height = 0) : _positionX(x), _positionY(y), _width(width), _height(height) {}

	/// <summary>
	/// Calculates the "space" object is occupying
	/// Overloaded for Ball since it isn't a rectangle
	/// </summary>
	/// <returns> List of Points along the objects edges </returns>
	virtual vector<Point> getEdgePoints();

public:
	float getPosX();

	/// Overriden by Player
	virtual void setPosX(float value);

	float getPosY();

	void setPosY(float value);

	/// Overriden by Player
	virtual void setPosition(float x, float y);

	float getHeight();

	float getWidth();

	void setWidth(float value);

	void setHeight(float value);

	/**
	* Detects wether objects are in collision & returns extra information based on T
	* 
	* @tparam T determines what info is sent back
	*		bool -> are objects in collision
	*		int -> which side of the rectangle is being touched
	*		float -> returns the degrees at which the ball should bounce
	* @param object Object for which we are checking wether this is touching it
	*/
	template<class T>
	T isInCollision(BreakpointObject* object) {
		vector<Point> obj1Points = this->getEdgePoints();
		vector<Point> obj2Points = object->getEdgePoints();

		return checkCollisionByType<T>(obj1Points, obj2Points, object);
	}

	/// <summary>
	/// Returns information about collision based on T parameter
	/// </summary>
	/// <typeparam name="T"> Determines the return values </typeparam>
	/// <param name="obj1Points"> Edge points from this object </param>
	/// <param name="obj2Points"> Edge points from other object </param>
	/// <param name="object"> Other object reference </param>
	/// <returns> Information about collision </returns>
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

	/// Returns index of side that was touched
	/// 1 - top, 2 - right, 3 - bottom, 4 - left
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

	/// Returns angle at which to bounce the object
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