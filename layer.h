#ifndef LAYER_H
#define LAYER_H

#include <SFML/Graphics.hpp>
#include "group.h"

class Layer : public sf::Group
{
public:
	Layer();
	Layer(int PZIndex);

	int getZIndex();
	void setBackgroundColor(sf::Color color);
    void draw(sf::RenderTarget& window, sf::RenderStates states) const;

private:
	int ZIndex;
};

#endif // LAYER_H
