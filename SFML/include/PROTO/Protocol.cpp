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
		m.As.join_ack.gs.players[i].direction = data[i].direction;
		m.As.join_ack.gs.players[i].numParts = data[i].parts.size();
		m.As.join_ack.gs.players[i].uID = i;
		for (unsigned int j = 0; j < data[i].parts.size(); j++) {
			m.As.join_ack.gs.players[i].parts[j] = data[i].parts[j];
		}
	}
	return m;
}

Message Protocol::kill(int sid)
{
	Message m = make(Message::KILL);
	m.As.kill.sid = sid;
	return m;
}

Message Protocol::kill_ack()
{
	Message m = make(Message::KILL_ACK);
	return m;
}

Message Protocol::kill_bc(int sid)
{
	Message m = make(Message::KILL_BC);
	m.As.kill_bc.sid = sid;
	return m;
}
