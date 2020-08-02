#include "Frame.hpp"
#include "InputMap.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>


const auto TITLE = "SFML Haxball";
const auto PLAYER_SIZE = 30;
const auto BALL_SIZE = 20;

struct Game {
    sf::RenderWindow* window;
    sf::Vector2u windowSize;
    Frame frame;

    sf::CircleShape player;
    float moveSpeed{0.1};

    sf::CircleShape ball;
    sf::Vector2f ballDirection;
    float ballSpeed{0.07};

    Game(sf::RenderWindow* window, sf::Vector2u windowSize) : window(window), windowSize(windowSize){
        window->create(sf::VideoMode(windowSize.x, windowSize.y), TITLE);
        initScene();
    }

    void initScene(){
        frame = Frame{window};
        
        player = sf::CircleShape(PLAYER_SIZE);
        auto center = sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2);
        player.setPosition(sf::Vector2f(center.x - player.getRadius(), center.y - player.getRadius()));

        ball = sf::CircleShape(BALL_SIZE);
        float ballOffset = 60;
        ball.setPosition(
            sf::Vector2f(center.x - player.getRadius() + ballOffset, center.y - player.getRadius() + ballOffset));
        ballDirection = sf::Vector2f(1.0f, 0.0f);
        ball.setFillColor(sf::Color::Blue);
    }

    void handleWindowEvents(){
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close();
                break;
            default:
                break;
            }
        }
    }

    bool isCollidingWithWalls(sf::CircleShape cs){
        for (const auto wall : frame.walls){
            if (cs.getGlobalBounds().intersects(wall.getGlobalBounds())){
                return true;
            } 
        }
        return false;
    }

    void handleInput(){
        sf::Vector2f moveVector = getMoveVector();
        sf::Vector2f oldPosition = player.getPosition();
        player.move(moveVector);
        
        if (isCollidingWithWalls(player)) {
            player.setPosition(oldPosition);
        }

        sf::Vector2f ballOldPosition = ball.getPosition();
        ball.move(ballDirection.x * ballSpeed, ballDirection.y * ballSpeed);

        if (isCollidingWithWalls(ball)){
            ball.setPosition(ballOldPosition);
            ballDirection = sf::Vector2f(ballDirection.x * -1, ballDirection.y * -1);
        }

        if(player.getGlobalBounds().intersects(ball.getGlobalBounds())) {
            ball.setPosition(ballOldPosition);
            player.setPosition(oldPosition);
            // ballDirection = sf::Vector2f(ballDirection.x * -1, ballDirection.y);
            ballDirection = getDirectionVector(ballDirection, moveVector);

            std::cout << "move vector";
            vecutils::printVector<decltype(moveVector)>(moveVector);
        }
    }

    sf::Vector2f getDirectionVector(sf::Vector2f v1, sf::Vector2f v2){
        auto magnitude = std::sqrt(std::pow((v2.x - v1.x), 2) + std::pow(v2.y - v1.y ,2));
        return sf::Vector2f((v2.x - v1.x) / magnitude,  (v2.y - v1.y) / magnitude);
    }

    sf::Vector2f getMoveVector(){
        float x = 0;
        float y = 0;
        
        if (InputMap::left())
        {   
            x -= moveSpeed;
        }
        if (InputMap::right())
        {
            x += moveSpeed;  
        }
        if (InputMap::up())
        {
            y -= moveSpeed;
        }
        if (InputMap::down())
        {
            y += moveSpeed;
        }
        return sf::Vector2f(x,y);
    }

    void UpdateAndDraw(){
        Update();
        Draw();
    }

    void Update(){
        handleWindowEvents();
        handleInput();
    }

    void Draw(){
        window->clear();
        window->draw(player);
        window->draw(frame);
        window->draw(ball);
        window->display();
    }

    bool isRunning(){
        return window->isOpen();
    }

    void runGameLoop(){
        while (isRunning()){
            UpdateAndDraw();
        }
    }
};