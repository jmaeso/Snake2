#pragma once

#include <PROTO\Protocol.h>
#include <SFML\Graphics.hpp>
#include "const.h"

class Food : public sf::Drawable
{
public:
	Food(int x, int y);
	~Food();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Sprite sprite;
	sf::Texture texture;
};

