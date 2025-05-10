#include "Game.h"

Game* Game::sm_game_ptr = nullptr;

#define DEBUG_STEP false

Game::Game()
{
	printf("Created Game\n");
}

Game::~Game()
{
	if (sm_game_ptr != nullptr)
	{
		delete sm_game_ptr;
		sm_game_ptr = nullptr;
	}
}
Game& Game::get()
{
	if (sm_game_ptr == nullptr)
	{
		sm_game_ptr = new Game();
	}

	return *sm_game_ptr;
}

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

		
		while (const std::optional<sf::Event> event = m_window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				m_window->close(); return true;
			}
			if (event->is<sf::Event::KeyPressed>())
			{
				if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
				{
					m_window->close(); return true;
				}

				playground.keyPressed(event.value());
			}
			if (event->is<sf::Event::KeyReleased>())
				playground.keyReleased(event.value());
			if (event->is<sf::Event::MouseButtonPressed>())
				playground.mousePressed(event.value());
			if (event->is<sf::Event::MouseButtonReleased>())
				playground.mouseReleased(event.value());
		}

		m_window->clear(sf::Color::Black);

#if DEBUG_STEP == true
		if (m_window->waitEvent().value().is<sf::Event::KeyPressed>())
		{
			playground.update(dt);
		}
#else
		playground.update(dt);

		if (time_elapsed > 1.f)
		{
			time_elapsed -= 1.f;
			printf("\x1b[1A\x1b[2K%f %f %d\n", 1.f / dt, dt, updates);
		}
#endif
		playground.render();

		m_window->display();
	}

	return true;
}

void Game::end()
{
	if (m_window != nullptr)
	{
		m_window->close();
	}
}
