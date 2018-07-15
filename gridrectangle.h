#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GridRectangle : public sf::Drawable, public sf::Transformable {
    public:
        GridRectangle(int originX, int originY, int width, int height);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        const int lineWidth = 5;
        sf::Vector2i origin;
        sf::RectangleShape left, right, upper, lower;
};
