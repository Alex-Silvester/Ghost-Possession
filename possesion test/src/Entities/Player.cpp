
#include "Player.h"

void Player::init(sf::Vector2f gravity)
{
	setGravity(gravity);

	e_collision_type = CollisionType::OUTSIDE;
}

void Player::update(float dt)
{
	if (isPossessingObject())
	{
		m_sprite->setPosition(m_possessable_obj_ptr->updateMovement(dt)-m_sprite->getGlobalBounds().size/2.f);
	}
	else
	{
		updateGravity();

		move(m_velocity * dt);
	}
}

void Player::jump(float vel)
{
	if (m_grounded) 
	{
		setVelocity(m_velocity.x, -vel);
		m_grounded = false;
	}
}

void Player::possess(IPossessable* possessable_obj)
{
	m_possessable_obj_ptr = possessable_obj;
	m_prev_position = m_sprite->getPosition();
}

void Player::unpossess()
{
	m_possessable_obj_ptr->unpossess();
	m_possessable_obj_ptr = nullptr;

	m_sprite->setPosition(m_prev_position);
}

void Player::keyPressed(const sf::Event& event)
{
	using namespace sf::Keyboard;
	Key code = event.getIf<sf::Event::KeyPressed>()->code;

	if (code == Key::Space && !keyHeld.Space)
	{
		keyHeld.Space = true;
		jump(350.f);
	}
	if (code == Key::A && !keyHeld.A)
	{
		keyHeld.A = true;
		addVelocity(-cst::s_player_speed, 0);
		flip(-1);
	}
	if (code == Key::D && !keyHeld.D)
	{
		keyHeld.D = true;
		addVelocity(cst::s_player_speed, 0);
		flip(1);
	}
}

void Player::keyReleased(const sf::Event& event)
{
	using namespace sf::Keyboard;
	Key code = event.getIf<sf::Event::KeyReleased>()->code;

	if (code == Key::A && keyHeld.A)
	{
		keyHeld.A = false;
		addVelocity(cst::s_player_speed, 0);
	}
	if (code == Key::D && keyHeld.D)
	{
		keyHeld.D = false;
		addVelocity(-cst::s_player_speed, 0);
	}
	if (code == Key::Space && keyHeld.Space)
	{
		keyHeld.Space = false;
	}
}
