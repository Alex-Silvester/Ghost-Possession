
#include "Menu.h"


bool Menu::init(std::shared_ptr<sf::RenderWindow> window)
{
	m_window = window;

	if (!m_cormorant_Bold.openFromFile("Data/Fonts/Cormorant/static/Cormorant-Bold.ttf"))
	{
		printf("[ERROR] Cormorant failed to load...\n");
		return false;
	}

	m_game_name = sf::Text(m_cormorant_Bold, "The Ghost Possession");
	m_game_name->setOrigin(m_game_name->getGlobalBounds().getCenter());
	m_game_name->setPosition(sf::Vector2f(m_window->getSize() / 2u));

	return true;
}

void Menu::update(float dt)
{
	if (m_game_name->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*m_window)))
	{
		m_game_name->setFillColor(sf::Color::Green);
	}
	else
	{
		m_game_name->setFillColor(sf::Color::White);
	}
}

void Menu::render()
{
	m_window->draw(m_game_name.value());
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
		if (m_game_name->getGlobalBounds().contains(mouse_pos))
		{
			m_current_state = LEVEL_SELECT;
		}
	}
}
