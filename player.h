#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics.hpp"
#include "animatedelement.h"

class Player : public AnimatedElement
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

    void accelerate(); // Accélère dans la direction pointée
    void turnRight(); // Sens horaire
    void turnLeft(); // Sens anti-horaire
	float getVelocity();
	void setStyle(int pStyle);
	int getStyle();
	float velocity;
	float reproduction;
	float resistance;

	AnimatedElement *player;

private:
	Style style;	//Style of the virus (3 values):icosahedral;helical;complex

};

#endif // PLAYER_H
