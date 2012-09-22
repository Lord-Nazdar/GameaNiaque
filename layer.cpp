#include "layer.h"
#include <iostream>

Layer::Layer()
{
}

Layer::Layer(int PZIndex)
{
	ZIndex=PZIndex;
}

int Layer::getZIndex(){
	return ZIndex;
}

void Layer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    std::cout << size() << std::endl;

    Group::draw(target, states);
}

void Layer::setBackgroundColor(sf::Color color){

}
