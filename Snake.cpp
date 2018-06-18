#include "Snake.h"

Snake::Snake(int blockSize, Textbox *l_log) {
    m_log = l_log;
    size = blockSize;

    bodyRect.setSize(sf::Vector2f(size - 1, size - 1));
    reset();
}

Snake::~Snake() {}

void Snake::setDirection(Direction l_dir) { dir = l_dir; }

Direction Snake::getDirection() { return dir; }

int Snake::getSpeed() { return speed; }

sf::Vector2i Snake::getPosition() {
    return (!m_snakeBody.empty() ? m_snakeBody.front().position : sf::Vector2i(1, 1));
}

int Snake::getLives() { return lives; }

int Snake::getScore() { return score; }

void Snake::increaseScore() {
    score += 10;
    m_log->add("SCORE: "
               + std::to_string((long long) score));
}

bool Snake::hasLost() { return lost; }

void Snake::lose() { lost = true; }

void Snake::toggleLost() { lost = !lost; }

Direction Snake::GetPhysicalDirection() {
    if (m_snakeBody.size() <= 1) {
        return Direction::None;
    }

    SnakeSegment &head = m_snakeBody[0];
    SnakeSegment &neck = m_snakeBody[1];

    if (head.position.x == neck.position.x) {
        return (head.position.y > neck.position.y
                ? Direction::Down : Direction::Up);
    } else if (head.position.y == neck.position.y) {
        return (head.position.x > neck.position.x
                ? Direction::Right : Direction::Left);
    }

    return Direction::None;
}

void Snake::extend() {
    if (m_snakeBody.empty()) { return; }
    SnakeSegment &tail_head =
            m_snakeBody[m_snakeBody.size() - 1];

    if (m_snakeBody.size() > 1) {
        SnakeSegment &tail_bone =
                m_snakeBody[m_snakeBody.size() - 2];

        if (tail_head.position.x == tail_bone.position.x) {
            if (tail_head.position.y > tail_bone.position.y) {
                m_snakeBody.push_back(SnakeSegment(
                        tail_head.position.x, tail_head.position.y + 1));
            } else {
                m_snakeBody.push_back(SnakeSegment(
                        tail_head.position.x, tail_head.position.y - 1));
            }
        } else if (tail_head.position.y == tail_bone.position.y) {
            if (tail_head.position.x > tail_bone.position.x) {
                m_snakeBody.push_back(SnakeSegment(
                        tail_head.position.x + 1, tail_head.position.y));
            } else {
                m_snakeBody.push_back(SnakeSegment(
                        tail_head.position.x - 1, tail_head.position.y));
            }
        }
    } else {
        if (dir == Direction::Up) {
            m_snakeBody.push_back(SnakeSegment(
                    tail_head.position.x, tail_head.position.y + 1));
        } else if (dir == Direction::Down) {
            m_snakeBody.push_back(SnakeSegment(
                    tail_head.position.x, tail_head.position.y - 1));
        } else if (dir == Direction::Left) {
            m_snakeBody.push_back(SnakeSegment(
                    tail_head.position.x + 1, tail_head.position.y));
        } else if (dir == Direction::Right) {
            m_snakeBody.push_back(SnakeSegment(
                    tail_head.position.x - 1, tail_head.position.y));
        }
    }
}

void Snake::reset() {
    m_snakeBody.clear();
    m_snakeBody.push_back(SnakeSegment(5, 7));
    m_snakeBody.push_back(SnakeSegment(5, 6));
    m_snakeBody.push_back(SnakeSegment(5, 5));

    setDirection(Direction::None); // Start off still.
    speed = 15;
    lives = 3;
    score = 0;
    lost = false;
}

void Snake::checkCollision() {
    if (m_snakeBody.size() < 5) { return; }
    SnakeSegment &head = m_snakeBody.front();
    for (auto itr = m_snakeBody.begin() + 1;
         itr != m_snakeBody.end(); ++itr) {
        if (itr->position == head.position) {
            int segments = m_snakeBody.end() - itr;
            cut(segments);
            break;
        }
    }
}

void Snake::move() {
    for (int i = m_snakeBody.size() - 1; i > 0; --i) {
        m_snakeBody[i].position = m_snakeBody[i - 1].position;
    }
    if (dir == Direction::Left) {
        --m_snakeBody[0].position.x;
    } else if (dir == Direction::Right) {
        ++m_snakeBody[0].position.x;
    } else if (dir == Direction::Up) {
        --m_snakeBody[0].position.y;
    } else if (dir == Direction::Down) {
        ++m_snakeBody[0].position.y;
    }
}

void Snake::tick() {
    if (m_snakeBody.empty()) { return; }
    if (dir == Direction::None) { return; }
    move();
    checkCollision();
}

void Snake::cut(int segments) {
    for (int i = 0; i < segments; ++i) {
        m_snakeBody.pop_back();
    }
    --lives;
    if (!lives) {
        lose();
        return;
    }

    m_log->add("You have lost a life! Lives left: "
               + std::to_string((long long) lives));
}

void Snake::render(sf::RenderWindow &window) {
    if (m_snakeBody.empty()) { return; }

    auto head = m_snakeBody.begin();
    bodyRect.setFillColor(sf::Color::Yellow);
    bodyRect.setPosition(head->position.x * size,
                         head->position.y * size);
    window.draw(bodyRect);

    bodyRect.setFillColor(sf::Color::Green);
    for (auto itr = m_snakeBody.begin() + 1;
         itr != m_snakeBody.end(); ++itr) {
        bodyRect.setPosition(itr->position.x * size,
                             itr->position.y * size);
        window.draw(bodyRect);
    }
}