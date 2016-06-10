#pragma once
#include <SFML\Graphics.hpp>
#include<vector>
#include"Snake.h"
#include <PROTO\Protocol.h>
#include <string>
using namespace std;

class Snakes : public sf::Drawable
{
public:
	Snakes(GameState &state, int id);
	~Snakes();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(unsigned dt);
	void sync(GameState state);
	void kill(unsigned sid);
	void SetDirection(direction_t dir);
private:
	vector<Snake> snakes;
	int playerID;
};

