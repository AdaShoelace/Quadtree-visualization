#include "qtree.h"

QTree::QTree(int capacity, sf::FloatRect boundary, sf::RenderWindow* window)
    : capacity(capacity), boundary{boundary}, window(window) {
    shape.setPosition(boundary.left, boundary.top);
    shape.setSize(sf::Vector2f(boundary.width, boundary.height));
    shape.setFillColor(sf::Color(0, 0, 0, 0));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1);

    std::cout << "Boundary width: " << boundary.width
              << " Boundary height: " << boundary.height << std::endl;
}

QTree::~QTree() {
    if(divided) {
        delete nw;
        delete ne;
        delete sw;
        delete se;
    }
}

void QTree::insert(sf::Transformable obj) {
    if (!boundary.contains(obj.getPosition().x, obj.getPosition().y)) {
        return;
    }
    if (objList.size() < capacity) {
        objList.push_back(obj);
        return;
    } else {
        if (!divided) {
            subdivide();
        }
        nw->insert(obj);
        ne->insert(obj);
        sw->insert(obj);
        se->insert(obj);
    }
}

// debug only
void QTree::draw() {
    window->draw(shape);

    if (divided) {
        nw->draw();
        ne->draw();
        sw->draw();
        se->draw();
    }
}

void QTree::subdivide() {
    int halfWidth = boundary.width * 0.5;
    int halfHeight = boundary.height * 0.5;

    sf::FloatRect nwBoundary(boundary.left, boundary.top, halfWidth,
                             halfHeight);
    nw = new QTree(capacity, nwBoundary, window);

    sf::FloatRect neBoundary(boundary.left + halfWidth, boundary.top, halfWidth,
                             halfHeight);
    ne = new QTree(capacity, neBoundary, window);

    sf::FloatRect swBoundary(boundary.left, boundary.top + halfHeight,
                             halfWidth, halfHeight);
    sw = new QTree(capacity, swBoundary, window);

    sf::FloatRect seBoundary(boundary.left + halfWidth,
                             boundary.top + halfHeight, halfWidth, halfHeight);
    se = new QTree(capacity, seBoundary, window);
    divided = true;
    std::cout << "Subdividing!\n";
}

std::vector<sf::Transformable*> QTree::query(
    sf::FloatRect range, std::vector<sf::Transformable*>& found) {
    if (!((sf::FloatRect)boundary).intersects(range)) {
        return found;
    } else {
        for (auto& p : objList) {
            if (range.contains(p.getPosition().x, p.getPosition().y)) {
                found.push_back(&p);
            }
        }
    }

    if (divided) {
        nw->query(range, found);
        ne->query(range, found);
        sw->query(range, found);
        se->query(range, found);
    }
    return found;
}

void QTree::clear() {
    objList.clear();
    if (divided) {
        delete nw;
        delete ne;
        delete sw;
        delete se;
        divided = false;
    }
}

