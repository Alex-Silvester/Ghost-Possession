
#include "PObject.h"

void PObject::keyPressed(const sf::Event& event)
{
	sf::Keyboard::Key code = event.getIf<sf::Event::KeyPressed>()->code;
	using namespace sf::Keyboard;
	
	if (code == Key::D && !keyHeld.D)
	{
		keyHeld.D = true;
		m_velocity += {100.f, 0};
	}
	if (code == Key::A && !keyHeld.A)
	{
		keyHeld.A = true;
		m_velocity += {-100.f, 0};
	}
	if (code == Key::W && !keyHeld.W)
	{
		keyHeld.W = true;
		m_velocity += {0,-100.f};
	}
	if (code == Key::S && !keyHeld.S)
	{
		keyHeld.S = true;
		m_velocity += {0,100.f};
	}
}

void PObject::keyReleased(const sf::Event& event)
{
	sf::Keyboard::Key code = event.getIf<sf::Event::KeyReleased>()->code;
	using namespace sf::Keyboard;

	if (code == Key::D && keyHeld.D)
	{
		keyHeld.D = false;
		m_velocity += {-100.f, 0};
	}
	if (code == Key::A && keyHeld.A)
	{
		keyHeld.A = false;
		m_velocity += {100.f, 0};
	}
	if (code == Key::W && keyHeld.W)
	{
		keyHeld.W = false;
		m_velocity += {0, 100.f};
	}
	if (code == Key::S && keyHeld.S)
	{
		keyHeld.S = false;
		m_velocity += {0, -100.f};
	}
}

sf::Vector2f PObject::updateMovement(float dt)
{
	flash(sf::Color(102,214,255,255));
	move(m_velocity * dt);

	//vertex array centre doesnt account for the object position
	return m_vertex_array->getBounds().getCenter() + m_position;
}

void PObject::unpossess()
{
	IPossessable::unpossess();

	resetFlash();
	m_velocity = { 0,0 };
}

void PObject::flash(sf::Color col_1, sf::Color col_2, float rate)
{
	rate *= m_flash_speed;

	auto lerp = [](std::uint8_t a, std::uint8_t b, float t)->std::uint8_t {return static_cast<std::uint8_t>(a + (b - a) * t); };

	setColour(sf::Color(
		lerp(col_1.r, col_2.r, fabsf(std::cosf(m_flash_amount))),
		lerp(col_1.g, col_2.g, fabsf(std::cosf(m_flash_amount))),
		lerp(col_1.b, col_2.b, fabsf(std::cosf(m_flash_amount))),
		255));

	m_flash_amount = m_flash_amount >= 2 * PI ? m_flash_amount - 2 * PI : m_flash_amount + rate;
}

void PObject::flash(sf::Color col_1, float rate)
{
	flash(col_1, sf::Color::White, rate);
}
