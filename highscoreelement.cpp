#include "highscoreelement.h"


HighScoreElement::HighScoreElement(int ptype, string pname, int pscore, string ptemps, string pplayerName, int ppos, int pheight, int pwidth)
{
	type=ptype;
	name=pname;
	score=pscore;
	temps=ptemps;
	playerName=pplayerName;
	pos=ppos;
	height=pheight;
	width=pwidth;
}

void HighScoreElement::draw(sf::RenderWindow &window){
	Element cadre(Texture("cadre.png"), sf::Vector2f(((width/2)-300),(((height/2)-520)+pos*130)), 0.f);
	cadre.draw(window);
	AnimatedElement player(Texture("grid.png"), sf::Vector2f(((width/2)-300)+20,(((height/2)-520)+pos*130)+20), 0.f, 64, 1, type*8);


	player.draw(window);

	//Texte
	sf::Font Arial = Font("pixelart.ttf");

	sf::Text nameR;
	nameR.setFont(Arial);
	nameR.setCharacterSize(40);
	nameR.setColor(sf::Color(100,100,100));
	nameR.setPosition(sf::Vector2f(((width/2)-190),(((height/2)-520)+pos*130)+25));
	nameR.setString(name);
	window.draw(nameR);

	sf::Text scoreR;
	scoreR.setFont(Arial);
	scoreR.setCharacterSize(40);
	scoreR.setColor(sf::Color(100,100,100));
	scoreR.setPosition(sf::Vector2f(((width/2)+260),(((height/2)-520)+pos*130)+25));
	scoreR.setString(intTostring(score));
	window.draw(scoreR);

	sf::Text tempsR;
	tempsR.setFont(Arial);
	tempsR.setCharacterSize(40);
	tempsR.setColor(sf::Color(100,100,100));
	tempsR.setPosition(sf::Vector2f(((width/2))+410,(((height/2)-520)+pos*130)+25));
	tempsR.setString(temps);
	window.draw(tempsR);

	sf::Text playerR;
	playerR.setFont(Arial);
	playerR.setCharacterSize(40);
	playerR.setColor(sf::Color(100,100,100));
	playerR.setPosition(sf::Vector2f(((width/2)+560),(((height/2)-520)+pos*130)+25));
	playerR.setString(playerName);
	window.draw(playerR);
}
