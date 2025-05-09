#pragma once

#include <SFML/graphics.hpp>

class GameObject : public sf::Drawable
{
public:

	GameObject() = default;
	GameObject(const sf::Texture& texture)
	{
		m_sprite = sf::Sprite(texture);
	}

	bool intersects(const sf::FloatRect& rect)
	{
		if (m_sprite.value().getGlobalBounds().findIntersection(rect) == std::nullopt)
		{
			return false;
		}
		return true;
	}

	sf::FloatRect getFloatRect()
	{
		return m_sprite.value().getGlobalBounds();
	}

	sf::Sprite& getSprite() { return m_sprite.value(); }

	//----------Position----------//
	void setPosition(float x, float y) { m_sprite.value().setPosition(sf::Vector2f(x, y)); };

	void setPosition(sf::Vector2f vec) { m_sprite.value().setPosition(vec); }

	template<typename T = float>
	sf::Vector2<T> getPosition() { return (sf::Vector2<T>)m_sprite.value().getPosition(); }

	void move(float x, float y) { m_sprite.value().move(sf::Vector2f(x, y)); }

	void move(sf::Vector2f vec) { m_sprite.value().move(vec); }
	//----------Position----------//

	//----------Visuals----------//
	void setColour(sf::Color col) { m_sprite.value().setColor(col); }

	void scale(float x, float y) { m_sprite.value().scale(sf::Vector2f(x, y)); }

	void scale(sf::Vector2f vec) { m_sprite.value().scale(vec); }

	void setTransparancey(float alpha) 
	{
		m_sprite.value().setColor(sf::Color(
			m_sprite.value().getColor().r,
			m_sprite.value().getColor().g,
			m_sprite.value().getColor().b, 
			alpha));
	}
	//----------Visuals----------//

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(m_sprite.value(), states);
	}

protected:

	std::optional<sf::Sprite> m_sprite;
};