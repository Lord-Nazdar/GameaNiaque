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

void Layer::draw(sf::RenderWindow &target, sf::RenderStates states)
{
    for(std::vector<Element*>::iterator i = elementVector.begin(); i != elementVector.end(); i++){
		(*i)->draw(target);
	}
}

void Layer::setBackgroundColor(sf::Color color){

}

void Layer::moveTo(int frame, sf::Vector2f pTo, int duration, int id){
        //elementVector[id]->movingTo(frame ,pTo, duration);
}

void Layer::addElement(Element *element){
	elementVector.push_back(element);
}

void Layer::erase(unsigned int pos){
	elementVector.erase(elementVector.begin()+pos);
}

void Layer::clear(){
	elementVector.clear();
}

void Layer::removeElement(Element *element){
	//elementVector.erase(element);
}

void Layer::update(int frame){
	for(std::vector<Element*>::iterator i = elementVector.begin(); i != elementVector.end(); i++){
		(*i)->update(frame);
	}
}
