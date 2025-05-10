
#include "PlayGround.h"

bool PlayGround::init(std::shared_ptr<sf::RenderWindow> window)
{
	State::init(window);

	if (!m_player_texture.loadFromFile("../possesion test/Data/Ghost.png"))
	{
		printf("[ERROR] Failed to load player texture\n");
		return false;
	}

	m_player = Player(m_player_texture);
	m_player.init({ 0,cst::s_gravity });
	m_player.scale(4, 4);

	if (!m_box_texture.loadFromFile("../possesion test/Data/yellow_block.png"))
	{
		printf("[ERROR] Failed to load player texture\n");
		return false;
	}

	m_box = Box(m_box_texture);
	m_box.scale(12,12);

	m_box.setPosition(0, 300);

	return true;
}

void PlayGround::update(float dt)
{
	m_player.update(dt);

	//if player intersects with a block
	if (m_player.intersects(m_box.getFloatRect()))
	{
		//if the player is moved up from the block
		if (m_player.outsideCollision(m_player.getSprite(), m_box.getFloatRect()).y < 0)
		{
			//the player is on the ground (set velocity to 0 to stop adding too much velocity)
			m_player.isGrounded();
		}
	}
}

void PlayGround::render()
{
	m_window->draw(m_player);
	m_window->draw(m_box);
}

void PlayGround::keyPressed(const sf::Event& event)
{
	using namespace sf::Keyboard;
	Key code = event.getIf<sf::Event::KeyPressed>()->code;

	if (code == Key::Space)
	{
		m_player.jump(350.f);
	}
	if (code == Key::A && !keyHeld.A)
	{
		keyHeld.A = true;
		m_player.addVelocity(-100.f, 0);
	}
	if (code == Key::D && !keyHeld.D)
	{
		keyHeld.D = true;
		m_player.addVelocity(100.f, 0);
	}
}

void PlayGround::keyReleased(const sf::Event& event)
{
	using namespace sf::Keyboard;
	Key code = event.getIf<sf::Event::KeyReleased>()->code;

	if (code == Key::A)
	{
		keyHeld.A = false;
		m_player.addVelocity(100.f, 0);
	}
	if (code == Key::D)
	{
		keyHeld.D = false;
		m_player.addVelocity(-100.f, 0);
	}
}

void PlayGround::mousePressed(const sf::Event& event)
{
}

void PlayGround::mouseReleased(const sf::Event& event)
{
}
