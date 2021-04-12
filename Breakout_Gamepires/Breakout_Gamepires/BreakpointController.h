#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Wall.h"
#include "Ball.h"
#include "LevelController.h"
#include "TextureController.h"
#include <algorithm>

/// <summary>
/// Main controller class
/// Stores objects used in game (implement object controller in case of more object manipulation demand)
/// Communicates with main
/// </summary>
class BreakpointController
{
private:
	std::string _tempSoundPath;	
	Ball _ball;	
	LevelController _levelController;
	Player* _player;

	vector<sf::RectangleShape> _shapes;
	vector<BreakpointObject*> _objects;
	// info for main
	bool _gameIsOver;
	int _score;
	bool _soundShouldBePlayed;

	/// Adds objects to lists in their formats
	void addObjects(vector<BreakpointObject*> objects);

	/// Removes object safely from game -> need rework for objects that are moving (or good encapsulation)
	void removeObject(BreakpointObject* objectToRemove);
	
	/// Performs actions that should be performed when Block is hit
	void hitBlock(BreakpointObject* hitObject);

	/// Launches a new ball
	void relaunchBall();

	/// Performs checks for game over
	bool isGameOver();

	/// Returns number of blocks to ignore
	int indestructableBlocks();

	/// Performs actions for objects that should always be present
	void initialize();

public:	
	BreakpointController() : _gameIsOver(false), _soundShouldBePlayed(false), _score(0) {
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

	~BreakpointController() {
		delete _player;
	}

	/// Returns true if there is a sound in queue
	bool shouldSoundBePlayed();

	/// Returns player score
	int getCurrentScore();

	/// Returns player health
	int getHealth();

	// Adds appropriate sound to buffer
	void addSoundToQueue(sf::SoundBuffer* buffer);

	/// Returns the ball instance
	Ball getBallInstance();

	/// Moves the player to an approptiare position
	void movePlayer(sf::Vector2i coordinates);

	/// <summary>
	/// Performs actions that need to be done every frame
	/// </summary>
	/// <param name="dt"> Delta time in seconds </param>
	void updateFrame(float dt); 

	/// Returns shapes that need to be drawn
	std::vector<sf::RectangleShape> shapesToDraw();

	/// Returns true if game is over
	bool getGameOver();
};