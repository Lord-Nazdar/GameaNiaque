#include "group.h"


Group::Group() :
	sf::Drawable(),
	std::vector<sf::Drawable*>() {
}
Group::~Group() {
	for(std::vector<sf::Drawable*>::iterator i = begin(); i != end(); ++i) {
		delete *i;
	}
}

// This is what ables you to do Group.Draw() to draw all the Drawable inside of a Group,
// and to apply common settings such as position, color, ... to its elements.
void Group::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for(std::vector<sf::Drawable*>::const_iterator i = begin(); i != end(); ++i) {
		target.draw(**i,states);
	}
}
