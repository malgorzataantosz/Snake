#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include <vector>

struct SnakeSegment {
    SnakeSegment(int x, int y) : position(x, y) {}

    sf::Vector2i position;
};

enum class Direction {
    None, Up, Down, Left, Right
};

class Snake {
public:
    Snake(int blockSize, Textbox *l_log);

    ~Snake();


    void setDirection(Direction l_dir);

    Direction getDirection();

    int getSpeed();

    sf::Vector2i getPosition();

    int getLives();

    int getScore();

    void increaseScore();

    bool hasLost();

    void lose();

    void toggleLost();

    Direction GetPhysicalDirection();

    void extend();

    void reset();

    void move();

    void tick();

    void cut(int segments);

    void render(sf::RenderWindow &window);

private:
    void checkCollision();

    std::vector<SnakeSegment> m_snakeBody;
    int size;
    Direction dir;
    int speed;
    int lives;
    int score;
    bool lost;
    sf::RectangleShape bodyRect;
    Textbox *m_log;
};
#endif