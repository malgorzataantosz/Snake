#include "Game.h"

Game::Game() : window("Snake", sf::Vector2u(800, 600)),
	snake(scene.getBlockSize(), &textbox),
	scene(sf::Vector2u(800, 600))
{
	clock.restart();
	srand(time(nullptr));

    textbox.setup(5, 20, 350, sf::Vector2f(225, 0));
	elapsed = 0.0f;

	textbox.add("Press Left, Right or Down ");
}

Game::~Game(){}

sf::Time Game::getElapsed(){ return clock.getElapsedTime(); }
void Game::restartClock(){ elapsed += clock.restart().asSeconds(); }
Window* Game::getWindow(){ return &window; }

void Game::handleInput(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) 
		&& snake.GetPhysicalDirection() != Direction::Down){
		snake.setDirection(Direction::Up);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) 
		&& snake.GetPhysicalDirection() != Direction::Up){
		snake.setDirection(Direction::Down);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
		&& snake.GetPhysicalDirection() != Direction::Right){
		snake.setDirection(Direction::Left);
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
		&& snake.GetPhysicalDirection() != Direction::Left){
		snake.setDirection(Direction::Right);
	}
}

void Game::update(){
	window.update();
	float timestep = 1.2f / snake.getSpeed();
	if(elapsed >= timestep){
		snake.tick();
		scene.update(snake);
		elapsed -= timestep;
		if (snake.hasLost()){
			textbox.add("GAME OVER! Score: "
						  + std::to_string((long long) snake.getScore()));
			snake.reset();
		}
	}
}

void Game::render(){
	window.beginDraw();
	scene.render(*window.getRenderWindow());
	snake.render(*window.getRenderWindow());
	textbox.render(*window.getRenderWindow());

	window.endDraw();
}