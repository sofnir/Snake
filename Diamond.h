#pragma once
#include "SFML\Graphics\Sprite.hpp"
#include "Data.h"

class Diamond : public sf::Sprite
{
public:
	Diamond();

	void setRandomPosition();	
};
