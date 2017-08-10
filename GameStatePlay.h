#pragma once
#include <SFML\Window\Event.hpp>
#include "GameState.h"
#include "Dialog.h"
#include "Logic.h"
#include "Snake.h"
#include "Diamond.h"
#include "TextButton.h"

class GameStatePlay : public GameState
{
public:
	GameStatePlay(Game * game);

	void draw() override;
	void update() override;
	void handleInput() override;

private:	
	Logic logic;
	Dialog * dialog;
	Snake * snake;
	Diamond * diamond;
	sf::RectangleShape board;
	TextButton buttons[2];
	sf::Text points;

	void createBoard();
	void createButtons();
	void createPoints();
};