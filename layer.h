#ifndef LAYER_H
#define LAYER_H

#include <SFML/Graphics.hpp>
#include "group.h"

class Layer
{
public:
	Layer();
	Layer(int PZIndex);
	int getZIndex();
	void render(sf::RenderWindow &window);
	void setBackgroundColor(sf::Color color);
	void addDrawable(sf::Drawable *drawable);
	void addDrawable(sf::Sprite *drawable);
	void addDrawable(sf::Text *drawable);
	void addDrawable(sf::VertexArray *drawable);

private:
	int ZIndex;
	Group group;
};

#endif // LAYER_H
