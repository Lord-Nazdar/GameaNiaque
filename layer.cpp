#include "layer.h"

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
