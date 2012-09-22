#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "layer.h"

class LayerManager : public sf::Group
{
public:
	LayerManager();
    void drawSingleLayer(sf::RenderTarget& target, int index) const;
};

#endif // LAYERMANAGER_H
