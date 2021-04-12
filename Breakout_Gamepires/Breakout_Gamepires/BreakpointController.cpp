#include "BreakpointController.h"

/*void BreakpointController::addObjects(vector<BreakpointObject*> objects)
{
    _objects.insert(_objects.end(), objects.begin(), objects.end());
    for (BreakpointObject* object : objects) {
        _shapes.push_back(sf::RectangleShape(sf::Vector2f(object->getWidth(), object->getHeight())));
        _shapes.back().setPosition(object->getPosX(), object->getPosY());
        //apply texture
        if (SoftBlock* b = dynamic_cast<SoftBlock*>(object))
            _shapes.back().setFillColor(sf::Color::White);

        if (MediumBlock* b = dynamic_cast<MediumBlock*>(object))
            _shapes.back().setFillColor(sf::Color::Green);

        if (HardBlock* b = dynamic_cast<HardBlock*>(object))
            _shapes.back().setFillColor(sf::Color::Magenta);

        if (ImpenetrableBlock* b = dynamic_cast<ImpenetrableBlock*>(object))
            _shapes.back().setFillColor(sf::Color::Red);
    }
}

void BreakpointController::removeObject(BreakpointObject* objectToRemove)
{
    _objects.erase(std::remove(_objects.begin(), _objects.end(), objectToRemove));
    for (size_t i = 0; i < _shapes.size(); i++)
        if (_shapes[i].getPosition().x == objectToRemove->getPosX() && _shapes[i].getPosition().y == objectToRemove->getPosY())
            _shapes.erase(_shapes.begin() + i);    
    
    delete objectToRemove;
}*/

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

/*void BreakpointController::relaunchBall()
{
    _ball = Ball(windowWidth / 2, windowHeight - 55, 10);
}

bool BreakpointController::isGameOver()
{
    if (dynamic_cast<Player*>(_player)->getHealth() < 1)
        return true;
    if ((int) _objects.size() <= 4 + indestructableBlocks())
        return true;
    return false;
}

int BreakpointController::indestructableBlocks()
{
    int impenetrableBlocksCount = 0;
    for (BreakpointObject* o : _objects)
        if (ImpenetrableBlock* b = dynamic_cast<ImpenetrableBlock*>(o))
            impenetrableBlocksCount++;
    return impenetrableBlocksCount;
}*/

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

        // ball moving
        //_objectController.getBall().update(dt);
        _objectController.checkCollisions(*this, dt);
        _objectController.updatePlayer();
        /*_ball.setPosition(_ball.getPosX(), _ball.getPosY());

        // collision check
        for (size_t i = 0; i < _objects.size(); i++) {

            int objectEdge = _ball.isInCollision<int>(_objects[i]);
            if (objectEdge != 0) {
                switch (objectEdge) {
                case 1:
                case 3:
                    _ball.invertDirectionVector('y');
                    break;
                case 2:
                case 4:
                    _ball.invertDirectionVector('x');
                    break;
                default:
                    _ball.setDirection(_ball.getDirectionAngle() + 180);
                }
                if (i > 3)
                    hitBlock(_objects[i]);
            }
        }

        // player collision
        int angleOfBounce = _ball.isInCollision<float>(_player);
        if (angleOfBounce != 0.0f)
            _ball.setDirection(angleOfBounce);

        // is ball out of screen
        if (_ball.getPosY() >= windowHeight) {
            dynamic_cast<Player*>(_player)->loseHealth();
            relaunchBall();
        }

        // load new level
        if (_objects.size() <= indestructableBlocks() + 4) {
            relaunchBall();
            if (_objects.size() > 4)
                _objects.erase(_objects.begin() + 4);
            addObjects(_levelController.loadBlocksForNextLevel());
        }*/
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
    //_objectController.getShapes().front().setPosition(_objectController.getPlayer()->getPosX(), _objectController.getShapes().front().getPosition().y);
    
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

/*void BreakpointController::initialize()
{
    _objects.push_back(new Wall(0, 0, windowWidth, 10));
    _objects.push_back(new Wall(windowWidth - 10, 0, 10, windowHeight));
    _objects.push_back(new Wall(0, 0, 10, windowHeight));

    for (BreakpointObject* object : _objects) {
        _shapes.push_back(sf::RectangleShape(sf::Vector2f(object->getWidth(), object->getHeight())));
    }

    for (size_t i = 0; i < _shapes.size(); i++) {
        _shapes[i].setPosition(_objects[i]->getPosX(), _objects[i]->getPosY());
        if (i != 0)
            _shapes[i].setFillColor(sf::Color::Red);
    }
    
    addObjects(_levelController.loadBlocksForNextLevel());
}*/

int BreakpointController::getHealth()
{
    return _objectController.getPlayer()->getHealth();
}
