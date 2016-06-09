#pragma once
#include <SFML\Graphics.hpp>
struct Ship : public sf::Drawable
{
	Ship(int id,int x, int y, int s, bool r, sf::Texture *t);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(unsigned dt);
	void sync(int x, int y, int s, bool r);
	int id, x, y, s;
	bool r;
	bool updated;
	sf::Sprite sprite;
};

