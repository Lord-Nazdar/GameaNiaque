#include <iostream>
#include <SFML/Graphics.hpp>

#include "gamestep.h"
#include "textures.h"

using namespace std;

void case1(GameStep gamestep);
void case2(GameStep gamestep);

int main()
{
	cout << "v0.7.1" << endl;


	GameStep gamestep;
	gamestep.init();

	//Gamestep Logo apparences
	gamestep.logo();

	//Gamestep menu
	switch(gamestep.menu()){
		case 1:
			case1(gamestep);
		case 2:
			case2(gamestep);
		case 3:
			gamestep.step3();
		case 4:
			gamestep.step4();
			break;
		case 5:
			gamestep.generateur();
			break;
	}

	return 0;
}

void case1(GameStep gamestep){
	//Music maestro
	sf::Music menuMusic;
	//logoMusic=new sf::Music("logo.wav");
	menuMusic.openFromFile("music/part1.wav");
	menuMusic.play();
	menuMusic.setLoop(true);

	gamestep.prestep1();
	gamestep.step1();
	gamestep.step1int2();
}

void case2(GameStep gamestep){
	//Music maestro
	sf::Music menuMusic;
	//logoMusic=new sf::Music("logo.wav");
	menuMusic.openFromFile("music/part2.wav");
	menuMusic.play();
	menuMusic.setLoop(true);

	gamestep.step2();
}

