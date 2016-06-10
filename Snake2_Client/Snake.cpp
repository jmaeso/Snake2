#include "Snake.h"



Snake::Snake(SnakeData& data)
{
	this->id = data.uID;
	_parts = vector<Parts*>(0);
	for (int i = 0; i < data.numParts; i++)
	{
		if(i == 0)
			_parts.push_back(new Parts((int)data.parts[i].x, (int)data.parts[i].y, (int)data.uID, HEAD, (direction_t)data.direction));
		else
			_parts.push_back(new Parts((int)data.parts[i].x, (int)data.parts[i].y, (int)data.uID, BODY, (direction_t)data.direction));
	}
}

Snake::~Snake()
{
	/*for (int i = 0; i < _parts.size(); i++)
	{
		delete _parts[i];
	}
	_parts.clear();*/
}

void Snake::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < _parts.size(); i++)
	{
		target.draw(*_parts[i]);
	}
}

void Snake::update(unsigned dt)
{
	
}

void Snake::sync(SnakeData data)
{
	for (int i = 0; i < _parts.size(); i++)
	{
		delete _parts[i];
	}
	_parts.clear();
	this->id = data.uID;
	for (int i = 0; i < data.numParts; i++)
	{
		if (i == 0)
			_parts.push_back(new Parts(data.parts[i].x, data.parts[i].y, i, HEAD, (direction_t)data.direction));
		else
			_parts.push_back(new Parts(data.parts[i].x, data.parts[i].y, i, BODY, (direction_t)data.direction));
	}
}
