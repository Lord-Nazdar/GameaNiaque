#include "player.h"
#include "textures.h"

Player::Player()
{
}

Player::Player(Style type){
	style=type;
	switch(style){
		case 0:
        sprite.setTexture(Texture("icosahedral.png"));
		sprite.setPosition(sf::Vector2f(400,300));
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
