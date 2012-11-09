#ifndef GAMESTEP_H
#define GAMESTEP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <time.h>
#include <math.h>
#include <sstream>

#include "textures.h"
#include "music.h"
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
	void instruction();
	bool generateur();
	bool logo();
	bool prestep1();
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
	int red;
};

float moveTo (int frame, float posFrom, float posTo, float duration);
std::string intTostring(int nb);

#endif // GAMESTEP_H
