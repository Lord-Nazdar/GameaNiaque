#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>

#include "layer.h"

class LayerManager
{
public:
	LayerManager();
	void drawSingleLayer(sf::RenderWindow &target, int index) const;
	void move(float speed, int direction);
	void move(float speed, int direction, float state);
	void add(Layer* layer);
	void draw(sf::RenderWindow& target);
	void update(int frame);
private:
	std::vector<Layer*> layerVector;
};

#endif // LAYERMANAGER_H
