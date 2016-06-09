#include "Game.h"



Game::Game()
{
	width = 800;
	height = 600;
	app.create(sf::VideoMode(width, height), "GAME", sf::Style::Titlebar|sf::Style::Close);
	app.setVerticalSyncEnabled(true);
	scene = SCENE_JOINING;
	font = sf::Font();
	/*font.loadFromFile("madpixels.otf");
	joiningText = sf::Text("Joining...", font, height / 30);
	joiningText.setOrigin({ joiningText.getLocalBounds().width / 2.0f,joiningText.getLocalBounds().height / 2.0f });
	joiningText.setPosition({ width / 2.0f,height / 2.2f });
	joiningText.setColor(sf::Color::Red);*/
	S = NULL;
	C = new Comm(SERVERIP);
	T = thread(&Comm::init, C);
	C->send(Protocol::join());
	deltaClock = sf::Clock();
}


Game::~Game()
{
	if (C != NULL) {
		C->stop();
		T.join();
		delete C;
	}
	if (S != NULL) delete S;
}

void Game::run()
{
	
	//app->setFramerateLimit(60);
	while (app.isOpen())
	{
		sf::Time dt = deltaClock.restart();
		sf::Event event;
		while (app.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) {
				app.close();
			}

			//mouse event
			else if (event.type == sf::Event::MouseButtonPressed){
				if (scene == SCENE_GAME) {
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						int k = S->click(event.mouseButton.x, event.mouseButton.y);
						if (k != -1) C->send(Protocol::kill(k));
					}
				}
			} else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape || event.key.alt && event.key.code == sf::Keyboard::F4) {
					app.close();
				}
			}
		}
		app.clear(sf::Color(255,255,255,128));
		if (scene == SCENE_JOINING) {
			drawJoining();
		}
		else if (scene == SCENE_GAME) {
			updateGame(dt);
			drawGame();
		}
		app.display();
	}
}

void Game::drawJoining()
{
	if (S != NULL) {
		scene = SCENE_GAME;
	}
	else {
		//app.draw(joiningText);
		while (!C->empty()) {
			Message m = C->poll();
			if (m.t == Message::JOIN_ACK) {
				//S = new Ships(m.As.join_ack.ships, m.As.join_ack.shipCount);
				cout << m.As.join_ack.snakeID << ", " << m.As.join_ack.gs.numPlayers << endl;
				system("PAUSE");
				break;
			}
		}
	}
}

void Game::updateGame(sf::Time dt) {
	S->update(dt.asMilliseconds());
	while (!C->empty()) {
		Message m = C->poll();
		if (m.t == Message::UPDATE) {
			//S->sync(m.As.update.ships, m.As.update.shipCount, m.As.update.delta);
		}
		else if (m.t == Message::KILL_BC) {
			S->kill(m.As.kill_bc.sid);
		}
	}
}

void Game::drawGame() {
	app.draw(*S);
}