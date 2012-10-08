#ifndef LAYER_H
#define LAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "movableelement.h"

class Layer
{
public:
	Layer();
	Layer(int PZIndex, float PParalaxSpeed);

	int getZIndex();
	void setBackgroundColor(sf::Color color);
	void draw(sf::RenderWindow &window, sf::RenderStates states) const;
	void moveTo(int frame, sf::Vector2f pTo, int duration, int id);
	void addElement(MovableElement *element);
	void update(int frame);

private:
	int ZIndex;
	float parallaxSpeed;
	std::vector<MovableElement*> elementVector;
};

#endif // LAYER_H
