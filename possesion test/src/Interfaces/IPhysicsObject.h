#pragma once

#include <SFML/graphics.hpp>

#include "../GameObject.h"

enum CollisionType
{
	NONE,
	INSIDE,
	OUTSIDE
};

class IPhysicsObject
{
public:

	IPhysicsObject() = default;

	void updateGravity()
	{
		m_velocity += m_gravity;
	}

	void haltX() { m_velocity.x = 0; }

	void haltY() { m_velocity.y = 0; }

	void setVelocity(float x, float y)
	{
		m_velocity = { x, y };
	}
	void setVelocity(sf::Vector2f vec)
	{
		m_velocity = vec;
	}

	void addVelocity(float x, float y) { m_velocity += sf::Vector2f(x, y); }
	void addVelocity(sf::Vector2f vec) { m_velocity += vec; }

	void setGravity(float x, float y)
	{
		m_gravity = { x, y };
	}
	void setGravity(sf::Vector2f vec)
	{
		m_gravity = vec;
	}

	void insideCollision(sf::Sprite& moving_sprite, const sf::FloatRect& static_sprite);

	virtual sf::Vector2f outsideCollision(GameObject& moving_obj, const GameObject& static_obj)
	{
		sf::FloatRect r1 = moving_obj.getFloatRect();
		sf::FloatRect r2 = static_obj.getFloatRect();

		sf::Vector2f offset = shortestOffset(r1,r2);

		moving_obj.move(offset);

		return offset;
	}

private:

	sf::Vector2f shortestOffset(const sf::FloatRect& rect_1, const sf::FloatRect& rect_2)
	{
		std::optional<sf::FloatRect> rect = rect_1.findIntersection(rect_2);

		if (rect == std::nullopt)
		{
			return sf::Vector2f();
		}

		sf::Vector2f size = rect.value().size;
		sf::Vector2f offset;

		if (fabsf(size.x) <= fabsf(size.y))
		{
			offset = sf::Vector2f(size.x, 0);
			offset *= rect_1.position.x <= rect_2.position.x ? -1.f : 1.f;
		}
		else
		{
			offset = sf::Vector2f(0, size.y);
			offset *= rect_1.position.y <= rect_2.position.y ? -1.f : 1.f;
		}

		return offset;
	}

public:

	CollisionType e_collision_type = NONE;

protected:

	sf::Vector2f m_velocity = {0,0};
	sf::Vector2f m_gravity = {0,0};
};