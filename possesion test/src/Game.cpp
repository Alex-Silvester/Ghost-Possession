#include "Game.h"

Game* Game::sm_game_ptr = nullptr;

bool Game::init(unsigned int max_fps)
{

	if (!playground.init(m_window))
	{
		printf("[ERROR] playerground init\n");
		return false;
	}
	printf("Playground initialised\n");

	m_window->setFramerateLimit(max_fps);
	return true;
}

bool Game::run()
{

	sf::Clock clock;
	float time_elapsed = 0;
	int updates = 0;

	printf("\n");

	while (m_window->isOpen())
	{

		float dt = clock.restart().asSeconds();
		time_elapsed += dt;
		updates += 1;

		if (time_elapsed > 1.f)
		{
			time_elapsed -= 1.f;
			printf("\x1b[1A\x1b[2K%f %f %d\n", 1.f / dt, dt, updates);
		}
		
		while (const std::optional<sf::Event> event = m_window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				m_window->close(); return true;
			}
		}

		m_window->clear(sf::Color::Black);

		playground.update();
		playground.render();

		m_window->display();
	}

	return true;
}