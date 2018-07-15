#include "gridrectangle.h"

GridRectangle::GridRectangle(int originX, int originY, int width, int height) {
    this->setPosition(originX, originY);

    //set sizes
    left.setSize(sf::Vector2f(lineWidth, height));
    right.setSize(sf::Vector2f(lineWidth, height));
    upper.setSize(sf::Vector2f(width, lineWidth));
    lower.setSize(sf::Vector2f(width, lineWidth));

    //set positions
    left.setPosition(originX, originY);
    right.setPosition(originX + width - lineWidth, originY);
    upper.setPosition(originX, originY);
    lower.setPosition(originX, originY + height - lineWidth);

    //set colors
    left.setFillColor(sf::Color::White);
    right.setFillColor(sf::Color::White);
    upper.setFillColor(sf::Color::White);
    lower.setFillColor(sf::Color::White);
}


void GridRectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(left, states);
    target.draw(right, states);
    target.draw(upper, states);
    target.draw(lower, states);
}

