#include "Game.h"



Game::Game()
{
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
	app.create(sf::VideoMode(width, height), "Snake", sf::Style::Titlebar|sf::Style::Close);
	app.setFramerateLimit(30);
	app.setVerticalSyncEnabled(true);
	scene = SCENE_JOINING;
	font = sf::Font();
	font.loadFromFile("madpixels.otf");
	joiningText = sf::Text("Joining...", font, height / 30);
	joiningText.setOrigin({ joiningText.getLocalBounds().width / 2.0f,joiningText.getLocalBounds().height / 2.0f });
	joiningText.setPosition({ width / 2.0f,height / 2.2f });
	joiningText.setColor(sf::Color::Red);

	backgroundTexture.loadFromFile("textures/background.png");
	backgroundSprite = sf::Sprite(backgroundTexture);
	backgroundSprite.setOrigin(0, 0);
	backgroundSprite.setScale((float)((SCREEN_WIDTH) / backgroundSprite.getLocalBounds().width), (float)((SCREEN_HEIGHT) / backgroundSprite.getLocalBounds().height));
	backgroundSprite.setPosition(0, 0);

	loadingTexture.loadFromFile("textures/loading.png");
	loadingSprite = sf::Sprite(loadingTexture);
	loadingSprite.setOrigin(0, 0);
	loadingSprite.setScale((float)((SCREEN_WIDTH) / loadingSprite.getLocalBounds().width), (float)((SCREEN_HEIGHT) / loadingSprite.getLocalBounds().height));
	loadingSprite.setPosition(0, 0);

	counter = 0;
	S = NULL;
	O = NULL;
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
	if (O != NULL) delete O;
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
						
					}
				}
			} else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape || event.key.alt && event.key.code == sf::Keyboard::F4) {
					app.close();
				}
				else if (S != NULL) {
					if (event.key.code == sf::Keyboard::Up) {
						S->SetDirection(UP); 
						C->send(Protocol::move(UP));
					}
					else if (event.key.code == sf::Keyboard::Down) {
						S->SetDirection(DOWN); 
						C->send(Protocol::move(DOWN));
					}
					else if (event.key.code == sf::Keyboard::Left) { 
						S->SetDirection(LEFT);
						C->send(Protocol::move(LEFT));
					}
					else if (event.key.code == sf::Keyboard::Right) { 
						S->SetDirection(RIGHT);
						C->send(Protocol::move(RIGHT));
					}
				}
			}
		}
		app.clear(sf::Color(0,0,0));
		if (scene == SCENE_JOINING) {
			counter+= dt.asMilliseconds();
			if (counter >= 1000) { 
				C->send(Protocol::join()); 
				counter = 0;
			}
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
		app.draw(loadingSprite);
		while (!C->empty()) {
			Message m = C->poll();
			if (m.t == Message::JOIN_ACK) {
				S = new Snakes(m.As.join_ack.gs, m.As.join_ack.snakeID);
				O = new Objects(m.As.join_ack.gs.food, m.As.join_ack.gs.numFood);
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
			S->sync(m.As.update.gs);
			O->sync(m.As.update.gs.food, m.As.update.gs.numFood);
		}
	}
}

void Game::drawGame() {
	app.draw(backgroundSprite);
	app.draw(*S);
	app.draw(*O);
}