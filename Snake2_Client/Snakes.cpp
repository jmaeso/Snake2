#include "Snakes.h"


Snakes::Snakes(GameState &state, int id)
{
	this->playerID = id;
	for (int i = 0; i < state.numPlayers; ++i) {
		snakes.push_back(Snake(state.players[i]));
	}
}

Snakes::~Snakes()
{
}

void Snakes::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (unsigned i = 0; i < snakes.size(); ++i) {
		target.draw(snakes[i]);
	}
}

void Snakes::update(unsigned dt)
{
	
}

void Snakes::sync(GameState state)
{
	snakes.clear();
	for (int i = 0; i < state.numPlayers; ++i) {
		snakes.push_back(Snake(state.players[i]));
	}
}

void Snakes::kill(unsigned sid)
{
	
}

void Snakes::SetDirection(direction_t dir)
{
}
