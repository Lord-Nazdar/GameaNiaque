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
	AnimatedElement player(Texture("grid.png"), sf::Vector2f(((width/2)-300)+20,(((height/2)-520)+pos*130)+20), 0.f, 64, 1, type*8);

	player.draw(window);

	if(pos%2){
		sf::RectangleShape top(sf::Vector2f(width*2, 130));
		top.setFillColor(sf::Color(0,0,0,50));
		top.setPosition(sf::Vector2f(0,(((height/2)-500)+pos*130)-35));

		window.draw(top);
	}

	//Texte
	sf::Font Arial = Font("pixelart.ttf");

	sf::Text nameR;
	nameR.setFont(Arial);
	nameR.setCharacterSize(30);
	nameR.setColor(sf::Color::Black);
	nameR.setPosition(sf::Vector2f(((width/2)-190),(((height/2)-520)+pos*130)+35));
	nameR.setString(name);
	window.draw(nameR);

	sf::Text scoreR;
	scoreR.setFont(Arial);
	scoreR.setCharacterSize(30);
	scoreR.setColor(sf::Color::Black);
	scoreR.setPosition(sf::Vector2f(((width/2)+260),(((height/2)-520)+pos*130)+35));
	scoreR.setString(toString(score));
	window.draw(scoreR);

	sf::Text tempsR;
	tempsR.setFont(Arial);
	tempsR.setCharacterSize(30);
	tempsR.setColor(sf::Color::Black);
	tempsR.setPosition(sf::Vector2f(((width/2))+410,(((height/2)-520)+pos*130)+35));
	tempsR.setString(temps);
	window.draw(tempsR);

	sf::Text playerR;
	playerR.setFont(Arial);
	playerR.setCharacterSize(30);
	playerR.setColor(sf::Color::Black);
	playerR.setPosition(sf::Vector2f(((width/2)+560),(((height/2)-520)+pos*130)+35));
	playerR.setString(playerName);
	window.draw(playerR);
}
