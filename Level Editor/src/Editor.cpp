
#include "Editor.h"

bool Editor::init(std::string path)
{
	m_path = path;

	if (std::filesystem::exists(m_path))
	{
		std::vector<BlockData> data;

		std::string line;
		std::ifstream file(m_path);
		while (std::getline(file, line))
		{
			data.emplace_back();

			std::istringstream string = std::istringstream(line);
			std::string chars;
			for (int i = 0; i < BLOCK_DATA_POINTS; i++)
			{
				std::getline(string, chars, ',');
				data.back().data[i] = std::stoi(chars);
			}
		}
		createBlockArray(data);
	}

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
	if (m_path.length() == 0)
	{
		return;
	}

#if DEBUG == true
	return;
#endif


	printf("Saving file...\n");

	if(std::filesystem::exists(m_path))
	{
		std::remove(m_path.c_str());
	}

	std::ofstream file(m_path);

	std::string data;
	for (auto& block : blocks)
	{
		data = std::to_string((int)block.getPosition().x) + "," +
			std::to_string((int)block.getPosition().y) + "," +
			std::to_string(block.getSize().x) + "," +
			std::to_string(block.getSize().y) + "," +
			std::to_string(block.getType()) + "\n";

		file << data;
	}
}

void Editor::update()
{
	sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window));

	if (mouse_held)
	{
		sf::Vector2f size = (mouse_pos - m_mouse_start) / 32.f;
		size = { ceilf(size.x), ceilf(size.y) };
		size *= 32.f;

		if(size.x >= 0 && size.y >= 0)
		{
			m_outline_rect.setPosition(m_mouse_start);
			m_outline_rect.setSize(size);
		}
		else if(size.x < 0 && size.y < 0)
		{
			m_outline_rect.setPosition(m_mouse_start + size-sf::Vector2f(32,32));
			m_outline_rect.setSize(sf::Vector2f(fabsf(size.x)+64, fabsf(size.y)+64));
		}
		else if (size.x < 0)
		{
			m_outline_rect.setPosition(m_mouse_start + sf::Vector2f(size.x-32, 0));
			m_outline_rect.setSize(sf::Vector2f(fabsf(size.x)+64, size.y));
		}
		else if (size.y < 0)
		{
			m_outline_rect.setPosition(m_mouse_start + sf::Vector2f(0, size.y-32));
			m_outline_rect.setSize(sf::Vector2f(size.x, fabsf(size.y)+64));
		}
		
		if (size.x == 0)
		{
			m_outline_rect.setSize({ 32, m_outline_rect.getSize().y });
		}
		if (size.y == 0)
		{
			m_outline_rect.setSize({ m_outline_rect.getSize().x, 32 });
		}
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
		m_mouse_start = m_outline_rect.getPosition();
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

void Editor::createBlockArray(const std::vector<BlockData>& block_data)
{
	for (auto& datum : block_data)
	{
		blocks.emplace_back(
			sf::Vector2f(datum.position_x, datum.position_y), 
			sf::Vector2i(datum.width, datum.height), 
			m_texture,
			datum.block_type);
	}
}
