#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include "layer.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class LayerManager
{
public:
	LayerManager();
	void addLayer(Layer *layer);
	void renderLayer(sf::RenderWindow &window);
	void renderLayer(sf::RenderWindow &window, int *tablayer); //render with layer choice
private:
	Layer *layerList;
	int size;
};

#endif // LAYERMANAGER_H
