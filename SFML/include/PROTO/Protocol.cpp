#include "Protocol.h"

const Message Protocol::decode(const char *msg)
{
	const Message *ret = reinterpret_cast <const Message*>(msg);
	return *ret;
}

const char* Protocol::encode(const Message &m)
{
	return reinterpret_cast<const char*>(&m);
}

Message Protocol::make(Message::Type type)
{
	Message m;
	m.t = type;
	return m;
}

Message Protocol::join()
{
	Message m = make(Message::JOIN);
	return m;
}

Message Protocol::join_ack(const std::vector<ServerSnake> &data, int id)
{
	Message m = make(Message::JOIN_ACK);
	m.As.join_ack.snakeID = id;
	m.As.join_ack.gs.numPlayers = data.size();
	for (unsigned i = 0; i < data.size(); ++i) {
		m.As.join_ack.gs.players[i].dead = data[i].dead;
		m.As.join_ack.gs.players[i].direction = data[i].direction;
		m.As.join_ack.gs.players[i].numParts = data[i].parts.size();
		m.As.join_ack.gs.players[i].uID = i;
		for (unsigned int j = 0;j < data[i].parts.size(); j++) {
			m.As.join_ack.gs.players[i].parts[j] = data[i].parts[j];
		}
	}
	return m;
}

Message Protocol::update(const std::vector<ServerSnake> &data)
{
	Message m = make(Message::UPDATE);
	m.As.join_ack.gs.numPlayers = data.size();
	for (unsigned i = 0; i < data.size(); ++i) {
		m.As.join_ack.gs.players[i].dead = data[i].dead;
		m.As.join_ack.gs.players[i].direction = data[i].direction;
		m.As.join_ack.gs.players[i].numParts = data[i].parts.size();
		m.As.join_ack.gs.players[i].uID = i;
		for (unsigned int j = 0; j < data[i].parts.size(); j++) {
			m.As.join_ack.gs.players[i].parts[j] = data[i].parts[j];
		}
	}
	return m;
}

Message Protocol::move(const direction_t & direction)
{
	Message m = make(Message::MOVE);
	m.As.move.direction = direction;
	return m;
}
