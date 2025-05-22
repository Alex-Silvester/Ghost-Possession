
#include "Editor.h"

bool Editor::init(std::string path)
{
	m_path = path;

	m_outline_rect.setFillColor(sf::Color(255, 255, 255, 90));
	m_outline_rect.setOutlineColor(sf::Color::White);
	m_outline_rect.setOutlineThickness(3.f);

	return true;
}

void Editor::run()
{

	sf::Clock clock;
	float time_elapsed = 0;
	int updates = 0;

	printf("\n");

	while (m_window.isOpen())
	{
		float dt = clock.restart().asSeconds();

		while (const std::optional<sf::Event> event = m_window.pollEvent())
		{
			using namespace sf;

			if (event->is<Event::Resized>())
			{
				sf::Vector2f size = static_cast<sf::Vector2f>(m_window.getSize());
				m_window.setView(sf::View(sf::FloatRect(sf::Vector2f(), size)));
			}
			if (event->is<Event::Closed>())
			{
				m_window.close();
			}
			if (event->is<Event::KeyPressed>())
				keyPressed(event.value().getIf<Event::KeyPressed>()->code);
			if (event->is<sf::Event::KeyReleased>())
				keyReleased(event.value().getIf<Event::KeyReleased>()->code);
			if (event->is<sf::Event::MouseButtonPressed>())
				mousePressed(event.value().getIf<Event::MouseButtonPressed>()->button);
			if (event->is<sf::Event::MouseButtonReleased>())
				mouseReleased(event.value().getIf<Event::MouseButtonReleased>()->button);
		}

		if (m_window.isOpen())
		{
			m_window.clear(sf::Color::Black);
			update();
			render();
			m_window.display();
		}
	}

}

#define DEBUG true
void Editor::end()
{
#if DEBUG == false
	if (path.length() == 0)
	{
		return;
	}
#endif

	std::string data;
	for (auto& block : blocks)
	{
		data = std::to_string((int)block.getPosition().x) + "," +
			std::to_string((int)block.getPosition().y) + "," +
			std::to_string(block.getSize().x) + "," +
			std::to_string(block.getSize().y) + "," +
			std::to_string(block.getType()) + "\n";

		std::cout << data;
	}
}

void Editor::update()
{
	sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));

	if (mouse_held)
	{
		sf::Vector2f size = (mouse_pos - m_outline_rect.getPosition()) / 32.f;
		size = { ceilf(size.x), ceilf(size.y) };
		size *= 32.f;

		if(size.x >= 0 && size.y >= 0)
			m_outline_rect.setSize(size);
	}

}

void Editor::render()
{
	for (auto& block : blocks)
	{
		m_window.draw(block);
	}

	m_window.draw(m_outline_rect);
}

void Editor::keyPressed(const sf::Keyboard::Key& key)
{
}

void Editor::keyReleased(const sf::Keyboard::Key& key)
{
}

void Editor::mousePressed(const sf::Mouse::Button& button)
{
	using namespace sf::Mouse;

	sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));

	if (button == Button::Left)
	{
		m_outline_rect.setPosition(sf::Vector2f(floorf(mouse_pos.x/32.f), floorf(mouse_pos.y/32.f))*32.f);
		mouse_held = true;
	}

}

void Editor::mouseReleased(const sf::Mouse::Button& button)
{
	if (mouse_held && m_outline_rect.getSize().x > 0 && m_outline_rect.getSize().y > 0)
	{
		blocks.emplace_back(m_outline_rect.getPosition(), (sf::Vector2i)m_outline_rect.getSize() / 32, m_texture);
	}

	mouse_held = false;
	m_outline_rect.setSize({ 0,0 });
	m_outline_rect.setPosition({ -1,-1 });
}
