#pragma once
#include <SFML\System.hpp>
#include <vector>
#include <iostream>

const unsigned MAX_PLAYERS = 4;
const unsigned MAX_PARTS = 35;
const unsigned MAX_FOOD = 10;
const unsigned WIDTH = 40;
const unsigned HEIGHT = 30;

enum direction_t {RIGHT = 1, LEFT = 2, UP = 4, DOWN = 8};

struct Part {
	char x;
	char y;
};

struct ServerSnake {
	std::vector<Part> parts;
	direction_t direction;
	char dead;
};

struct SnakeData{
	int uID;
	int numParts;
	Part parts[MAX_PARTS];
	direction_t direction;
	char dead;
};

struct GameState {
	int numPlayers;
	int numFood;
	SnakeData players[MAX_PLAYERS];
	Part food[MAX_FOOD];
};

struct Message {
	enum Type {
		NONE,
		JOIN,
		JOIN_ACK,
		UPDATE,
		MOVE,
		DEAD,
		MAX
	};
	Message::Type t;
	union
	{
		struct {

		} join;
		struct {
			GameState gs;
			int snakeID;
		} join_ack;
		struct {
			GameState gs;
		} update;
		struct{
			direction_t direction;
		}move;
		struct {
			int sid;
		} kill;
		struct {
		
		} kill_ack;
		struct {
			int sid;
		} kill_bc;
	} As;
};

class Protocol
{
public:
	static const Message decode(const char *msg);
	static const char* encode(const Message &m);
	static Message make(Message::Type type);
	static Message join();
	static Message join_ack(const std::vector<ServerSnake> &data, int id, const std::vector<Part> &food);
	static Message update(const std::vector<ServerSnake> &data, const std::vector<Part> &food);
	static Message move(const direction_t direction);
	
};

