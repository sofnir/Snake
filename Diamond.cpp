#include "Diamond.h"

Diamond::Diamond() : sf::Sprite(Data::snakeTexture, sf::IntRect(32 * 3, 0, 32, 32))
{
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
	setRandomPosition();
}

void Diamond::setRandomPosition()
{
	int x = rand() % 24;
	int y = rand() % 14;

	setPosition(sf::Vector2f(32 + x * 32, 92 + y * 32));
}