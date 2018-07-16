#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

class QTree {
   public:
    QTree(int capacity, sf::Rect<int> boundary, sf::RenderWindow *window);
    void insert(sf::Transformable obj);
    void draw();     // debug only

   private:
    bool divided = false;
    sf::RectangleShape shape;
    unsigned int capacity;
    sf::Rect<int> boundary;
    sf::RenderWindow *window;
    std::vector<sf::Transformable> objList;
    QTree *nw = NULL;
    QTree *ne = NULL;
    QTree *sw = NULL;
    QTree *se = NULL;

    void subdivide();
    std::vector<sf::Transformable *> query();
    void clean();
};
