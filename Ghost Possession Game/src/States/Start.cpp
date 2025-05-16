
#include "Start.h"

bool Start::init(std::shared_ptr<sf::RenderWindow> window)
{
	m_window = window;

	if (!m_font.openFromFile("Data/Fonts/Cormorant/static/Cormorant-Bold.ttf"))
	{
		printf("[ERROR] Font failed to load...\n");
		return false;
	}

	std::function<float(float)> func = [](float t)->float {return (1 - cosf(3.14159 * t)) / 2.f; };

	m_play_text = ScalingText(m_font, "Play", true);
	m_play_text.setMaxScale({ 1.5, 1.5 });
	m_play_text.setScalingFunction(func);
	m_play_text.setPosition((sf::Vector2i)m_window->getSize() / 2);

	m_menu_text = ScalingText(m_font, "Options", true);
	m_menu_text.setMaxScale({ 1.5, 1.5 });
	m_menu_text.setScalingFunction(func);
	m_menu_text.setPosition((sf::Vector2i)m_window->getSize() / 2 + sf::Vector2i(0, 75));

	m_quit_text = ScalingText(m_font, "Quit", true);
	m_quit_text.setMaxScale({ 1.5, 1.5 });
	m_quit_text.setScalingFunction(func);
	m_quit_text.setPosition((sf::Vector2i)m_window->getSize() / 2 + sf::Vector2i(0, 150));

	return true;
}

void Start::update(float dt)
{
	m_play_text.update(m_window, dt);
	m_menu_text.update(m_window, dt);
	m_quit_text.update(m_window, dt);
}

void Start::render()
{
	m_window->draw(m_play_text.getText().value());
	m_window->draw(m_menu_text.getText().value());
	m_window->draw(m_quit_text.getText().value());
}

void Start::mousePressed(const sf::Mouse::Button& key)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*m_window);

	if (m_play_text.press(mouse_pos))
	{
		m_play_text.reset();
		m_current_state = PLAY;
	}

	if (m_menu_text.press(mouse_pos))
	{
		m_menu_text.reset();
		m_current_state = MENU;
	}

	if (m_quit_text.press(mouse_pos))
	{
		m_quit_text.reset();
		m_window->close();
	}
}
