#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics.hpp"
#include "movableelement.h"

class Player : public MovableElement
{
public:
	enum Style
	{
		icosahedral,
		helical,
		complex
	};

	Player();
	Player(Style type);
	void setSpeed(float value);
	float getSpeed();
	void setDirection(int value);
	int getDirection();
	void incDirection();
	void decDirection();

private:
	Style style;	//Style of the virus (3 values):icosahedral;helical;complex


};

#endif // PLAYER_H
