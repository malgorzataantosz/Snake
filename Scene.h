#ifndef SNAKE_SCENE_H
#define SNAKE_SCENE_H
#include <SFML/Graphics.hpp>
#include "Snake.h"

class Scene{
public:
	Scene(sf::Vector2u l_windSize);
	~Scene();

	int getBlockSize();

	void respawnApple();

	void update(Snake& player);
	void render(sf::RenderWindow& window);
private:
	sf::Vector2u windowSize;
	sf::Vector2i item;
	int blockSize;

	sf::CircleShape appleShape;
	sf::RectangleShape bounds[4];
};
#endif