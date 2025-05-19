#pragma once

#include "GameEntity.h"
#include "../Interfaces/Interfaces.h"
#include "../constants.h"

#include <iostream>

#define DEBUG_P_RADIUS false;

class Player : public GameEntity, public IPhysicsObject, public IControllable
{
public:
	Player() = default;

	~Player()
	{
		delete m_possessable_obj_ptr;
	}

	Player& operator=(const Player& obj)
	{
		return *this;
	}

	void init(std::shared_ptr<sf::Texture>& texture, sf::Vector2f scale = { 1.f,1.f });
	void update(float dt);

	void isGrounded() { m_velocity.y = 0; m_grounded = true; }

	void jump(float vel = 100.f);

	void flip(int direction);

	void possess(IPossessable* possessable_obj);
	void unpossess();

	bool isPossessingObject();

	void keyPressed(const sf::Keyboard::Key& key) override;
	void keyReleased(const sf::Keyboard::Key& key) override;

	IPossessable* getPossessedObject() 
	{
		return m_possessable_obj_ptr;
	}

	sf::Vector2f outsideCollision(GameObject& moving_sprite, const GameObject& static_sprite) override;

	inline float getPossessionDist() const
	{
		return m_possession_radius;
	}

private:

	IPossessable* m_possessable_obj_ptr = nullptr;
	sf::Vector2f m_prev_position;

	bool m_grounded = false;

	struct KeyHeld
	{
		bool A = false;
		bool D = false;
		bool Space = false;
	}keyHeld;

	const float m_possession_radius = 200.f;

#if DEBUG_P_RADIUS == true
	sf::RectangleShape possession_radius = sf::RectangleShape({ m_possession_radius, m_possession_radius });
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
#endif

};