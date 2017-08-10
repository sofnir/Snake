#include "GameStatePlay.h"
#include "GameState.h"

GameStatePlay::GameStatePlay(Game * game)
{
	this->game = game;	

	createBoard();
	createButtons();
	createPoints();

	dialog = new Dialog();
	snake = nullptr;	
	diamond = nullptr;
}

void GameStatePlay::draw()
{
	game->window.clear(Color::Grey);	
	game->window.draw(points);

	if (snake != nullptr)
	{
		game->window.draw(*snake);
	}

	for (auto & button : buttons)
	{
		game->window.draw(button);
	}			

	if (diamond != nullptr)
	{
		game->window.draw(*diamond);
	}	

	game->window.draw(board);

	if (dialog != nullptr)
	{
		game->window.draw(*dialog);
	}

	game->window.display();
}

void GameStatePlay::update()
{
	for (auto & button : buttons)
	{
		button.update(game->mousePosition);
	}

	points.setString("Current points : " + std::to_string(logic.getPoints()));

	if (game->clock.getElapsedTime().asMilliseconds() > 120 && logic.getState() == Logic::State::Playing)
	{
		snake->move();

		// game over
		if (snake->isSelfBitting() || snake->isWallCollision(board))
		{
			logic.setState(Logic::State::Waiting);
			snake->setAliveState(false);
			board.setFillColor(sf::Color(22, 27, 32, 200));
			dialog = new Dialog();
		}

		// get diamond
		if (snake->isEatingDiamond(*diamond))
		{
			do
			{
				diamond->setRandomPosition();
			} while (snake->isDiamondOnTheBody(*diamond));

			snake->addPart();
			logic.increasePoints();
		}

		game->clock.restart();
	}
}

void GameStatePlay::handleInput()
{
	sf::Event event;

	while (game->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			game->window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				game->popState();
				return;
			}
			// reset game
			else if (event.key.code == sf::Keyboard::Space && logic.getState() == Logic::State::Waiting)
			{				
				logic.reset();
				board.setFillColor(sf::Color::Transparent);				
				dialog = nullptr;
				snake = new Snake();
				diamond = new Diamond();
			}
			else if (event.key.code == sf::Keyboard::Left)
			{
				snake->changeDirection(Snake::Direction::LEFT);
			}
			else if (event.key.code == sf::Keyboard::Right)
			{
				snake->changeDirection(Snake::Direction::RIGHT);
			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				snake->changeDirection(Snake::Direction::UP);
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				snake->changeDirection(Snake::Direction::DOWN);
			}
			break;
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{							
				if (buttons[0].isHover(game->mousePosition))
				{
					game->popState();
					return;
				}
				else if (buttons[1].isHover(game->mousePosition))
				{
					game->window.close();
				}
			}
		}
		default: break;
		}
	}

	return;
}

void GameStatePlay::createBoard()
{
	board.setSize(sf::Vector2f(32 * 24, 32 * 14));
	board.setOrigin(board.getGlobalBounds().width / 2.0f, board.getGlobalBounds().height / 2.0f);
	board.setFillColor(sf::Color::Transparent);
	board.setOutlineThickness(1);
	board.setOutlineColor(Color::Blue);
	board.setPosition(Config::windowSize.x / 2.0f, Config::windowSize.y / 2.0f);
}

void GameStatePlay::createButtons ()
{
	buttons[0] = TextButton("Back", Data::font, 30);
	buttons[1] = TextButton("Exit", Data::font, 30);

	for (int i = 0; i < 2; i++)
	{
		buttons[i].setHoverColor(Color::Green);
		buttons[i].setFillColor(Color::White);
		buttons[i].setOrigin(sf::Vector2f(buttons[i].getGlobalBounds().width / 2.0f,
			buttons[i].getGlobalBounds().height / 2.0f));
		buttons[i].setPosition(sf::Vector2f(Config::windowSize.x / 4.0f + Config::windowSize.x / 2.0f * i,
			Config::windowSize.y - 50.0f));
	}
}

void GameStatePlay::createPoints()
{
	points.setFont(Data::font);
	points.setString("Current points : 0");
	points.setOrigin(sf::Vector2f(points.getGlobalBounds().width / 2.0f, points.getGlobalBounds().height / 2.0f));
	points.setPosition(sf::Vector2f(Config::windowSize.x / 2.0f, 25.0f));
	points.setFillColor(Color::White);
}
