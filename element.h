#ifndef ELEMENT_H
#define ELEMENT_H

#include "SFML/Graphics.hpp"
#include <string>

class Element
{
public:
	Element();
	Element(std::string pDir);
	Element(std::string pDir, sf::Vector2f pPos, int pOrietation);
	void assignSprite(std::string pDir);
	void setPos(sf::Vector2f pPos);
	void setRotation(int pOrientation);
	void draw(sf::RenderWindow &window);
	void update(int frame);
protected:
	sf::Vector2f pos;
	int orientation;
	sf::Texture texture;
	sf::Sprite sprite;
};

#endif // ELEMENT_H
