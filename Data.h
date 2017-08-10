#pragma once
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Sprite.hpp>

class Data
{
public:
	Data();

	static sf::Font font;
	static sf::Texture snakeTexture;
};

namespace Color
{	
	const sf::Color Blue(69, 159, 212);
	const sf::Color Green(44, 191, 164);
	const sf::Color Grey(22, 27, 32);
	const sf::Color Silver(139, 145, 152);
	const sf::Color Red(255, 65, 54);
	const sf::Color White(210, 211, 214);
	const sf::Color Yellow(220, 186, 69);
}

namespace Config
{
	const sf::Vector2u windowSize(800, 600);	
}
