
#include "Menu.h"


bool Menu::init(std::shared_ptr<sf::RenderWindow> window)
{
	m_window = window;

	if (!m_cormorant_Bold.openFromFile("Data/Fonts/Cormorant/static/Cormorant-Bold.ttf"))
	{
		printf("[ERROR] Cormorant failed to load...\n");
		return false;
	}

	m_return_text = ScalingText(m_cormorant_Bold, "Return");
	m_return_text.getText()->setOrigin(m_return_text.getText()->getGlobalBounds().getCenter());
	m_return_text.setPosition(sf::Vector2i(m_window->getSize() / 2u));
	m_return_text.setMaxScale({ 1.5,1.5 });

	m_return_text.setScalingFunction([](float t)->float {return (1 - cosf(3.14159 * t)) / 2.f; });

	return true;
}

void Menu::update(float dt)
{
	m_return_text.update(m_window, dt);
}

void Menu::render()
{
	m_window->draw(m_return_text.getText().value());
}

void Menu::keyPressed(const sf::Keyboard::Key& key)
{
	using namespace sf::Keyboard;
}

void Menu::mousePressed(const sf::Mouse::Button& button)
{
	using namespace sf::Mouse;

	sf::Vector2f mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(*m_window);

	if (button == Button::Left)
	{
		if (m_return_text.getText()->getGlobalBounds().contains(mouse_pos))
		{
			m_return_text.reset();
			m_current_state = START;
		}
	}
}
