#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include "const.h"
#include <string>
#include <PROTO\Protocol.h>
#include <unordered_map>
#include <map>
#include "User.h"

using namespace std;

typedef unordered_map<string, User>::const_iterator iter;


class Server
{
public:
	Server(unsigned port);
	~Server();
	void run();
private:
	int next_update;
	int next_move;
	void update();
	void broadcast(string UUID, const Message &m);
	void broadcastAll(const Message &m);
	sf::UdpSocket socket;
	unsigned port;
	unordered_map<string,User> users;
	vector<ServerSnake> game_data;
};

