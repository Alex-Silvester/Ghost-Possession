#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class ScalingText
{
public:

	ScalingText() = default;

	ScalingText(const sf::Font& font, sf::String string = "", bool set_origin_to_centre = false)
	{
		m_text = sf::Text(font, string);

		if (set_origin_to_centre)
		{
			m_text->setOrigin(m_text->getGlobalBounds().getCenter());
		}
	}

	std::optional<sf::Text>& getText()
	{
		return m_text;
	}

	void setScalingFunction(std::function<float(float)> func)
	{
		m_scaling_function = func;
	}

	void setDefaultScale(sf::Vector2f vec)
	{
		m_text->setScale(vec);
		m_default_scale = vec;
	}

	void setMaxScale(sf::Vector2f vec)
	{
		m_max_scale = vec;
	}

	void setRate(float rate)
	{
		m_rate = rate;
	}

	void lerpUp(float dt)
	{
		m_t += m_t < 1 ? m_rate * dt : 0;

		lerpScale();
	}

	void lerpDown(float dt)
	{
		m_t -= m_t > 0 ? m_rate * dt : 0;

		lerpScale();
	}

	void reset()
	{
		m_t = -0.f;
		m_text->setScale((sf::Vector2f)m_default_scale);
	}

	void update(std::shared_ptr<sf::RenderWindow>& window, float dt)
	{
		if (m_text->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window)))
		{
			lerpUp(dt);
		}
		else
		{
			lerpDown(dt);
		}
	}

	bool press(sf::Vector2i position)
	{
		return m_text->getGlobalBounds().contains((sf::Vector2f)position);
	}

	void setPosition(int x, int y)
	{
		m_text->setPosition(sf::Vector2f(x, y));
	}
	void setPosition(sf::Vector2i vec)
	{
		m_text->setPosition((sf::Vector2f)vec);
	}

private:

	void lerpScale()
	{
		if (m_t <= 0)
		{
			m_text->setScale((sf::Vector2f)m_default_scale);
		}
		else if (m_t >= 1)
		{
			m_text->setScale((sf::Vector2f)m_max_scale);
		}
		else
		{
			m_text->setScale((sf::Vector2f)m_default_scale + (sf::Vector2f)(m_max_scale - m_default_scale) * m_scaling_function(m_t));
		}
	}

private:
	
	std::optional<sf::Text> m_text;

	sf::Vector2f m_default_scale = {1,1};
	sf::Vector2f m_max_scale = { 1,1 };

	float m_rate = 10.f;

	float m_t = 0.f;

	std::function<float(float)> m_scaling_function = [](float t)->float {return t; };
};