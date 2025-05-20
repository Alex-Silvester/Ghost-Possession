
#include "LevelSelect.h"

bool LevelSelect::init(std::shared_ptr<sf::RenderWindow> window)
{
	m_window = window;

	if (!m_font.openFromFile("Data/Fonts/Cormorant/static/Cormorant-Bold.ttf"))
	{
		printf("[ERROR] failed to load font: LevelSelect\n");
		return false;
	}

	std::function<float(float)> func = [](float t)->float {return (1 - cosf(3.14159f * t)) / 2.f; };

	m_level_1_select = ScalingText(m_font, "Level 1", true);
	m_level_1_select.setPosition((sf::Vector2i)m_window->getSize() / 2);
	m_level_1_select.setMaxScale({ 1.5,1.5 });
	m_level_1_select.setScalingFunction(func);

	m_level_2_select = ScalingText(m_font, "Level 2", true);
	m_level_2_select.setPosition((sf::Vector2i)m_window->getSize() / 2 + sf::Vector2i(0,75));
	m_level_2_select.setMaxScale({ 1.5,1.5 });
	m_level_2_select.setScalingFunction(func);

	m_return_text = ScalingText(m_font, "Return", true);
	m_return_text.setPosition(sf::Vector2i(m_window->getSize().x / 2, m_window->getSize().y - 75));
	m_return_text.setMaxScale({ 1.5,1.5 });
	m_return_text.setScalingFunction(func);

	return true;
}

void LevelSelect::update(float dt)
{
	m_level_1_select.update(m_window, dt);
	m_level_2_select.update(m_window, dt);

	m_return_text.update(m_window, dt);
}

void LevelSelect::render()
{
	m_window->draw(m_level_1_select.getText().value());
	m_window->draw(m_level_2_select.getText().value());

	m_window->draw(m_return_text.getText().value());
}

void LevelSelect::mousePressed(const sf::Mouse::Button& button)
{
	using namespace sf::Mouse;

	sf::Vector2f mouse_position = (sf::Vector2f)sf::Mouse::getPosition(*m_window);

	if (button == Button::Left)
	{
		if (m_level_1_select.getText()->getGlobalBounds().contains(mouse_position))
		{
			*level_ptr = 1;
			m_level_1_select.reset();
			m_current_state = PLAY;
		}

		if (m_level_2_select.getText()->getGlobalBounds().contains(mouse_position))
		{
			*level_ptr = 2;
			m_level_2_select.reset();
			m_current_state = PLAY;
		}

		if (m_return_text.getText()->getGlobalBounds().contains(mouse_position))
		{
			m_return_text.reset();
			m_current_state = START;
		}
	}
}

void LevelSelect::keyPressed(const sf::Keyboard::Key& key)
{
	using namespace sf::Keyboard;

	if (key == Key::Escape)
	{
		m_current_state = START;
	}
}