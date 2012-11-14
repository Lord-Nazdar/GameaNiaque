#include <iostream>
#include <SFML/Graphics.hpp>

#include "gamestep.h"
#include "textures.h"

using namespace std;

bool case1(GameStep *gamestep);
bool case2(GameStep *gamestep);

int main()
{
	cout << "v0.7.1" << endl;


	GameStep gamestep;
	gamestep.init();

	//Gamestep Logo apparences
	gamestep.logo();


	int returnMenu=0;

	//Gamestep menu
	do{
		gamestep.step3();
		returnMenu=gamestep.menu();
		switch(returnMenu){
			case 1:
				gamestep.generateur();
				if(case1(&gamestep)){
					if(case2(&gamestep)){
						if(gamestep.step3()){
							gamestep.step4();
						}
					}
				}
				break;
				break;
			case 5:
				gamestep.generateur();
				break;
			case 6:
				gamestep.stepScore();
				break;
			case 7:
				gamestep.credit();
				break;
			case 8:
				gamestep.instruction();
				break;
		}
	}while(returnMenu!=10);

	return 0;
}

bool case1(GameStep *gamestep){
	//Music maestro
	sf::Music menuMusic;
	//logoMusic=new sf::Music("logo.wav");
	menuMusic.openFromFile("music/part1.wav");
	menuMusic.play();
	menuMusic.setLoop(true);

	if(gamestep->prestep1()){
		if(gamestep->step1()){
			if(gamestep->step1int2()){
				return true;
			}
		}
	}


	return false;
}

bool case2(GameStep *gamestep){
	//Music maestro
	sf::Music menuMusic;
	//logoMusic=new sf::Music("logo.wav");
	menuMusic.openFromFile("music/part2.wav");
	menuMusic.play();
	menuMusic.setLoop(true);

	if(gamestep->step2()){
		return true;
	}

	return false;
}
