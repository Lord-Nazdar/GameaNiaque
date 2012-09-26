#ifndef LAYER_H
#define LAYER_H

#include <SFML/Graphics.hpp>
#include "group.h"

class Layer : public sf::Group
{
public:
	Layer();
	Layer(int PZIndex, float PParalaxSpeed);

	int getZIndex();
	void setBackgroundColor(sf::Color color);
    void draw(sf::RenderTarget& window, sf::RenderStates states) const;
	void move(float speed, int direction);

private:
	int ZIndex;
	float parallaxSpeed;
};

#endif // LAYER_H
