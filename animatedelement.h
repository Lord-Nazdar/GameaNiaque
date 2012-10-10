/*
#ifndef ANIMATEDELEMENT_H
#define ANIMATEDELEMENT_H

#include "SFML/Graphics.hpp"
#include <string>

class AnimatedElement : public Element
{
public:
	Element();
    Element(sf::Texture pTex, sf::Vector2f pPos, float pOrientation);


    virtual void draw(sf::RenderWindow &window);
    virtual void update(int frame);

protected:
	sf::Sprite sprite;
};

#endif // ANIMATEDELEMENT_H
*/
