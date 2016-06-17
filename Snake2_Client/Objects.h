#pragma once
#include <PROTO\Protocol.h>
#include <SFML\Graphics.hpp>
#include "Food.h"

class Objects : public sf::Drawable
{
public:
	std::vector<Food*> food;
	Objects(Part *food, int size);
	~Objects();
	void sync(Part *food, int size);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

