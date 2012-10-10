#ifndef ELEMENT_H
#define ELEMENT_H

#include "SFML/Graphics.hpp"
#include <string>

class Element : public sf::Transformable
{
public:
	Element();
    Element(sf::Texture& pTex, sf::Vector2f pPos, float pOrientation);


    virtual void draw(sf::RenderWindow &window);
    virtual void update(int frame);

protected:
	sf::Sprite sprite;
};

#endif // ELEMENT_H
