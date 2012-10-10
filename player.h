#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics.hpp"
#include "element.h"

class Player : public Element
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

private:
	Style style;	//Style of the virus (3 values):icosahedral;helical;complex
    sf::Vector2f velocity;


};

#endif // PLAYER_H
