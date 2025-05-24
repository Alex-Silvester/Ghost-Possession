
#include "LevelSelect.h"

bool LevelSelect::init(std::shared_ptr<sf::RenderWindow> window)
{
	m_window = window;

	if (!m_font.openFromFile("Data/Fonts/Cormorant/static/Cormorant-Bold.ttf"))
	{
		printf("[ERROR] failed to load font: LevelSelect\n");
		return false;
	}

	std::function<float(float)> func = [](float t)->float {return (1 - cosf(3.14159f * t)) / 2.f; };

	m_return_text = ScalingText(m_font, "Return", true);
	m_return_text.setPosition(sf::Vector2i(m_window->getSize().x / 2, m_window->getSize().y - 75));
	m_return_text.setMaxScale({ 1.5,1.5 });
	m_return_text.setScalingFunction(func);

	//go through all of the paths in the levels folder and create a piece of text
	//that will load that level when pressed
	int idx = 0;
	std::string path = "Data/Levels";
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::string file_name = entry.path().filename().generic_string().replace(5, 1, " ").replace(7, 4, "");
		std::cout << file_name << std::endl;

		m_level_select_text.emplace_back(ScalingText(m_font, file_name, true));
		m_level_select_text.back().setPosition((sf::Vector2i)m_window->getSize() / 2 + sf::Vector2i(0, idx*75));
		m_level_select_text.back().setMaxScale({ 1.5,1.5 });
		m_level_select_text.back().setScalingFunction(func);

		idx++;
	}

	return true;
}

void LevelSelect::update(float dt)
{
	for (auto& level_text : m_level_select_text)
	{
		level_text.update(m_window, dt);
	}

	m_return_text.update(m_window, dt);
}

void LevelSelect::render()
{
	for (auto& level_text : m_level_select_text)
	{
		m_window->draw(level_text.getText().value());
	}

	m_window->draw(m_return_text.getText().value());
}

void LevelSelect::mousePressed(const sf::Mouse::Button& button)
{
	using namespace sf::Mouse;

	sf::Vector2f mouse_position = (sf::Vector2f)sf::Mouse::getPosition(*m_window);

	if (button == Button::Left)
	{
		//go through all of the levels on screen and if one is pressed, go to that level
		//(current standart level naming requires the "name" to be a number, might change later)
		int idx = 1;
		for (auto& level_text : m_level_select_text)
		{
			if (level_text.getText()->getGlobalBounds().contains(mouse_position))
			{
				*level_ptr = idx;
				level_text.reset();
				m_current_state = PLAY;
			}
			idx++;
		}

		if (m_return_text.getText()->getGlobalBounds().contains(mouse_position))
		{
			m_return_text.reset();
			m_current_state = START;
		}
	}
}

void LevelSelect::keyPressed(const sf::Keyboard::Key& key)
{
	using namespace sf::Keyboard;

	if (key == Key::Escape)
	{
		m_current_state = START;
	}
}