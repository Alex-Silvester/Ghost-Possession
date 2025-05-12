#include "GameObject.h"

GameObject::GameObject(const sf::Texture& texture)
{
	m_sprite = sf::Sprite(texture);
}

void GameObject::selectTextureView(sf::Vector2i size, sf::Vector2i position)
{
	sf::Vector2f scale_increase =
	{
		(float)size.x / m_sprite->getGlobalBounds().size.x,
		(float)size.y / m_sprite->getGlobalBounds().size.y
	};

	printf("%f %f\n", scale_increase.x, scale_increase.y);

	m_sprite->setTextureRect(sf::IntRect(position, size));

	m_sprite->setScale({ m_sprite->getScale().x / scale_increase.x, m_sprite->getScale().y / scale_increase.y });

}

bool GameObject::intersects(const sf::FloatRect& rect)
{
	if (m_sprite.value().getGlobalBounds().findIntersection(rect) == std::nullopt)
	{
		return false;
	}
	return true;
}

sf::FloatRect GameObject::getFloatRect()
{
	return m_sprite.value().getGlobalBounds();
}

sf::Sprite& GameObject::getSprite()
{
	return m_sprite.value();
}

void GameObject::setPosition(float x, float y)
{
	m_sprite.value().setPosition(sf::Vector2f(x, y));
}

void GameObject::setPosition(sf::Vector2f vec)
{
	m_sprite.value().setPosition(vec);
}

sf::Vector2f GameObject::getPosition()
{
	return m_sprite.value().getPosition();
}

void GameObject::move(float x, float y)
{
	m_sprite.value().move(sf::Vector2f(x, y));
}

void GameObject::move(sf::Vector2f vec)
{
	m_sprite.value().move(vec);
}

void GameObject::setColour(sf::Color col)
{
	m_sprite.value().setColor(col);
}

void GameObject::scale(float x, float y)
{
	m_sprite.value().scale(sf::Vector2f(x, y));
}

void GameObject::scale(sf::Vector2f vec)
{
	m_sprite.value().scale(vec);
}

void GameObject::setTransparancey(float alpha)
{
	m_sprite.value().setColor(sf::Color(
		m_sprite.value().getColor().r,
		m_sprite.value().getColor().g,
		m_sprite.value().getColor().b,
		alpha));
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite.value(), states);
}
