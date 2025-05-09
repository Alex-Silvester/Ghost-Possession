#pragma once

#include <SFML/graphics.hpp>

#include "States/States.h"

class Game
{
public:

	Game(const Game& game) = delete;
	Game operator=(const Game& game) = delete;

	~Game()
	{
		if (sm_game_ptr != nullptr)
		{
			delete sm_game_ptr;
			sm_game_ptr = nullptr;
		}
	}

	static Game& get()
	{
		if (sm_game_ptr == nullptr)
		{
			sm_game_ptr = new Game();
		}

		return *sm_game_ptr;
	}

	bool init(unsigned int max_fps = 0);

	bool run();

	void end()
	{
		if (m_window != nullptr)
		{
			m_window->close();
		}
	}

public:

private:

	Game()
	{
		printf("Created Game\n");
	}

private:

	static Game* sm_game_ptr;

	std::shared_ptr<sf::RenderWindow> m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode({ 720,540 }), "Game");

	PlayGround playground;

};