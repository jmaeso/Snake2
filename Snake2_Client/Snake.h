#pragma once
#include <SFML\Graphics.hpp>
#include "Parts.h"
#include <vector>
#include <PROTO\Protocol.h>

struct Snake : public sf::Drawable
{
	Snake(SnakeData& data);
	~Snake();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(unsigned dt);
	void sync(SnakeData data);
	int id;
	bool alive;
	bool updated;
	std::vector<Parts*> _parts;
};

