#include "animatedelement.h"
#include <iostream>

AnimatedElement::AnimatedElement() : Element()
{

}

AnimatedElement::AnimatedElement(sf::Texture& pTex, sf::Vector2f pPos = sf::Vector2f(0, 0), float pDir = 0.f, int pFrameSize = 64, int pMaxFrames = 1) : Element()
{
	sprite.setTexture(pTex);
	setPosition(pPos);
	setRotation(pDir);
	frameSize = pFrameSize;
	maxFrames = pMaxFrames;
	frameIndex = 0;
}

void AnimatedElement::draw(sf::RenderWindow &window)
{
	sprite.setPosition(getPosition());
	sprite.setRotation(getRotation());
	window.draw(sprite);
}

void AnimatedElement::update(int frame)
{
	if(frame%20 == 0)
	{
		setFrame(frameIndex);
		frameIndex++;
	}
}

void AnimatedElement::setFrame(int frame)
{
	std::cout << frame << std::endl;

	sf::Vector2u size = sprite.getTexture()->getSize();
	int framesPerLine = size.x/frameSize;
	frame = frame % maxFrames;
	int u = frame % framesPerLine;
	int v = frame / framesPerLine;

	sprite.setTextureRect(sf::IntRect(u*frameSize, v*frameSize, frameSize, frameSize));
}

