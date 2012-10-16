#include "element.h"
#include <iostream>

Element::Element()
{

}

Element::Element(sf::Texture& pTex, sf::Vector2f pPos = sf::Vector2f(0, 0), float pDir = 0.f)
{
    sprite.setTexture(pTex);
    setPosition(pPos);
    setRotation(pDir);
}

Element::Element(sf::Sprite &pSprite){
	sprite=pSprite;
}

void Element::draw(sf::RenderWindow &window)
{
    sprite.setPosition(getPosition());
    sprite.setRotation(getRotation());
	sprite.setOrigin(getOrigin());
	sprite.setScale(getScale());
	window.draw(sprite);
}

void Element::update(int frame)
{

}

void Element::setColor(sf::Color color){
	sprite.setColor(color);
}
