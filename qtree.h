#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

class QTree {
   public:
    QTree(int capacity, sf::FloatRect boundary, sf::RenderWindow *window);
    void insert(sf::Transformable obj);
    void draw();     // debug only
    std::vector<sf::Transformable*> query(sf::FloatRect range, std::vector<sf::Transformable*>& found);

   private:
    bool divided = false;
    sf::RectangleShape shape;
    unsigned int capacity;
    sf::FloatRect boundary;
    sf::RenderWindow *window;
    std::vector<sf::Transformable> objList;
    QTree *nw = NULL;
    QTree *ne = NULL;
    QTree *sw = NULL;
    QTree *se = NULL;

    void subdivide();
    void clear();
};
