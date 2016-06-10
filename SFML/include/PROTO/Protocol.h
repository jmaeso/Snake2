#pragma once
#include <SFML\System.hpp>
#include <vector>
#include <iostream>

const unsigned MAX_PLAYERS = 4;
const unsigned MAX_PARTS = 55;
const unsigned WIDTH = 40;
const unsigned HEIGHT = 30;

enum direction_t {RIGHT, LEFT, UP, DOWN, MAX_DIR};

struct Part {
	char x;
	char y;
};

struct ServerSnake {
	std::vector<Part> parts;
	direction_t direction;
};

struct SnakeData{
	int uID;
	int numParts;
	Part parts[MAX_PARTS];
	char direction;
};

struct GameState {
	int numPlayers;
	SnakeData players[MAX_PLAYERS];
};

struct Message {
	enum Type {
		NONE,
		JOIN,
		JOIN_ACK,
		UPDATE,
		KILL,
		KILL_ACK,
		KILL_BC,
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
	static Message join_ack(const std::vector<ServerSnake> &data, int id);
	static Message update(const std::vector<ServerSnake> &data);
	static Message kill(int sid);
	static Message kill_ack();
	static Message kill_bc(int sid);
};

