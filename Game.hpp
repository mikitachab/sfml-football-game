#include "Frame.hpp"
#include <SFML/Graphics.hpp>

#include <iostream>


const auto TITLE = "SFML Haxball";
const auto PLAYER_SIZE = 30;



struct Game {
    sf::RenderWindow* window;
    sf::Vector2u windowSize;
    Frame frame;
    sf::CircleShape player;

    Game(sf::RenderWindow* window, sf::Vector2u windowSize) : window(window), windowSize(windowSize){
        window->create(sf::VideoMode(windowSize.x, windowSize.y), TITLE);
        initScene();
    }

    void initScene(){
        frame = Frame{window};
        player = sf::CircleShape(PLAYER_SIZE);
        auto center = sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2);
        player.setPosition(sf::Vector2f(center.x - player.getRadius(), center.y - player.getRadius()));
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

    void handleInput(){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {   
            player.move(-0.1f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            player.move(0.1f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            player.move(0.0f, -0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            player.move(0.0f, 0.1f);
        }
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
        window->draw(frame);
        window->draw(player);
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