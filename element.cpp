#include "element.h"
#include <iostream>

Element::Element()
{
}

Element::Element(std::string pDir){
	assignSprite(pDir);
	pos=sf::Vector2f(0,0);
}

Element::Element(std::string pDir, sf::Vector2f pPos, int pOrientation){
	assignSprite(pDir);
	pos=pPos;
	orientation=pOrientation%360;
	std::cout << pOrientation%360 << std::endl;
}

void Element::assignSprite(std::string pDir){
	texture.loadFromFile(pDir);
	sprite.setTexture(texture);
}

void Element::setPos(sf::Vector2f pPos){
	pos=pPos;
}

void Element::setRotation(int pOrientation){
	orientation=pOrientation%360;
}

void Element::draw(sf::RenderWindow &window){
	sprite.setPosition(pos);
	sprite.setRotation(orientation);
	window.draw(sprite);
}
