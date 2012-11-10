#ifndef HIGHSCOREELEMENT_H
#define HIGHSCOREELEMENT_H

#include <string>
#include "element.h"
#include "animatedelement.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include "textures.h"
#include "gamestep.h"

using namespace std;

class HighScoreElement
{
public:
	HighScoreElement(int ptype, string pname, int pscore, string ptemps, string pplayerName, int ppos, int pheight, int pwidth);
	void draw(sf::RenderWindow &window);
private:
	int type;
	string name;
	int score;
	string temps;
	string playerName;
	int pos;
	int height;
	int width;
};

#endif // HIGHSCOREELEMENT_H
