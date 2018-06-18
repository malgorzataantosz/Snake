#include "Textbox.h"

Textbox::Textbox(){
	setup(1, 10, 100, sf::Vector2f(0, 0));
}

Textbox::Textbox(int visible, int charSize,
int width, sf::Vector2f screenPos){
	setup(visible, charSize, width, screenPos);
}

Textbox::~Textbox(){ clear(); }

void Textbox::setup(int visible, int charSize,
					int width, sf::Vector2f screenPos){
	numVisible = visible;

	sf::Vector2f offset(1.0f, 1.0f);
	
	font.loadFromFile("/home/malgorzata/clion/snake/UbuntuMono-B.ttf");
	content.setFont(font);
	content.setString("");
	content.setCharacterSize(charSize);
	content.setColor(sf::Color::White);
	content.setPosition(screenPos + offset);

	backdrop.setSize(sf::Vector2f(
		width, (visible * (charSize * 0.2f))));
	backdrop.setFillColor(sf::Color(90,90,90,90));
	backdrop.setPosition(screenPos);
}

void Textbox::add(std::string message){
	messages.push_back(message);
	if (messages.size() < 2){ return; }
	messages.erase(messages.begin());
}

void Textbox::clear(){ messages.clear(); }

void Textbox::render(sf::RenderWindow &wind){
	std::string lContent;

	for(auto &itr : messages){
		lContent.append(itr+"\n");
	}

	if(lContent != ""){
		content.setString(lContent);
		wind.draw(backdrop);
		wind.draw(content);
	}
}