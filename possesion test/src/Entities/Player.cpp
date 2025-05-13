
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
		sf::Vector2f bounds = 
		{
			m_vertex_array->getBounds().size.x * m_scale.x, 
			m_vertex_array->getBounds().size.y * m_scale.y 
		};

		setPosition(m_possessable_obj_ptr->updateMovement(dt)-bounds/2.f);
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

void Player::flip(int direction)
{
	if (direction / abs(direction) != m_scale.x / fabsf(m_scale.x))
	{
		scale({ direction / abs(direction) * fabsf(m_scale.x), m_scale.y });
		move(-direction / abs(direction) * m_vertex_array->getBounds().size.x * fabsf(m_scale.x), 0.f);
	}
}

void Player::possess(IPossessable* possessable_obj)
{
	m_possessable_obj_ptr = possessable_obj;
	m_prev_position = getPosition();
	flip(1);
}

void Player::unpossess()
{
	m_possessable_obj_ptr->unpossess();
	m_possessable_obj_ptr = nullptr;

	setPosition(m_prev_position);
}

bool Player::isPossessingObject()
{
	return m_possessable_obj_ptr != nullptr;
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

sf::Vector2f Player::outsideCollision(GameObject& moving_sprite, const GameObject& static_sprite)
{
	auto offset = IPhysicsObject::outsideCollision(moving_sprite, static_sprite);

	if (offset.y < 0)
	{
		isGrounded();
	}
	return offset;
}
