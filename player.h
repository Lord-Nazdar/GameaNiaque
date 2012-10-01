#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics.hpp"

class Player
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
	sf::Texture texture;
	sf::Sprite sprite;

private:
	float speed;
	int direction;
	Style style;	//Style of the virus (3 values):icosahedral;helical;complex


};

#endif // PLAYER_H
