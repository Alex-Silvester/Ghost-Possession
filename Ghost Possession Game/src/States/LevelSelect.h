#pragma once

#include "State.h"

class LevelSelect : public State
{
public:

	LevelSelect() : State(LEVEL_SELECT) {}

	void keyPressed(const sf::Keyboard::Key& key) override
	{
		using namespace sf::Keyboard;

		if (key == Key::A)
		{
			m_current_state = MENU;
		}
	}

	void render() override
	{
		m_window->draw(sf::RectangleShape({ 30,30 }));
	}

private:

};