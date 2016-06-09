#pragma once
#include <SFML\System.hpp>
#include <vector>
#include <iostream>

const unsigned MAX_PLAYERS = 4;
const unsigned MAX_PARTS = 55;

enum direction_t {RIGHT, LEFT, UP, DOWN, MAX_DIR};

struct Part {
	char x;
	char y;
};

struct Snake {
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

//TEMPORAL, PENDING TO ERASE
struct ship_data {
	char16_t x;
	char16_t y;
	char type;
	char id;
	char16_t speed;
};

enum ship_t {
	SHIP_0,
	SHIP_1,
	SHIP_2,
	SHIP_3,
	SHIP_4,
	SHIP_5,
	SHIP_MAX,
	SHIP_LEFT = 8,
	SHIP_RIGHT = 16
};
//UNTIL HERE

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
		/*struct {
			int delta;
			int shipCount;
			ship_data ships[MAXSHIP];
		} update;*/
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
	static Message join_ack(const std::vector<Snake> &data, int id);
	//static Message update(int delta, const std::vector<ship_data> &data);
	static Message kill(int sid);
	static Message kill_ack();
	static Message kill_bc(int sid);
};

