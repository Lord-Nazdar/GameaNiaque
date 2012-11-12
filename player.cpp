#include "player.h"
#include "textures.h"

Player::Player()
{
	player=new AnimatedElement(Texture("grid.png"), sf::Vector2f(0,0), 0.f, 64, 1, 0);
}

Player::Player(Style type){
	style=type;
	sf::Vector2f pos (0,0);
	switch(style){
	case 0:
		player=new AnimatedElement(Texture("grid.png"), pos, 0.f, 64, 1, 0);
		this->velocity=8;
		break;
	case 1:
		player=new AnimatedElement(Texture("grid.png"), pos, 0.f, 64, 1, 8);
		this->velocity=7;
		break;
	case 2:
		player=new AnimatedElement(Texture("grid.png"), pos, 0.f, 64, 2, 16);
		this->velocity=10;
		break;
	}
}

void Player::accelerate()
{

}

void Player::turnRight()
{

}

void Player::turnLeft()
{


}

float Player::getVelocity()
{
	return velocity;
}

void Player::setStyle(int pStyle){
	style=((Style)pStyle);
	sf::Vector2f pos=player->getPosition();
	switch(style){
	case 0:
		player=new AnimatedElement(Texture("grid.png"), pos, 0.f, 64, 1, 0);
		break;
	case 1:
		player=new AnimatedElement(Texture("grid.png"), pos, 0.f, 64, 1, 8);
		break;
	case 2:
		player=new AnimatedElement(Texture("grid.png"), pos, 0.f, 64, 2, 16);
		break;
	}
}

int Player::getStyle(){
	return (int)style;
}
