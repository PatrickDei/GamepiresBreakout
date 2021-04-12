#include "BreakpointController.h"

void BreakpointController::hitBlock(BreakpointObject* hitObject)
{
    if (Block* b = dynamic_cast<Block*>(hitObject)) {            
        _soundShouldBePlayed = true;
        if (b->loseHealth()) {
            _tempSoundPath = b->getBreakSoundPath();
            _objectController.removeObject(hitObject);
            _score += b->getScore();
        }
        else
            _tempSoundPath = b->getHitSoundPath();
    }
}

bool BreakpointController::shouldSoundBePlayed()
{
    return _soundShouldBePlayed;
}

int BreakpointController::getCurrentScore()
{
    return _score;
}

void BreakpointController::updateFrame(float dt)
{
    if (!_objectController.isGameOver()) {
        _objectController.checkCollisions(*this, dt);
        _objectController.updatePlayer();
    }
    else
        _gameIsOver = true;
}

vector<sf::RectangleShape> BreakpointController::shapesToDraw()
{
    return _objectController.getShapes();
}

bool BreakpointController::getGameOver()
{
    return _gameIsOver;
}

void BreakpointController::movePlayer(sf::Vector2i coordinates)
{
    _objectController.getPlayer()->setPosX((float) coordinates.x - _objectController.getPlayer()->getWidth() / 2);    
}

void BreakpointController::addSoundToQueue(sf::SoundBuffer* buffer)
{
    buffer->loadFromFile(_tempSoundPath);
    _soundShouldBePlayed = false;
}

Ball BreakpointController::getBallInstance()
{
    return _objectController.getBall();
}

int BreakpointController::getHealth()
{
    return _objectController.getPlayer()->getHealth();
}
