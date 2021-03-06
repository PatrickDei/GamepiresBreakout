#include <SFML/Graphics.hpp>
#include "BreakpointController.h"
#include <queue>

int main()
{
    /// essentials
    /// dimensions set in LevelController.h
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Breakpoint");

    BreakpointController gameController = BreakpointController();

    sf::CircleShape ball(5.0f); ball.setOrigin(1, 1);

    /// background
    sf::Texture t;
    t.loadFromFile("Textures/Boards/Boards_01.jpg");
    t.setRepeated(true);

    sf::Sprite background;
    background.scale(sf::Vector2f(4, 3));
    background.setTexture(t);

    // health icons
    sf::Texture h;
    h.loadFromFile("Textures/Health/Heart.png");

    sf::Sprite health;
    health.setTexture(h);
    
    /// UI texts
    sf::Font font;
    font.loadFromFile("Fonts/TrainOne-Regular.ttf");
    sf::Text endGameText;
    endGameText.setFont(font);
    endGameText.setCharacterSize(100);
    endGameText.setString("GAME OVER!");
    endGameText.setPosition(windowWidth / 2, windowHeight / 2 + 100);

    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(70);

    /**
    * Elements needed for sounds
    * 
    * Queues used to keep sound nodes alive and releasing after sound has been played
    */
    std::queue<sf::SoundBuffer> bufferQueue;
    std::queue<sf::Sound> soundQueue;

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

        ball.setPosition(gameController.getBallInstance().getPosX(), gameController.getBallInstance().getPosY());

        /// game controller says if a sound should be played and buffers request which sound to load
        if (gameController.shouldSoundBePlayed()) {
            sf::SoundBuffer buffer;
            sf::Sound sound;
            bufferQueue.push(buffer);
            soundQueue.push(sound);
            gameController.addSoundToQueue(&bufferQueue.back());
        
            soundQueue.back().setBuffer(bufferQueue.back());
            soundQueue.back().play();
        }
        /// check if there are elements in queues and if ready, release them
        if (soundQueue.size() > 0 && soundQueue.front().getStatus() != sf::Sound::Playing) {
            bufferQueue.pop();
            soundQueue.pop();
        }

        score.setString(std::to_string(gameController.getCurrentScore()));
        score.setPosition(windowWidth / 2 - score.getGlobalBounds().width / 2, windowHeight / 2 - score.getGlobalBounds().height / 2);

        /// drawing
        window.clear();

        window.draw(background);
        window.draw(score);
        for (sf::RectangleShape shape : gameController.shapesToDraw())
        {
            window.draw(shape);
        }
        for (int i = 0; i < gameController.getHealth(); i++) {
            health.setPosition(i * (health.getTexture()->getSize().x + 50) + 50, windowHeight - 150);
            window.draw(health);
        }
        window.draw(ball);
        if (gameController.getGameOver()) {
            window.draw(endGameText);
        }

        window.display();
    }
    return 0;
}