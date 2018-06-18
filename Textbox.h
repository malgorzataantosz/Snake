#ifndef SNAKE_TEXTBOX_H
#define SNAKE_TEXTBOX_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


class Textbox{
public:
	Textbox();
	Textbox(int visible, int charSize,
		int width, sf::Vector2f screenPos);
	~Textbox();

	void setup(int visible, int charSize,
               int width, sf::Vector2f screenPos);
	void add(std::string message);
	void clear();

	void render(sf::RenderWindow &wind);
private:
	std::vector<std::string> messages;
	int numVisible;

	sf::RectangleShape backdrop;
	sf::Font font;
	sf::Text content;
};
#endif