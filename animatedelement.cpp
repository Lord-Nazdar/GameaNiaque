#include "animatedelement.h"
#include <iostream>
#include <math.h>

AnimatedElement::AnimatedElement() : Element()
{

}

AnimatedElement::AnimatedElement(sf::Texture& pTex, sf::Vector2f pPos = sf::Vector2f(0, 0), float pDir = 0.f, int pFrameSize = 64, int pMaxFrames = 1, int pstartframe = 0) : Element()
{
	sprite.setTexture(pTex);
	setPosition(pPos);
	setRotation(pDir);
	frameSize = pFrameSize;
	maxFrames = pMaxFrames;
	startframe = pstartframe;
	frameIndex = 0;
	setFrame(0);
}


void AnimatedElement::update(int frame)
{
	if(frame%20 == 0)
	{
		setFrame(frameIndex);
		frameIndex++;
	}
}

void AnimatedElement::draw(sf::RenderWindow& window)
{
	Element::draw(window);
}

void AnimatedElement::setFrame(int frame)
{
	//std::cout << frame << std::endl;

	sf::Vector2u size = sprite.getTexture()->getSize();
	int framesPerLine = size.x/frameSize;
	frame = frame % maxFrames;
	int u = frame % framesPerLine;
	int v = frame / framesPerLine;

	//std::cout << (startframe*frameSize)+(u*frameSize) << ";" << ((floor(startframe/framesPerLine))*frameSize)+(v*frameSize) << std::endl;

	sprite.setTextureRect(sf::IntRect((floor(startframe%framesPerLine)*frameSize)+(u*frameSize), ((floor(startframe/framesPerLine))*frameSize)+(v*frameSize), frameSize, frameSize));
}

