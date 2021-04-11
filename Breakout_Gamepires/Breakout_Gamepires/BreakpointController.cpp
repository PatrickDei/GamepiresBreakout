#include "BreakpointController.h"

void BreakpointController::addObjects(vector<BreakpointObject*> objects)
{
    _objects.insert(_objects.end(), objects.begin(), objects.end());
    for (BreakpointObject* object : objects) {
        _shapes.push_back(sf::RectangleShape(sf::Vector2f(object->getWidth(), object->getHeight())));
        _shapes.back().setPosition(object->getPosX(), object->getPosY());
        //apply texture
        if (SoftBlock* b = dynamic_cast<SoftBlock*>(object)) {
            /*sf::Texture t;
            if (t.loadFromFile(b->getTexturePath()))
                _shapes.back().setTexture(&t);*/
            _shapes.back().setFillColor(sf::Color::White);
        }
        if (MediumBlock* b = dynamic_cast<MediumBlock*>(object)) {
            _shapes.back().setFillColor(sf::Color::Green);

        }
        if (HardBlock* b = dynamic_cast<HardBlock*>(object)) {
            /*sf::Texture t;
            if (t.loadFromFile(b->getTexturePath()))
                _shapes.back().setTexture(&t);*/
            _shapes.back().setFillColor(sf::Color::Magenta);
        }
        if (ImpenetrableBlock* b = dynamic_cast<ImpenetrableBlock*>(object)) {
            /*sf::Texture t;
            if (t.loadFromFile(b->getTexturePath()))
                _shapes.back().setTexture(&t);*/
            _shapes.back().setFillColor(sf::Color::Red);

        }
    }
}

void BreakpointController::removeObject(BreakpointObject* objectToRemove)
{
    _objects.erase(std::remove(_objects.begin(), _objects.end(), objectToRemove));
    for (size_t i = 0; i < _shapes.size(); i++)
        if (_shapes[i].getPosition().x == objectToRemove->getPosX() && _shapes[i].getPosition().y == objectToRemove->getPosY())
            _shapes.erase(_shapes.begin() + i);    
    
    delete objectToRemove;
}

void BreakpointController::hitObject(BreakpointObject* hitObject)
{
    if (Block* b = dynamic_cast<Block*>(hitObject)) {            
        _soundShouldBePlayed = true;
        if (b->loseHealth()) {
            _tempSoundPath = b->getBreakSoundPath();
            removeObject(hitObject);
            _score += b->getScore();
        }
        else
            _tempSoundPath = b->getHitSoundPath();
    }
}

void BreakpointController::relaunchBall()
{
    _ball = Ball(windowWidth / 2, windowHeight - 55, 10);
}

bool BreakpointController::isGameOver()
{
    if (dynamic_cast<Player*>(_objects.front())->getHealth() < 1)
        return true;
    if (_objects.size() <= 4 + indestructableBlocks())
        return true;
    return false;
}

void BreakpointController::endTheGame()
{
    _gameIsOver = true;
}

int BreakpointController::indestructableBlocks()
{
    int impenetrableBlocksCount = 0;
    for (BreakpointObject* o : _objects)
        if (ImpenetrableBlock* b = dynamic_cast<ImpenetrableBlock*>(o))
            impenetrableBlocksCount++;
    return impenetrableBlocksCount;
}

int BreakpointController::getCurrentScore()
{
    return _score;
}

void BreakpointController::updateFrame(float dt)
{
    if (!isGameOver()) {

        // ball moving
        _ball.update(dt);
        _ball.setPosition(_ball.getPosX(), _ball.getPosY());

        // collision check
        for (size_t i = 0; i < _objects.size(); i++) {
            int objectEdge = _ball.isInCollision<int>(_objects[i]);
            if (objectEdge != 0) {
                switch (objectEdge) {
                case 1:
                case 3:
                    _ball.invertDirectionVector("y");
                    break;
                case 2:
                case 4:
                    _ball.invertDirectionVector("x");
                    break;
                default:
                    _ball.setDirection(_ball.getDirectionAngle() + 180);
                }
                if (i > 3)
                    hitObject(_objects[i]);
            }
        }

        // player collision
        int angleOfBounce = _ball.isInCollision<float>(_objects.front());
        if (angleOfBounce != 0.0f)
            _ball.setDirection(angleOfBounce);

        // is ball out of screen
        if (_ball.getPosY() >= windowHeight) {
            dynamic_cast<Player*>(_objects.front())->loseHealth();
            relaunchBall();
        }

        // load new level
        if (_objects.size() <= indestructableBlocks() + 4) {
            relaunchBall();
            _objects.erase(_objects.begin() + 3);
            addObjects(_levelController.loadBlocksForNextLevel());
        }
    }
    else
        endTheGame();
}

vector<sf::RectangleShape> BreakpointController::shapesToDraw()
{
    return _shapes;
}

void BreakpointController::movePlayer(sf::Vector2i coordinates)
{
    _objects.front()->setPosX((float) coordinates.x - _objects.front()->getWidth() / 2);    
    _shapes.front().setPosition(_objects.front()->getPosX(), _shapes.front().getPosition().y);

}

void BreakpointController::addSoundToQueue(sf::SoundBuffer* buffer)
{
    buffer->loadFromFile(_tempSoundPath);
    _soundShouldBePlayed = false;
}

Ball BreakpointController::getBallInstance()
{
    return _ball;
}

void BreakpointController::drawWalls()
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
}

int BreakpointController::getHealth()
{
    return dynamic_cast<Player*>(_objects.front())->getHealth();
}
