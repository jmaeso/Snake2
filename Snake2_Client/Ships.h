#pragma once
#include <SFML\Graphics.hpp>
#include<vector>
#include"Ship.h"
#include <PROTO\Protocol.h>
#include <string>
using namespace std;

#define TSIZE 6

class Ships : public sf::Drawable
{
public:
	Ships(ship_data *data, int size);
	~Ships();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(unsigned dt);
	void sync(ship_data *data, int size, int delta);
	int click(unsigned x, unsigned y);
	void kill(unsigned sid);
private:
	vector<sf::Texture> texs;
	vector<Ship> ships;
	int nasty;
	int df() { return ships.size() * 2 + 30; }
};

