#include "Server.h"



Server::Server(unsigned port)
{
	this->port = port;
}


Server::~Server()
{
}

void Server::run()
{
	next_update = 0;
	next_move = 0;
	if (socket.bind(port) != sf::Socket::Done) {
		cout << "Coudn't start server: bind failed" << endl;
		return;
	}
	cout << "Server is listening to port " << port << endl;
	cout << "Protocol message size: " << sizeof(Message) << endl;
	socket.setBlocking(false);
	char in[sizeof(Message)];
	memset(in, '\0', sizeof(Message));
	std::size_t received;
	sf::IpAddress sender;
	unsigned short senderPort;
	sf::Clock clock;
	int previous = clock.getElapsedTime().asMilliseconds();
	game_data = vector<ServerSnake>(0);
	while (true) {
		sf::Socket::Status s = socket.receive(in, sizeof(in), received, sender, senderPort);
		if (received != 0) {
			Message got = Protocol::decode(in);
			if (got.t < Message::MAX) {
				cout << (string)sender.toString() << endl;
					cout<< to_string(senderPort) << endl;
				string UUID = (string)(sender.toString() + to_string(senderPort));
				if (got.t == Message::JOIN) {
					User newUser;
					newUser.ip = sender;
					newUser.port = senderPort;
					newUser.sID = game_data.size();
					users[UUID] = newUser;
					ServerSnake tempSnake;
					tempSnake.dead = false;
					tempSnake.parts = std::vector<Part>(0);
					int div = game_data.size() % 4;
					int x0 = (rand() % (WIDTH / 2 - MIN_PARTS)) + MIN_PARTS;
					int dx = -1;
					if (div > 1) {
						dx = 1;
						x0 += WIDTH / 2;
					}
					int y0 = rand() % (HEIGHT / 2);
					if (div % 2 == 1)
						y0 += HEIGHT / 2;
					for (int i = 0; i < MIN_PARTS; i++)
					{
						tempSnake.parts.push_back({ (char)(x0 + i * dx), char(y0) });
					}
					if (dx == 1) tempSnake.direction = LEFT;
					else tempSnake.direction = RIGHT;
					game_data.push_back(tempSnake);
					cout << "NEW USER Current users: " << users.size() << endl;
				}
				if (users.count(UUID)>0) {
					User *u = &users[UUID];
					Message tobroadcast=Protocol::make(Message::NONE);
					Message res = u->message(got,game_data, tobroadcast);
					if (tobroadcast.t!=Message::NONE) broadcast(UUID, tobroadcast);
					if (res.t != Message::NONE) socket.send(Protocol::encode(res), sizeof(Message) , u->ip, u->port);
				}
				if (got.t == Message::MOVE) {
					for (int i = 0; i < game_data.size(); i++)
					{
						if (users[UUID].sID == i) {
							game_data[i].direction = got.As.move.direction;
							cout << "Received " << (int)got.As.move.direction << " from " << i << endl;
						}
					}
				}
			}
		}
		int current = clock.getElapsedTime().asMilliseconds();
		if (current != previous) {
			int steps = current - previous;
			if (users.size() > 0) {
				next_update += steps;
				if (next_update > UPDATEEVERY) {
					update();
					broadcastAll(Protocol::update(game_data));
					next_update -= UPDATEEVERY;
				}
			}
			previous = current;
		}
	}
}

void Server::update()
{
	vector<vector<int> > cells(WIDTH, vector<int>(HEIGHT, -1));
	for (int i = 0; i < game_data.size(); i++)
	{
		for (int j = 0; j < game_data[i].parts.size(); j++) {
			cells[game_data[i].parts[j].x][game_data[i].parts[j].y] = i;
		}
	}
	vector<bool> alive(game_data.size(), true);
	for (int i = 0; i < game_data.size(); i++)
	{
		Part tempPart;
		tempPart = game_data[i].parts[0];
		switch (game_data[i].direction) {
		case RIGHT:
			tempPart.x += 1;
			break;
		case LEFT:
			tempPart.x -= 1;
			break;
		case UP:
			tempPart.y -= 1;
			break;
		case DOWN:
			tempPart.y += 1;
			break;
		}
		if (tempPart.x < 0) tempPart.x += WIDTH;
		if (tempPart.y < 0) tempPart.y += HEIGHT;
		tempPart.x = tempPart.x % WIDTH;
		tempPart.y = tempPart.y % HEIGHT;
		if (cells[tempPart.x][tempPart.y] != -1 && cells[tempPart.x][tempPart.y] != i) {
			alive[cells[tempPart.x][tempPart.y]] = false;
			game_data[i].dead = true;
			cout << i << " kill " << cells[tempPart.x][tempPart.y] << endl;
		}
	}
	for (int i = 0; i < game_data.size(); i++)
	{
		if (alive[i]) {
			Part tempPart;
			tempPart = game_data[i].parts[0];
			switch (game_data[i].direction) {
			case RIGHT:
				tempPart.x += 1;
				break;
			case LEFT:
				tempPart.x -= 1;
				break;
			case UP:
				tempPart.y -= 1;
				break;
			case DOWN:
				tempPart.y += 1;
				break;
			}
			if (tempPart.x < 0) tempPart.x += WIDTH;
			if (tempPart.y < 0) tempPart.y += HEIGHT;
			tempPart.x = tempPart.x % WIDTH;
			tempPart.y = tempPart.y % HEIGHT;
			game_data[i].parts.insert(game_data[i].parts.begin(), tempPart);
			if (cells[tempPart.x][tempPart.y] == -1 || cells[tempPart.x][tempPart.y] == i) {
				game_data[i].parts.erase(game_data[i].parts.begin() + game_data[i].parts.size() - 1);
			}
		}
	}
}

void Server::broadcast(string UUID, const Message &m)
{
	const char *data = Protocol::encode(m);
	for (auto it = users.begin(); it != users.end(); ++it) {
		if (it->first != UUID) {
			socket.send(data, sizeof(Message), it->second.ip, it->second.port);
		}
	}
}

void Server::broadcastAll(const Message & m){
	const char *data = Protocol::encode(m);
	for (auto it = users.begin(); it != users.end(); ++it) {
		socket.send(data, sizeof(Message), it->second.ip, it->second.port);
	}
}
