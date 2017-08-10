#include "Data.h"

sf::Font Data::font;
sf::Texture Data::snakeTexture;

Data::Data()
{
	font.loadFromFile("Data/font.ttf");

	snakeTexture.loadFromFile("Data/snake.png");
	snakeTexture.setSmooth(true);
}
