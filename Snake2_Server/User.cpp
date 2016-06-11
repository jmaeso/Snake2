#include "User.h"

Message User::message(const Message & m, vector<ServerSnake> &game_data, Message & broadcast)
{
	Message res;
	res.t = Message::NONE;
	if (m.t == Message::JOIN) {
		res = Protocol::join_ack(game_data, sID);
	}
	/*else if (m.t == Message::KILL) {
		res = Protocol::kill_ack();
		for (unsigned i = 0; i < game_data.size(); ++i) {
			/*if (game_data[i].id == m.As.kill.sid) {
				game_data.erase(game_data.begin() + i);
				break;
			}
		}
		broadcast = Protocol::kill_bc(m.As.kill.sid);
	}*/
	return res;
}
