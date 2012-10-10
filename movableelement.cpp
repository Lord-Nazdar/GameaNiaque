/*
#include "movableelement.h"

float easeInOutQuad(float t, float b, float c, int d){
	t /= d/2;
	if (t < 1) return c/2*t*t + b;
	t--;
	return -c/2 * (t*(t-2) - 1) + b;
}

MovableElement::MovableElement()
{
}

MovableElement::MovableElement(std::string filename, sf::Vector2f pPos, int pOrientation):Element(filename,pPos,pOrientation)
{

}

void MovableElement::update(int frame){
	updateAnim(frame);
	if(movingToDuration>0){
		updatePos(frame);
	}
}

void MovableElement::updatePos(int frame){
	sf::Vector2f provPos;
	provPos.x=easeInOutQuad(frame-movingToStartTime,startPos.x,posTo.x-startPos.x,movingToDuration);
	provPos.y=easeInOutQuad(frame-movingToStartTime,startPos.y,posTo.y-startPos.y,movingToDuration);
	this->setPos(provPos);
	if(frame-movingToStartTime==movingToDuration) movingToDuration=0;
}

void MovableElement::updateAnim(int frame){

}

void MovableElement::movingTo(int frame, sf::Vector2f pTo, int pDuration){
	startPos=pos;
	posTo=pTo;
	movingToDuration=pDuration;
	movingToStartTime=frame;
}
*/
