
#include "PossessableBox.h"

void PossessableBox::keyPressed(const sf::Event& event)
{
	sf::Keyboard::Key code = event.getIf<sf::Event::KeyPressed>()->code;
	using namespace sf::Keyboard;
	
	if (code == Key::D && !keyHeld.D)
	{
		keyHeld.D = true;
		m_velocity += {100.f, 0};
	}
}

void PossessableBox::keyReleased(const sf::Event& event)
{
	sf::Keyboard::Key code = event.getIf<sf::Event::KeyReleased>()->code;
	using namespace sf::Keyboard;

	if (code == Key::D && keyHeld.D)
	{
		keyHeld.D = false;
		m_velocity += {-100.f, 0};
	}
}

sf::Vector2f PossessableBox::updateMovement(float dt)
{
	auto lerp = [](float a, float b, float t)->float {return a + (b - a) * t; };

	m_sprite->setColor(sf::Color(
		lerp(102.f, 255.f, fabsf(std::cosf(m_flash_amount))), 
		lerp(214.f, 255.f, fabsf(std::cosf(m_flash_amount))), 
		255, 
		255));

	m_flash_amount = m_flash_amount >= 2 * PI ? m_flash_amount - 2 * PI : m_flash_amount + m_flash_speed;

	m_sprite->move(m_velocity * dt);

	return m_sprite->getPosition();
}
