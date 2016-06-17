#include "Objects.h"



Objects::Objects(Part *food, int size)
{
}


Objects::~Objects()
{
}

void Objects::sync(Part *food, int size)
{
	for (int i = 0; i < this->food.size(); i++)
	{
		delete this->food[i];
	}
	this->food.clear();
	for (int i = 0; i < size; i++)
	{
		this->food.push_back(new Food(food[i].x, food[i].y));
	}
}

void Objects::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = food.size() - 1; i >= 0; i--)
	{
		target.draw(*food[i]);
	}
}