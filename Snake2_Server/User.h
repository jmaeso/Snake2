#pragma once
#include <SFML\Network.hpp>
#include <SFML\Main.hpp>
#include <string>
#include <PROTO\Protocol.h>
#include <vector>
#include <map>
#include "const.h"
#include <math.h>
using namespace std;

 

struct User {
	sf::IpAddress ip;
	unsigned short port;
	int sID;
	Message message(const Message &m, vector<Snake> &game_data, Message &broadcast);
};

