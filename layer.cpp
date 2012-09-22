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

void Layer::render(sf::RenderWindow &window){
	std::cout << group.size() << std::endl;
	group.draw(window,sf::RenderStates::Default);
}

void Layer::setBackgroundColor(sf::Color color){

}

void Layer::addDrawable(sf::Drawable *drawable){
	/*sf::CircleShape *shape;
	shape = new sf::CircleShape(100.f);
	shape->setFillColor(sf::Color::Green);*/
	group.push_back(drawable);
	std::cout << group.size() << std::endl;
	//group.draw(window,sf::RenderStates::Default);
}
