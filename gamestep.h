#ifndef GAMESTEP_H
#define GAMESTEP_H

#include "SFML/Graphics.hpp"

#include "layer.h"
#include "layermanager.h"
#include "player.h"

#include "movableelement.h"

class GameStep
{
public:
	GameStep();
	void init();
	int menu();
	void pauseMenu();
	bool step1();
	bool step2();
	bool step3();
	bool step4();
private:
	sf::RenderWindow *window;
	int frame;
	int height;
	int width;
};

#endif // GAMESTEP_H
