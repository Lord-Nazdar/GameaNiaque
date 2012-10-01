#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "layer.h"

class LayerManager : public std::vector<Layer>
{
public:
	LayerManager();
	void drawSingleLayer(sf::RenderWindow &target, int index) const;
	void move(float speed, int direction);
	void add(Layer* layer);
	void draw(sf::RenderWindow& target);
private:
	std::vector<Layer*> layerVector;
};

#endif // LAYERMANAGER_H
