#include <SFML/Graphics.hpp>
#include <iostream>
#include "BreakpointController.h"
#include <queue>

using namespace tinyxml2;
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Breakpoint");

    BreakpointController gameController = BreakpointController();

    sf::CircleShape ball(5.0f);

    /*sf::SoundBuffer buffer;
    // load something into the sound buffer...
    buffer.loadFromFile("Sounds/Hit_01.wav");

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();*/  

    sf::SoundBuffer buffer;
    std::queue<sf::SoundBuffer> bufferQueue;
    bufferQueue.push(buffer);

    std::queue<sf::Sound> soundQueue;
    sf::Sound newSound;
    soundQueue.push(newSound);

    soundQueue.back().setBuffer(bufferQueue.back());


    sf::SoundBuffer b;
    bufferQueue.push(b);
    
    sf::Sound s;
    soundQueue.push(s);
    soundQueue.back().setBuffer(bufferQueue.back());

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                gameController.movePlayer(mousePosition);
            }
        }
        sf::Time dt = clock.restart();
        gameController.updateFrame(dt.asSeconds());
        ball.setOrigin(0.5, 0.5),
        ball.setPosition(gameController.getBallInstance().getPosX(), gameController.getBallInstance().getPosY());

        /*if (gameController.soundShouldBePlayed) {
            gameController.addSoundToBuffer(&bufferQueue.front());
            gameController.addSoundToBuffer2(&bufferQueue.back());
        
            soundQueue.back().play();
            soundQueue.front().play();
}*/
        window.clear();

        for (sf::RectangleShape shape : gameController.shapesToDraw())
        {
            window.draw(shape);
        }
        window.draw(ball);

        window.display();
    }

    gameController.deleteObjects();

    return 0;
}