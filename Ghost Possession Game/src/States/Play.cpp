
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

	m_player.update(dt);

	if (!m_player.isPossessingObject())
	{
		for (auto& box : m_boxes)
		{
			//do the player's collision between them and all of the boxes
			physicsCollision(m_player, *box);

			//check if the current box is a possessable objext
			if (!dynamic_cast<IPossessable*>(box))
			{
				continue;
			}

			sf::Vector2f size = { m_player.getPossessionDist(), m_player.getPossessionDist() };
			sf::FloatRect possession_detector(m_player.getFloatRect().getCenter() - size / 2.f, size);

			//if the box's type is PObject, check if the player's possession area collides
			if (auto temp = dynamic_cast<PObject*>(box))
			{
				//if the players possession area collides, flash the box to indicate
				if (temp->intersects(possession_detector))
				{
					temp->flash(sf::Color(255, 150, 100), 1.3f * dt);
				}
				//otherwise reset the box's colour back to white
				else
				{
					temp->resetFlash();
				}
			}
		}
	}
	else if (PObject* obj = dynamic_cast<PObject*>(m_player.getPossessedObject()))
	{
		for (auto& box : m_boxes)
		{
			if (obj != box)
				physicsCollision(*obj, *box);
		}
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

	if (!m_player.isPossessingObject())
	{
		m_player.keyPressed(key);
	}

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

void Play::keyReleased(const sf::Keyboard::Key& key)
{
	if (!m_player.isPossessingObject())
	{
		m_player.keyReleased(key);
	}
}

void Play::reset()
{

}

void Play::physicsCollision(Visual& moving_obj, const Visual& static_obj)
{
	if (moving_obj.intersects(static_obj.getFloatRect()))
	{
		if (auto temp = dynamic_cast<IPhysicsObject*>(&moving_obj))
		{
			temp->outsideCollision(moving_obj, static_obj);
		}
	}
}
