
#include "Menu.h"


bool Menu::init(std::shared_ptr<sf::RenderWindow> window)
{
	m_window = window;

	if (!m_cormorant_Bold.openFromFile("Data/Fonts/Cormorant/static/Cormorant-Bold.ttf"))
	{
		printf("[ERROR] Cormorant failed to load...\n");
		return false;
	}

	m_game_name = ScalingText(m_cormorant_Bold, "The Ghost Possession");
	m_game_name.getText()->setOrigin(m_game_name.getText()->getGlobalBounds().getCenter());
	m_game_name.getText()->setPosition(sf::Vector2f(m_window->getSize() / 2u));
	m_game_name.setMaxScale({ 1.5,1.5 });

	m_game_name.setRate(3.f);
	m_game_name.setScalingFunction([](float t)->float {return (1.f - cosf(3.14159 * t)/2.f); });

	return true;
}

void Menu::update(float dt)
{
	if (m_game_name.getText()->getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*m_window)))
	{
		m_game_name.lerpUp(dt);
	}
	else
	{
		m_game_name.lerpDown(dt);
	}
}

void Menu::render()
{
	m_window->draw(m_game_name.getText().value());
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
		if (m_game_name.getText()->getGlobalBounds().contains(mouse_pos))
		{
			m_game_name.reset();
			m_current_state = LEVEL_SELECT;
		}
	}
}
