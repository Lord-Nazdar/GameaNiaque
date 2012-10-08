#include "layer.h"
#include <iostream>
#include <math.h>

#define PI 3.14159265

Layer::Layer()
{
}

Layer::Layer(int PZIndex, float PParalaxSpeed)
{
	ZIndex=PZIndex;
	parallaxSpeed=PParalaxSpeed;
}

int Layer::getZIndex(){
	return ZIndex;
}

void Layer::draw(sf::RenderWindow &target, sf::RenderStates states) const
{
	for(int i=0;i<elementVector.size();i++){
		elementVector[i]->draw(target);
	}
}

void Layer::setBackgroundColor(sf::Color color){

}

void Layer::moveTo(int frame, sf::Vector2f pTo, int duration, int id){
		elementVector[id]->movingTo(frame ,pTo, duration);
}

void Layer::addElement(MovableElement *element){
	elementVector.push_back(element);
}

void Layer::update(int frame){
	for(int i=0;i<elementVector.size();i++){
		elementVector[i]->update(frame);
	}
}
