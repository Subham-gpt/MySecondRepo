#include "Ball.h"

// Constructor Function
Ball::Ball(float startX, float startY) {
    m_Position.x = startX;
    m_Position.y = startY;
    m_Shape.setRadius(10.0);
    m_Shape.setPosition(m_Position);
}

FloatRect Ball::get_Position() {
    return m_Shape.getGlobalBounds();
}

CircleShape Ball::get_Shape() {
    return m_Shape;
}

float Ball::getXVelocity() {
    return m_DirectionX;
}

void Ball::reboundSides() {
    m_DirectionX = -m_DirectionX;
}

void Ball::reboundBatOrTop() {
    m_DirectionY = -m_DirectionY;
}

void Ball::reboundBottom() {
    m_Position.y = 0;
    m_Position.x = 500;
    m_DirectionY = -m_DirectionY;
}

void Ball::update(Time dt) {
    // Update the ball position
    m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();
    m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();

    // Move the ball and bat
    m_Shape.setPosition(m_Position);
}
