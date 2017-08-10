#pragma once
#include <SFML\Window\Event.hpp>
#include "GameState.h"
#include "TextButton.h"

class GameStateMenu : public GameState
{

public:
	GameStateMenu(Game* game);

	void draw() override;
	void update() override;
	void handleInput() override;

private:
	sf::Text title;
	TextButton buttons[2];

	void createTitle();
	void createButtons();
	void playGame();
};
