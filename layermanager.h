#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include "layer.h"

class LayerManager
{
public:
	LayerManager();
	void addLayer(Layer *layer);
private:
	Layer *layerList;
	int size;
};

#endif // LAYERMANAGER_H
