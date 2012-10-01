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
	for(int i=0;i<spriteVector.size();i++){
		target.draw(*spriteVector[i]);
	}
}

void Layer::setBackgroundColor(sf::Color color){

}

void Layer::move(float speed, int direction){
	for(int i=0;i<spriteVector.size();i++){
		spriteVector[i]->move(sf::Vector2f((speed*cos(direction*PI/180))*parallaxSpeed,(speed*sin(direction*PI/180))*parallaxSpeed));
	}
}

void Layer::addSprite(sf::Sprite *sprite){
	spriteVector.push_back(sprite);
}
