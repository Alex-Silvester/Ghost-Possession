
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

	//should use a dictionary and going through the files like the 
	// levels in level selection menu
	if (!m_box_texture->loadFromFile("Data/Textures/Stone Tile Map.png"))
	{
		printf("[ERROR] failed to load texture: Play -> box texture\n");
		return false;
	}

	if (!m_player_texture->loadFromFile("Data/Textures/Ghost.png"))
	{
		printf("[ERROR] failed to load texture: Play -> player texture\n");
	}

	if (!m_flag_texture->loadFromFile("Data/Textures/Small Flag.png"))
	{
		printf("[ERROR] failed to load texture: Play -> flag texture\n");
	}

	m_player.init(m_player_texture, { 4.f,4.f });

	return true;
}

void Play::update(float dt)
{
	if (m_current_state != PLAY)
	{
		return;
	}

	if (m_boxes.size() == 0 && std::filesystem::exists("Data/Levels/Level_" + std::to_string(m_level) + ".txt"))
	{
		m_start.emplace();
		m_end.emplace();

		m_start->init(m_flag_texture, { 8,8 });
		m_end->init(m_flag_texture, { 8,8 });

		m_boxes = lt::createBlockArray(
			lt::readBlockData("Data/Levels/Level_" + std::to_string(m_level) + ".txt"),
			m_box_texture, {&m_start.value(), &m_end.value()});

		m_player.setPosition(m_start->getPosition());
	}

	m_player.update(dt);

	m_window->setView(sf::View(m_player.getFloatRect().getCenter(), (sf::Vector2f)m_window->getSize()));

	if (!m_player.isPossessingObject())
	{
		//if the player is intersecting with the end flag, they win
		if (m_player.intersects(m_end->getFloatRect()))
		{
			reset();
			m_current_state = WIN;
			return;
		}

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
					temp->flash(sf::Color(255, 150, 100), cst::s_flash_rate * dt);
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
		//if the object the player is possessing is intersecting the end flag,
		// they win
		if (obj->intersects(m_end->getFloatRect()))
		{
			reset();
			m_current_state = WIN;
			return;
		}
		for (auto& box : m_boxes)
		{
			if (obj != box)
				physicsCollision(*obj, *box);
		}
	}
}

void Play::render()
{
	if (m_current_state != PLAY)
	{
		return;
	}

	if(m_start.has_value())
	{
		m_window->draw(m_start.value());
	}
	if(m_end.has_value())
	{
		m_window->draw(m_end.value());
	}

	m_window->draw(m_player);
	
	for (auto& box : m_boxes)
	{
		m_window->draw(*box);
	}
}

void Play::keyPressed(const sf::Keyboard::Key& key)
{
	using namespace sf::Keyboard;

	if (m_player.isPossessingObject())
	{
		m_player.getPossessedObject()->keyPressed(key);
	}
	else
	{
		m_player.keyPressed(key);
	}

	if (key == Key::Escape)
	{
		reset();

		m_current_state = LEVEL_SELECT;
	}

	if (key == Key::LControl)
	{
		if (m_player.isPossessingObject())
		{
			m_player.unpossess();
			return;
		}
		for (auto& box : m_boxes)
		{
			sf::Vector2f size = { m_player.getPossessionDist(), m_player.getPossessionDist() };
			sf::FloatRect possession_detector(m_player.getFloatRect().getCenter() - size / 2.f, size);

			if (!box->intersects(possession_detector))
			{
				continue;
			}
			if (auto temp = dynamic_cast<IPossessable*>(box))
			{
				m_player.possess(temp);
				break;
			}
		}
	}
}

void Play::keyReleased(const sf::Keyboard::Key& key)
{
	if (m_player.isPossessingObject())
	{
		m_player.getPossessedObject()->keyReleased(key);
	}
	else
	{
		m_player.keyReleased(key);
	}
}

void Play::reset()
{
	m_level = 0;

	m_player.unpossess();
	for (auto& box : m_boxes)
	{
		delete box;
	}
	m_boxes.clear();

	m_start.reset();
	m_end.reset();
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
