#include "layermanager.h"

#define PI 3.14159265

LayerManager::LayerManager(){}

void LayerManager::drawSingleLayer(sf::RenderWindow& target, int index) const
{
	layerVector.at(index)->draw(target,sf::RenderStates::Default);
}

void LayerManager::move(float speed, int direction){
	for(unsigned int i=0;i<layerVector.size();i++){
		layerVector.at(i)->move(speed,direction);
	}
}

void LayerManager::move(float speed, int direction, float state){
	for(unsigned int i=0;i<layerVector.size();i++){
		layerVector.at(i)->move(speed*(1-sin(PI/2+state*PI))/2,direction);
	}
}

void LayerManager::draw(sf::RenderWindow& target){
	for(unsigned int i=0;i<layerVector.size();i++){
		layerVector.at(i)->draw(target,sf::RenderStates::Default);
	}
}

void LayerManager::add(Layer *layer){
	layerVector.push_back(layer);
}
