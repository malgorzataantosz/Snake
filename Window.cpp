#include "Window.h"

Window::Window(){ setup("Window", sf::Vector2u(640, 480)); }
Window::Window(const std::string& title, const sf::Vector2u& size){ setup(title, size); }
Window::~Window(){ destroy(); }

void Window::setup(const std::string title, const sf::Vector2u &size){
	windowTitle = title;
	windowSize = size;
	isFullScreen = false;
	done = false;
    create();
}

void Window::create(){
	auto style = (isFullScreen ? sf::Style::Fullscreen
		: sf::Style::Default);
	window.create({ windowSize.x, windowSize.y, 32 },
		windowTitle, style);
}

void Window::destroy(){
	window.close();
}

void Window::beginDraw(){ window.clear(sf::Color::Black); }
void Window::endDraw(){ window.display(); }

bool Window::isDone(){ return done; }
bool Window::isFullscreen(){ return isFullScreen; }

sf::RenderWindow* Window::getRenderWindow(){ return &window; }
sf::Vector2u Window::getWindowSize(){ return windowSize; }

void Window::fullscreen(){
	isFullScreen = !isFullScreen;
	window.close();
    create();
}

void Window::update(){
	sf::Event event;
	while(window.pollEvent(event)){
		if(event.type == sf::Event::Closed){ done = true; }
		else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){ done = true; }
		else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5){ fullscreen(); }
	}
}