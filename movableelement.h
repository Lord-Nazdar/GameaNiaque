/*
#ifndef MOVABLEELEMENT_H
#define MOVABLEELEMENT_H

#include "element.h"

class MovableElement : public Element
{
public:
	MovableElement();
    MovableElement(std::string filename, sf::Vector2f pPos, int pOrientation);
	void update(int frame);
	void updateAnim(int frame);
	void updatePos(int frame);
	void movingTo(int frame, sf::Vector2f pTo, int pDuration);
protected:
	int thrust;
	sf::Vector2f startPos;
	sf::Vector2f posTo;
	int movingToDuration;
	int movingToStartTime;
};

#endif // MOVABLEELEMENT_H
*/
