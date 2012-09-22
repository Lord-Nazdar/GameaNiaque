#include "layermanager.h"

LayerManager::LayerManager() : sf::Group() {}

void LayerManager::drawSingleLayer(sf::RenderTarget& target, int index) const
{
    target.draw(*at(index));
}
