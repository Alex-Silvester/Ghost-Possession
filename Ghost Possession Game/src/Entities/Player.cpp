
#include "Player.h"

void Player::init(std::shared_ptr<sf::Texture>& texture, sf::Vector2f scale)
{
	GameEntity::init(texture, scale);

	setGravity(0,cst::s_gravity);

	e_collision_type = CollisionType::OUTSIDE;

#if DEBUG_P_RADIUS == true
	possession_radius.setOrigin(possession_radius.getGlobalBounds().getCenter());
#endif
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

#if DEBUG_P_RADIUS == true
	possession_radius.setPosition(getFloatRect().getCenter());
#endif
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

void Player::keyPressed(const sf::Keyboard::Key& key)
{
	using namespace sf::Keyboard;

	if (key == Key::Space && !keyHeld.Space)
	{
		keyHeld.Space = true;
		jump(450.f);
	}
	if (key == Key::A && !keyHeld.A)
	{
		keyHeld.A = true;
		addVelocity(-cst::s_player_speed, 0);
		flip(-1);
	}
	if (key == Key::D && !keyHeld.D)
	{
		keyHeld.D = true;
		addVelocity(cst::s_player_speed, 0);
		flip(1);
	}
}

void Player::keyReleased(const sf::Keyboard::Key& key)
{
	using namespace sf::Keyboard;

	if (key == Key::A && keyHeld.A)
	{
		keyHeld.A = false;
		addVelocity(cst::s_player_speed, 0);
	}
	if (key == Key::D && keyHeld.D)
	{
		keyHeld.D = false;
		addVelocity(-cst::s_player_speed, 0);
	}
	if (key == Key::Space && keyHeld.Space)
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

#if DEBUG_P_RADIUS == true
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(possession_radius);

	if (m_vertex_array.has_value())
	{
		states.transform.scale(m_scale);
		states.transform.translate({ m_position.x / m_scale.x, m_position.y / m_scale.y });
		states.texture = m_texture;
		target.draw(m_vertex_array.value(), states);
	}
}
#endif
