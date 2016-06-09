#include "Ship.h"



Ship::Ship(int id, int x, int y, int s, bool r, sf::Texture *t)
{
	sprite.setTexture(*t);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setScale(0.2f, 0.2f);
	this->id = id;
	this->x = x;
	this->y = y;
	this->s = s;
	this->r = r;
	sprite.setPosition((float)x, (float)y);
}

void Ship::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);
}

void Ship::update(unsigned dt)
{
	int dir = (r) ? 1 : -1;
	int nx = x + 5 * dir;
	if (nx<50 || nx>750) {
		r = !r;
		dir = (r) ? 1 : -1;
		nx = x + 5 * dir;
	}
	x = nx;
	sprite.setPosition((float)x, (float)y);
}

void Ship::sync(int x, int y, int s, bool r)
{
	this->x = x;
	this->y = y;
	this->s = s;
	this->r = r;
	sprite.setPosition((float)x, (float)y);
}
