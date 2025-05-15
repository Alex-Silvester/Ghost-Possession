#pragma once

#include "State.h"

class Menu : public State
{
public:

	Menu() : State(MENU) {}

	void keyPressed(const sf::Keyboard::Key& key) override
	{
		using namespace sf::Keyboard;
		if (key == Key::A)
		{
			m_current_state = States::LEVEL_SELECT;
		}
	}

	void render() override
	{
		m_window->draw(sf::CircleShape(15.f));
	}

private:

};