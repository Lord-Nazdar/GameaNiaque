#include "layermanager.h"

LayerManager::LayerManager()
{
	size=0;
	layerList = new Layer[2];
}

void LayerManager::addLayer(Layer *layer){
	size++;
	int *p;
	p = new int[12];
	p[0]=12;
	p[1]=1;
	bool assign=false;
	int j=0;
	Layer *provLayerList;
	provLayerList = new Layer[size];
	if(size>1){
		for(int i=0;i<size-1;i++)
		{
			if(layer->getZIndex()<layerList[i].getZIndex() && !assign){
				provLayerList[i]=*layer;
				assign=true;
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
