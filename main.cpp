#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <random>
#include <vector>
#include "qtree.h"

int myRand(int pos);
void addDots(sf::RenderWindow& window, std::vector<sf::CircleShape*>& vec,
             QTree& qtree);
void removeDots(std::vector<sf::CircleShape*>& vec);

int main(int argc, char* argv[]) {
    int windowX, windowY;

    if (argc < 2) {
        windowX = 1024;
        windowY = 768;
    } else {
        windowX = atoi(argv[1]);
        windowY = atoi(argv[2]);
    }

    bool rectMouse = false;

    std::srand(time(0));
    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Qtree test");
    std::vector<sf::CircleShape*> dotVector;
    QTree q(5, sf::FloatRect(0, 0, window.getSize().x, window.getSize().y),
            &window);

    sf::RectangleShape rangeRect(sf::Vector2f(100, 100));
    rangeRect.setFillColor(sf::Color(0, 0, 0, 0));
    rangeRect.setOutlineThickness(1);
    rangeRect.setOutlineColor(sf::Color::Green);
    rangeRect.setOrigin(rangeRect.getSize().x / 2, rangeRect.getSize().y / 2);
    std::vector<sf::Transformable*> found;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.key.code == sf::Keyboard::Escape ||
                event.type == sf::Event::Closed) {
                window.close();
            }

            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R) {
                rectMouse = !rectMouse;
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                addDots(window, dotVector, q);
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                removeDots(dotVector);
                window.clear(sf::Color::Black);
            }
        }
        rangeRect.setPosition(sf::Mouse::getPosition(window).x,
                              sf::Mouse::getPosition(window).y);
        window.clear(sf::Color::Black);
        for (sf::CircleShape* d : dotVector) {
            window.draw(*d);
        }
        q.draw();
        if (rectMouse) {
            window.setMouseCursorVisible(false);
            window.draw(rangeRect);
            auto tempfound = q.query(rangeRect.getGlobalBounds(), found);

            //debug
            std::cout << "In range: " << tempfound.size() << "\n";

            for (auto p : tempfound) {
                sf::CircleShape c(2);
                c.setPosition(p->getPosition());
                c.setFillColor(sf::Color::Blue);
                window.draw(c);
            }
        } else {
            window.setMouseCursorVisible(true);
        }

        found.clear();
        window.display();
    }
}

void addDots(sf::RenderWindow& window, std::vector<sf::CircleShape*>& vec,
             QTree& qtree) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::CircleShape* circle = new sf::CircleShape(2);
    circle->setPosition(mousePos.x, mousePos.y);
    circle->setFillColor(sf::Color::White);
    vec.push_back(circle);
    qtree.insert(*circle);
}

int myRand(int pos) { return pos + (rand() % 20 - 10); }

void removeDots(std::vector<sf::CircleShape*>& vec) { vec.clear(); }
