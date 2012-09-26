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

void Layer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Group::draw(target, states);
}

void Layer::setBackgroundColor(sf::Color color){

}

void Layer::move(float speed, int direction){
	/*Group::move(sf::Vector2f((speed*cos(direction*PI/180))*parallaxSpeed,(speed*sin(direction*PI/180))*parallaxSpeed));
	std::cout << "moving speed " << speed << " moving direction " << direction << " parallax " << parallaxSpeed << std::endl;
	std::cout << "x:" << (speed*cos(direction*PI/180))*parallaxSpeed << " y:" << (speed*sin(direction*PI/180))*parallaxSpeed << std::endl;*/
	Group::setPosition(100.f,100.f);
}
