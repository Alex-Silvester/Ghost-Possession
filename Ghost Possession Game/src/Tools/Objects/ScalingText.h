#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class ScalingText
{
public:

	ScalingText() = default;

	ScalingText(const sf::Font& font, sf::String string = "")
	{
		m_text = sf::Text(font, string);
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
		m_text->setScale(m_default_scale);
	}

private:

	void lerpScale()
	{
		m_text->setScale(m_default_scale + (m_max_scale - m_default_scale) * m_scaling_function(m_t));
	}

private:
	
	std::optional<sf::Text> m_text;

	sf::Vector2f m_default_scale = {1,1};
	sf::Vector2f m_max_scale = { 1,1 };

	float m_rate = 0.1f;

	float m_t = 0.f;

	std::function<float(float)> m_scaling_function = [](float t)->float {return t; };
};