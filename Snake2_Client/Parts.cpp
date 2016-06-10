#include "Parts.h"



Parts::Parts(int x, int y, int snakeID, int partID, direction_t direction)
{
	std::string partType;
	this->direction = direction;
	if (partID == HEAD) partType = "cap";
	else partType = "bola";
	texture.loadFromFile("textures/" + partType + std::to_string(snakeID + 1) + ".png");
	sprite = sf::Sprite(texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setScale((float)(SCREEN_WIDTH / WIDTH) / sprite.getLocalBounds().width, (float)(SCREEN_WIDTH / WIDTH) / sprite.getLocalBounds().height);
	sprite.setPosition((x + 0.5f) * (float)(SCREEN_WIDTH / WIDTH), (y + 0.5f) * (float)(SCREEN_HEIGHT / HEIGHT));
}

void Parts::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);
}

Parts::~Parts()
{
}
