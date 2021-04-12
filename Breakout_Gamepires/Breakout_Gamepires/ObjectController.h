#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "LevelController.h"
#include "Player.h"

class BreakpointController;

class ObjectController
{
private:
	Ball _ball;
	LevelController _levelController;
	Player* _player;

	vector<sf::RectangleShape> _shapes;
	vector<BreakpointObject*> _objects;

	/// Adds objects to lists in their formats
	void addObjects(vector<BreakpointObject*> objects);

	/// Launches a new ball
	void relaunchBall();

	/// Returns number of blocks to ignore
	int indestructableBlocks();

	/// Performs actions for objects that should always be present
	void initialize();

public:
	ObjectController() {
		tinyxml2::XMLDocument params;
		params.LoadFile("Parameters/Parameters.xml");
		tinyxml2::XMLElement* rootElement = params.RootElement();

		float playerWidth = rootElement->FirstChildElement("playerWidth")->FloatText();

		// player
		_objects.push_back(new Player(0, windowHeight - 50, playerWidth, 15));
		_player = dynamic_cast<Player*>(_objects.front());

		// ball
		_ball = Ball(windowWidth / 2, windowHeight - 55, 10);

		initialize();
	}

	~ObjectController() {
		delete _player;
	}

	/// <summary>
	/// Performs actions every frame
	/// </summary>
	/// <param name="breakpointController"> Reference to the "main" controller class </param>
	/// <param name="dt"> Delta time from last frame </param>
	void checkCollisions(BreakpointController& breakpointController, float dt);

	/// Returns the ball insance
	Ball getBall();

	/// Returns the player reference
	Player* getPlayer();

	/// Returns the shapes that need to be drawn - shapes are already set to appropriate positions
	std::vector<sf::RectangleShape> getShapes();
	
	/// Performs checks for game over
	bool isGameOver();

	/// Removes object safely from game -> need rework for objects that are moving (or good encapsulation)
	void removeObject(BreakpointObject* objectToRemove);

	/// Moves the player shape to players position
	void updatePlayer();
};

