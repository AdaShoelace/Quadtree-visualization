#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <random>
#include <vector>
#include "qtree.h"

int myRand(int pos);
void addDots(sf::RenderWindow& window, std::vector<sf::CircleShape*>& vec, QTree& qtree);
void removeDots(std::vector<sf::CircleShape*>& vec);

int main(int argc, char* argv[]) {
    int windowX, windowY;

    if(argc < 2) {
        windowX = 1024;
        windowY = 768;
    } else {
        windowX = atoi(argv[1]);
        windowY = atoi(argv[2]);
    }

    std::srand(time(0));
    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Qtree test");
    std::vector<sf::CircleShape*> dotVector;
    QTree q(5, sf::Rect<int>(0,0,window.getSize().x, window.getSize().y), &window);
    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.key.code == sf::Keyboard::Escape ||
                event.type == sf::Event::Closed) {
                window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                addDots(window, dotVector, q);
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                removeDots(dotVector);
                window.clear(sf::Color::Black);
            }
        }
        window.clear(sf::Color::Black);
        for (sf::CircleShape* d : dotVector) {
            window.draw(*d);
        }
        q.draw();
        window.display();
    }
}

void addDots(sf::RenderWindow& window, std::vector<sf::CircleShape*>& vec, QTree& qtree) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::CircleShape* circle = new sf::CircleShape(2);
    //circle->setPosition(myRand(mousePos.x), myRand(mousePos.y));
    circle->setPosition(mousePos.x, mousePos.y);
    circle->setFillColor(sf::Color::Green);
    vec.push_back(circle);
    qtree.insert(*circle);
}

int myRand(int pos) { return pos + (rand() % 20 - 10); }

void removeDots(std::vector<sf::CircleShape*>& vec) { vec.clear(); }
