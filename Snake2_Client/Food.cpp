#include "Food.h"



Food::Food(int x, int y)
{
	texture.loadFromFile("textures/food.png");
	sprite = sf::Sprite(texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setScale((float)((SCREEN_WIDTH / WIDTH) / sprite.getLocalBounds().width), (float)((SCREEN_WIDTH / WIDTH) / sprite.getLocalBounds().height));
	sprite.setPosition((x + 0.5f) * (float)(SCREEN_WIDTH / WIDTH), (y + 0.5f) * (float)(SCREEN_HEIGHT / HEIGHT));
}


Food::~Food()
{
}

void Food::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);
}
