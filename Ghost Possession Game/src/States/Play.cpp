
#include "Play.h"

Play::~Play()
{
	for (auto& box : m_boxes)
	{
		delete box;
	}
	m_boxes.clear();
}

bool Play::init(std::shared_ptr<sf::RenderWindow> window)
{
	m_window = window;

	if (!m_box_texture->loadFromFile("Data/Textures/Stone Tile Map.png"))
	{
		printf("[ERROR] failed to load texture: Play -> box texture\n");
		return false;
	}

	if (!m_player_texture->loadFromFile("Data/Textures/Ghost.png"))
	{
		printf("[ERROR] failed to load texture: Play -> player texture\n");
	}

	m_player.init(m_player_texture, { 4.f,4.f });

	return true;
}

void Play::update(float dt)
{
	if (m_boxes.size() == 0 && std::filesystem::exists("Data/Levels/Level_" + std::to_string(m_level) + ".txt"))
	{
		m_boxes = lt::createBlockArray(lt::readBlockData("Data/Levels/Level_"+std::to_string(m_level)+".txt"), m_box_texture);
	}
}

void Play::render()
{
	for (auto& box : m_boxes)
	{
		m_window->draw(*box);
	}

	m_window->draw(m_player);
}

void Play::keyPressed(const sf::Keyboard::Key& key)
{
	using namespace sf::Keyboard;
	if (key == Key::Escape)
	{
		m_level = 0;

		for (auto& box : m_boxes)
		{
			delete box;
		}
		m_boxes.clear();

		m_current_state = LEVEL_SELECT;
	}
}

void Play::reset()
{

}
