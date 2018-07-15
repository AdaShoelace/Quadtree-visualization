#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include "gridrectangle.h"

template <typename T>
class QTree {
   public:
    QTree(int capacity, sf::Rect<int> boundary, sf::RenderWindow *window)
        : capacity(capacity), boundary(boundary), window(window) {
        std::cout << "Boundary width: " << boundary.width
                  << " Boundary height: " << boundary.height << std::endl;
    }

    void insert(T obj) {
        if (objList.size() < capacity) {
            objList.push_back(obj);
            return;
        } else if (!divided) {
            subdivide();
            divided = true;
        }
        nw->insert(obj);
        ne->insert(obj);
        sw->insert(obj);
        se->insert(obj);
    }

    // debug only
    void draw() {
        if (nw != NULL) {
            nw->draw();
        }
        if (ne != NULL) {
            ne->draw();
        }
        if (sw != NULL) {
            sw->draw();
        }
        if (se != NULL) {
            se->draw();
        }

        GridRectangle gridRect(window->getSize().x - boundary.width,
                               window->getSize().y - boundary.height,
                               boundary.width, boundary.height);
        /*if(!isDrawn) {
            std::cout << "Boundary width: " << boundary.width << "\n"
                "Boundary height: " << boundary.height << "\n"
                "GridRectangle x: " << gridRect.getPosition().x << "\n"
                "GridRectangle y: " << gridRect.getPosition().y;
            isDrawn = true;
        }*/
        window->draw(gridRect);
    }

   private:
    bool isDrawn = false;
    bool divided = false;
    unsigned int capacity;
    sf::Rect<int> boundary;
    sf::RenderWindow *window;
    std::vector<T> objList;
    QTree<T> *nw = NULL;
    QTree<T> *ne = NULL;
    QTree<T> *sw = NULL;
    QTree<T> *se = NULL;

    void subdivide() {
        int halfWidth = boundary.width * 0.5;
        int halfHeight = boundary.height * 0.5;

        sf::Rect<int> nwBoundary(0, 0, halfWidth, halfHeight);
        nw = new QTree(capacity, nwBoundary, window);

        sf::Rect<int> neBoundary(halfWidth, 0, halfWidth, halfHeight);
        ne = new QTree(capacity, neBoundary, window);

        sf::Rect<int> swBoundary(0, halfHeight, halfWidth, halfHeight);
        sw = new QTree(capacity, swBoundary, window);

        sf::Rect<int> seBoundary(halfWidth, halfHeight, halfWidth, halfHeight);
        se = new QTree(capacity, seBoundary, window);
    }

    std::vector<T *> query() {}

    void clean() {
        // recursive clean up (dfs)
    }
};
