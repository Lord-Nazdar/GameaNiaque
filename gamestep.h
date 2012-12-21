#ifndef GAMESTEP_H
#define GAMESTEP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <time.h>
#include <math.h>
#include <sstream>

#include "textures.h"
#include "fonts.h"
#include "layer.h"
#include "layermanager.h"
#include "player.h"
#include "highscoreelement.h"

//#include "movableelement.h"

class GameStep
{
public:
	GameStep();
	void init();
	int menu();
	bool pauseMenu();
	bool instruction();
	bool generateur();
	bool logo();
	bool prestep1();
	bool step1();
	bool step1int2();
	bool step2();
	bool step2int3();
	bool step3();
	bool step4();
	void stepEvent();
	bool stepScore();
	bool credit();
	static Player* player;
	bool talent();

private:
	sf::RenderWindow *window;
	int frame;
	int height;
	int width;
	bool mouseButtonDown;
	int score;
	int red;
	int tier;
	std::vector<Element*> white1;
	std::vector<Element*> white2;
};

float moveTo (int frame, float posFrom, float posTo, float duration);
template <typename T>
std::string toString(T nb){
	std::ostringstream oss;
	oss << nb;
	return oss.str();
}

#endif // GAMESTEP_H
