#include <iostream>
#include <SFML/Graphics.hpp>

#include "gamestep.h"
#include "textures.h"

using namespace std;

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
			gamestep.step1();
			gamestep.step1int2();
		case 2:
			gamestep.step2();
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


