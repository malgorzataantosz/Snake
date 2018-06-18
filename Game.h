#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H
#include "Window.h"
#include "Scene.h"
#include "Snake.h"
#include "Textbox.h"

class Game{
public:
	Game();
	~Game();

	void handleInput();
	void update();
	void render();

	sf::Time getElapsed();
	void restartClock();

	Window* getWindow();
private:
	Window window;
	sf::Clock clock;
	float elapsed;

	Scene scene;
	Snake snake;
	Textbox textbox;
};
#endif