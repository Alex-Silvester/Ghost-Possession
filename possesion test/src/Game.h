#pragma once

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

public:

private:

	Game();

private:

	static Game* sm_game_ptr;

	std::shared_ptr<sf::RenderWindow> m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode({ 720,540 }), "Game");

	PlayGround playground;

};