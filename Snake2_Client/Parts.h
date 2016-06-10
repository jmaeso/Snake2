#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <PROTO\Protocol.h>
#include "const.h"
#include <iostream>

using namespace std;

enum PartType{HEAD, BODY};

struct Parts : public sf::Drawable
{
	Parts(int x, int y, int snakeID, int partID, direction_t direction);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	~Parts();
	direction_t direction;
	sf::Sprite sprite;
	sf::Texture texture;
};

