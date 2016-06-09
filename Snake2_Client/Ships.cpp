#include "Ships.h"


Ships::Ships(ship_data * data, int size)
{
	texs = vector<sf::Texture>(6);
	for (unsigned i = 0; i < TSIZE; ++i) {
		texs[i].loadFromFile("textures/" + to_string(i) +".png");
	}
	for (int i = 0; i < size; ++i) {
		ships.push_back(Ship((int)data[i].id, (int)data[i].x, (int)data[i].y, (int)data[i].speed, (data[i].type&SHIP_RIGHT)>0, &texs[(int)(data[i].type&7)]));
	}
	nasty = 0;
}

Ships::~Ships()
{
}

void Ships::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (unsigned i = 0; i < ships.size(); ++i) {
		target.draw(ships[i]);
	}
}

void Ships::update(unsigned dt)
{
	nasty += dt;
	if (nasty >= df()) {
		for (unsigned i = 0; i < ships.size(); ++i) {
			ships[i].update(dt);
		}
		nasty -= df();
	}
}

void Ships::sync(ship_data * data, int size, int delta)
{
	nasty = delta;
	for (unsigned j = 0; j < ships.size(); ++j) ships[j].updated = false;
	for (int i = 0; i < size; ++i) {
		for (unsigned j = 0; j < ships.size(); ++j) {
			if (ships[j].id == data[i].id) {
				ships[j].sync(data[i].x, data[i].y, data[i].speed, (data[i].type&SHIP_RIGHT)>0);
				ships[j].updated = true;
			}
		}
	}
	for (int j = ships.size()-1; j >=0; --j) {
		if (!ships[j].updated) ships.erase(ships.begin() + j);
	}
}

int Ships::click(unsigned x, unsigned y)
{
	for (unsigned j = 0; j < ships.size(); ++j) {
		if (ships[j].sprite.getGlobalBounds().contains((float)x, (float)y)) {
			int ret = ships[j].id;
			ships.erase(ships.begin() + j);
			return ret;
		}
	}
	return -1;
}

void Ships::kill(unsigned sid)
{
	for (unsigned j = 0; j < ships.size(); ++j) {
		if (ships[j].id == sid) {
			ships.erase(ships.begin() + j);
			break;
		}
	}
}
