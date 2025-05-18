#pragma once

#include "State.h"

class Play : public State
{
public:

	Play() : State(PLAY) {}

	void update(float dt) override
	{
		printf("level %d\n", m_level);
	}

	void keyPressed(const sf::Keyboard::Key& key)
	{
		using namespace sf::Keyboard;
		if (key == Key::A)
		{
			m_level = 0;
			m_current_state = LEVEL_SELECT;
		}
	}

	int* getLevelPtr() { return &m_level; }

private:

	int m_level = 0;

};