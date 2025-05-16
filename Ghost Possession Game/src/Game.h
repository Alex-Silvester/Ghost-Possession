#pragma once

#include <map>

#include <SFML/graphics.hpp>

#include "States/States.h"

class Game
{
public:

	Game(const Game& game) = delete;
	Game operator=(const Game& game) = delete;

	~Game();

	static Game& get();

	bool init(unsigned int max_fps = 0);

	bool run();

	void end();

private:

	Game();

	template<typename T>
	bool addState(States state)
	{
		m_states.emplace(state, std::make_unique<T>());
		return m_states[state]->init(m_window);
	}

private:

	static Game* sm_game_ptr;

	std::shared_ptr<sf::RenderWindow> m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode({ 1080,720 }), "The Ghost Possession");

	std::unordered_map<States, std::unique_ptr<State>> m_states;
	States m_current_state = START;
};