#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Wall.h"
#include "Ball.h"
#include "LevelController.h"
#include "TextureController.h"
#include "ObjectController.h"
#include <algorithm>

/// <summary>
/// Main controller class
/// Stores UI info
/// Communicates with main and other controllers
/// </summary>
class BreakpointController
{
private:
	ObjectController _objectController;
	std::string _tempSoundPath;
	// info for main
	bool _gameIsOver;
	int _score;
	bool _soundShouldBePlayed;

public:	
	BreakpointController() : _gameIsOver(false), _soundShouldBePlayed(false), _score(0) {}

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

	/// Performs actions that should be performed when Block is hit
	void hitBlock(BreakpointObject* hitObject);
};