#ifndef GAMESTEP_H
#define GAMESTEP_H

#include "SFML/Graphics.hpp"

#include "layer.h"
#include "layermanager.h"
#include "player.h"

//#include "movableelement.h"

class GameStep
{
public:
	GameStep();
	void init();
	int menu();
	void pauseMenu();
	bool logo();
	bool step1();
	bool step1int2();
	bool step2();
	bool step3();
	bool step4();
	void stepEvent();
	int step3Mouse(std::vector<Element*> element);
private:
	sf::RenderWindow *window;
	int frame;
	int height;
	int width;
	bool mouseButtonDown;
	int score;
	Player *player;
};

#endif // GAMESTEP_H
