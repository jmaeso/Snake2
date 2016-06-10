#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include "const.h"
#include <thread>
#include "Comm.h"
#include "Snakes.h"

using namespace std;

enum scenes {
	SCENE_JOINING,
	SCENE_GAME
};

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	sf::RenderWindow app;
	sf::Font font;
	int width, height;
	int uid;
	scenes scene;
	void drawJoining();
	void drawGame();
	void updateGame(sf::Time dt);
	Comm *C;
	thread T;
	sf::Clock deltaClock;
	Snakes *S;
	sf::Text joiningText;
};

