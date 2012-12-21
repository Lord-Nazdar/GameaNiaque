#ifndef ELEMENT_H
#define ELEMENT_H

#include <SFML/Graphics.hpp>
#include <string>

class Element : public sf::Transformable
{
public:
	Element();
    Element(sf::Texture& pTex, sf::Vector2f pPos = sf::Vector2f(0, 0), float pDir = 0.f);
	Element(sf::Sprite& pSprite);


    virtual void draw(sf::RenderWindow &window);
    virtual void update(int frame);

	void setColor(sf::Color color);

//protected:
	sf::Sprite sprite;
};

#endif // ELEMENT_H
