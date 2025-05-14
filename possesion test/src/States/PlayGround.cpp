
#include "PlayGround.h"

bool PlayGround::init(std::shared_ptr<sf::RenderWindow> window)
{
	State::init(window);

	if (!m_player_texture.loadFromFile("../possesion test/Data/Ghost.png"))
	{
		printf("[ERROR] Failed to load player texture\n");
		return false;
	}

	m_player = Player();
	m_player.generateTexture({ {0} }, { 14,12 }, &m_player_texture);
	m_player.init({ 0,cst::s_gravity });
	m_player.scale(4, 4);

	if (!m_box_texture.loadFromFile("../possesion test/Data/Stone Tile Map.png"))
	{
		printf("[ERROR] Failed to load Block texture\n");
		return false;
	}

	std::vector<lt::BlockData> block_data = lt::readBlockData("Data/Levels/test_level.txt");

	m_boxes = lt::createBlockArray(block_data, &m_box_texture);

	return true;
}

void PlayGround::update(float dt)
{
	m_player.update(dt);

	if(!m_player.isPossessingObject())
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
					temp->flash(sf::Color(255, 180, 150), 0.5f);
				}
				//otherwise reset the box's colour back to white
				else
				{
					temp->resetFlash();
				}
			}
		}
	}
	else if(PObject* obj = dynamic_cast<PObject*>(m_player.getPossessedObject()))
	{
		for(auto& box : m_boxes)
		{
			if(obj != box)
				physicsCollision(*obj, *box);
		}
	}
}

#define PLAYER_POS_CHECK false
void PlayGround::render()
{
#if PLAYER_POS_CHECK == false
	m_window->draw(m_player);
#endif
	for(auto& box : m_boxes)
	{
		m_window->draw(*box);
	}

#if PLAYER_POS_CHECK == true
	m_window->draw(m_player);
#endif
}

void PlayGround::keyPressed(const sf::Event& event)
{
	if (m_player.isPossessingObject())
	{
		m_player.getPossessedObject()->keyPressed(event);
	}
	else
	{
		m_player.keyPressed(event);
	}

	if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::LControl)
	{
		if(m_player.isPossessingObject())
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
			}
		}
	}
	if (event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::F1)
	{
		m_player.setPosition({ 0,0 });
	}
}

void PlayGround::keyReleased(const sf::Event& event)
{
	if (m_player.isPossessingObject())
	{
		m_player.getPossessedObject()->keyReleased(event);
	}
	else
	{
		m_player.keyReleased(event);
	}
}

void PlayGround::mousePressed(const sf::Event& event)
{
}

void PlayGround::mouseReleased(const sf::Event& event)
{
}

void PlayGround::physicsCollision(GameObject& moving_obj, GameObject& static_obj)
{
	if (moving_obj.intersects(static_obj.getFloatRect()))
	{
		if(auto temp = dynamic_cast<IPhysicsObject*>(&moving_obj))
		{
			temp->outsideCollision(moving_obj, static_obj);
		}
	}
}
