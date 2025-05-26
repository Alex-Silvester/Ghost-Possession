
#include "Win.h"

bool Win::init(std::shared_ptr<sf::RenderWindow> window)
{
	m_window = window;

	if (!m_font.openFromFile("Data/Fonts/Cormorant/static/Cormorant-Bold.ttf"))
	{
		printf("[ERROR] Font failed to load...\n");
		return false;
	}

	std::function<float(float)> func = [](float t)->float {return (1 - cosf(3.14159 * t)) / 2.f; };

	m_return_text = ScalingText(m_font, "Return", true);
	m_return_text.setMaxScale({ 1.5, 1.5 });
	m_return_text.setScalingFunction(func);
	m_return_text.setPosition((sf::Vector2i)m_window->getSize() / 2);

	return true;
}

void Win::update(float dt)
{
	m_return_text.update(m_window, dt);
}

void Win::render()
{
	m_window->draw(m_return_text.getText().value());
}

void Win::mousePressed(const sf::Mouse::Button& button)
{
	using namespace sf::Mouse;
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*m_window);

	if (m_return_text.press(mouse_pos))
	{
		m_return_text.reset();
		m_current_state = LEVEL_SELECT;
	}
}
