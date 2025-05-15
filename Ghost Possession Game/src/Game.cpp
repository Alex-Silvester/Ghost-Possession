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
	addState<Menu>(States::MENU);
	addState<LevelSelect>(States::LEVEL_SELECT);

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

		m_current_state = m_states[m_current_state]->getCurrentState();
		
		while (const std::optional<sf::Event> event = m_window->pollEvent())
		{
			using namespace sf;

			if (event->is<Event::Resized>())
			{
				sf::Vector2f size = static_cast<sf::Vector2f>(m_window->getSize());
				m_window->setView(sf::View(sf::FloatRect(sf::Vector2f(), size)));
			}
			if (event->is<Event::Closed>())
			{
				m_window->close(); return true;
			}
			if (event->is<Event::KeyPressed>())
			{
				if (event->getIf<Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
				{
					m_window->close(); return true;
				}

				m_states[m_current_state]->keyPressed(event.value().getIf<Event::KeyPressed>()->code);
			}
			if (event->is<sf::Event::KeyReleased>())
				m_states[m_current_state]->keyReleased(event.value().getIf<Event::KeyReleased>()->code);
			if (event->is<sf::Event::MouseButtonPressed>())
				m_states[m_current_state]->mousePressed(event.value().getIf<Event::MouseButtonPressed>()->button);
			if (event->is<sf::Event::MouseButtonReleased>())
				m_states[m_current_state]->mouseReleased(event.value().getIf<Event::MouseButtonReleased>()->button);
		}

		m_window->clear(sf::Color::Black);


		m_states[m_current_state]->update(dt);

		if (time_elapsed > 1.f)
		{
			time_elapsed -= 1.f;
			//printf("\x1b[1A\x1b[2K%f %f %d\n", 1.f / dt, dt, updates);
		}
		m_states[m_current_state]->render();

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
