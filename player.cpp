#include "player.h"

Player::Player()
{
}

Player::Player(Style type){
	style=type;
	switch(style){
		case 0:
		texture.loadFromFile("icosahedral.png");
		sprite.setTexture(texture);
		sprite.setPosition(sf::Vector2f(400,300));
	}
}

void Player::setSpeed(float value){
//	speed=value;
}

float Player::getSpeed(){
//	return speed;
}

void Player::setDirection(int value){
	//direction=value;
}

int Player::getDirection(){
	//return direction;
}

void Player::incDirection(){
	/*direction++;
	if(direction==360)
		direction=0;*/
}

void Player::decDirection(){
	/*direction--;
	if(direction==-1)
		direction=359;*/
}
