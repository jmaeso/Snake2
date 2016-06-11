#include "Parts.h"



Parts::Parts(int x, int y, int snakeID, int partID, direction_t direction)
{
	std::string partType;
	//this->direction = direction;
	if (partID == HEAD) partType = "cap";
	else partType = "bola";
	texture.loadFromFile("textures/" + partType + std::to_string(snakeID + 1) + ".png");
	sprite = sf::Sprite(texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setScale((float)((SCREEN_WIDTH / WIDTH) / sprite.getLocalBounds().width) * 1.2, (float)((SCREEN_WIDTH / WIDTH) / sprite.getLocalBounds().height) * 1.2);
	sprite.setPosition((x + 0.5f) * (float)(SCREEN_WIDTH / WIDTH), (y + 0.5f) * (float)(SCREEN_HEIGHT / HEIGHT));
	SetRotation(direction);
}

void Parts::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);
}

void Parts::SetRotation(direction_t direction)
{
	switch (direction)
	{
	case RIGHT:
		sprite.setRotation(270);
		break;
	case LEFT:
		sprite.setRotation(90);
		break;
	case UP:
		sprite.setRotation(180);
		break;
	case DOWN:
		sprite.setRotation(0);
		break;
	case MAX_DIR:
		break;
	default:
		break;
	}
}

Parts::~Parts()
{
}
