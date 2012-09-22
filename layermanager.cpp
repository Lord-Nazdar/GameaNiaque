#include "layermanager.h"


LayerManager::LayerManager()
{
	size=0;
	layerList = new Layer[2];
}

void LayerManager::addLayer(Layer *layer){
	size++;
	bool assign=false;
	int j=0;
	Layer *provLayerList;
	provLayerList = new Layer[size];
	if(size>1){
		for(int i=0;i<size;i++)
		{
			if(layer->getZIndex()<layerList[i].getZIndex() && !assign){
				provLayerList[i]=*layer;
				assign=true;
			}
			else if(i==size && !assign)
			{
				provLayerList[i]=*layer;
			}
			else{
				provLayerList[i]=layerList[j];
				j++;
			}

		}
	}
	else
		provLayerList[0]=*layer;

	delete[] layerList;
	layerList = new Layer[size];
	for(int i=0;i<size;i++)
	{
		layerList[i]=provLayerList[i];
	}
}

void LayerManager::renderLayer(sf::RenderWindow &window){
	for(int i=0;i<size;i++)
	{
		/*sf::CircleShape shape(100.f);
		shape.setFillColor(sf::Color::Green);
		layerList[i].addDrawable(&shape);*/
		layerList[i].render(window);
	}
}

void LayerManager::renderLayer(sf::RenderWindow &window, int *tablayer){
	for(int i=0;i<sizeof(tablayer);i++){
		layerList[tablayer[i]].render(window);
	}
}
