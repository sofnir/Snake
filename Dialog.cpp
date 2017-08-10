#include "Dialog.h"

Dialog::Dialog()
{
	createStartingMessage();
}

void Dialog::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(message);
}

void Dialog::createStartingMessage()
{
	message.setFont(Data::font);
	message.setString("Press spacebar to start");
	message.setCharacterSize(40);
	message.setOrigin(message.getGlobalBounds().width / 2, message.getGlobalBounds().height / 2);
	message.setPosition(sf::Vector2f(Config::windowSize.x / 2, Config::windowSize.y / 2));
	message.setFillColor(Color::Blue);
}