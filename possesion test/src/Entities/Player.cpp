
#include "Player.h"

void Player::init(sf::Vector2f gravity)
{
	setGravity(gravity);

	e_collision_type = CollisionType::OUTSIDE;
}

void Player::update(float dt)
{
	updateGravity();

	move(m_velocity * dt);
}