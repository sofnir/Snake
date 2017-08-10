#pragma once
#include "SFML\Graphics\Drawable.hpp"
#include "SFML\Graphics\RenderTarget.hpp"
#include "SFML\Graphics\Text.hpp"
#include "Data.h"

class Dialog : public sf::Drawable
{
public:
	Dialog();
	
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	sf::Text message;

	void createStartingMessage();
};
