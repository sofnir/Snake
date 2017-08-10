#include "Snake.h"
#include <iostream>

Snake::Snake()
{
	createHead();
	addPart();
	snakeParts[1].setPosition(sf::Vector2f(snakeParts.begin()->getPosition().x - 32.0f,
		snakeParts.begin()->getPosition().y));
	createTail();
}

void Snake::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

	//draw head if snake is alive
	if (isAlive)
	{
		target.draw(snakeParts[0]);
	}

	//draw body parts
	for (int i = 1; i < snakeParts.size(); i++)
	{
		target.draw(snakeParts[i]);
	}

	//draw tail
	target.draw(tail);
}

void Snake::move()
{
	// get head position
	sf::Vector2f headPosition = snakeParts.begin()->getPosition();
	float headRotation = snakeParts.begin()->getRotation();

	changeNextRect();
	moveHead();
	moveBody(headPosition, headRotation);
	globalDirection = currentDirection;
}

void Snake::changeDirection(const Direction & direction)
{
	switch (direction)
	{
	case Direction::UP:
		if (globalDirection != Direction::DOWN)
		{
			currentDirection = Direction::UP;
		}
		break;
	case Direction::DOWN:
		if (globalDirection != Direction::UP)
		{
			currentDirection = Direction::DOWN;
		}
		break;
	case Direction::RIGHT:
		if (globalDirection != Direction::LEFT)
		{
			currentDirection = Direction::RIGHT;
		}
		break;
	case Direction::LEFT:
		if (globalDirection != Direction::RIGHT)
		{
			currentDirection = Direction::LEFT;
		}
		break;
	default:
		break;
	}
}

bool Snake::isSelfBitting()
{
	for (int i = 1; i < snakeParts.size(); i++)
	{
		if (snakeParts[0].getPosition().x > snakeParts[i].getPosition().x - size / 2
			&& snakeParts[0].getPosition().x < snakeParts[i].getPosition().x + size / 2
			&& snakeParts[0].getPosition().y > snakeParts[i].getPosition().y - size / 2
			&& snakeParts[0].getPosition().y < snakeParts[i].getPosition().y + size / 2)
		{
			return true;
		}
	}

	// if bitting tail
	if (snakeParts[0].getGlobalBounds().intersects(tail.getGlobalBounds()))
	{
		return true;
	}

	return false;
}

bool Snake::isWallCollision(const sf::RectangleShape & area)
{
	if (snakeParts.begin()->getPosition().x < area.getGlobalBounds().left ||
		snakeParts.begin()->getPosition().x > area.getGlobalBounds().left + area.getGlobalBounds().width ||
		snakeParts.begin()->getPosition().y < area.getGlobalBounds().top ||
		snakeParts.begin()->getPosition().y > area.getGlobalBounds().top + area.getGlobalBounds().height)
	{
		return true;
	}

	return false;
}

bool Snake::isEatingDiamond(const sf::Sprite & diamond)
{
	if (diamond.getGlobalBounds().intersects(snakeParts.begin()->getGlobalBounds()))
	{
		return true;
	}

	return false;
}

bool Snake::isDiamondOnTheBody(const sf::Sprite & diamond)
{
	// if diamond is on the head or any body part return true
	for (int i = 0; i < snakeParts.size(); i++)
	{
		if (diamond.getGlobalBounds().intersects(snakeParts[i].getGlobalBounds()))
		{
			return true;
		}
	}

	// if diamond is on the tail return true
	if (diamond.getGlobalBounds().intersects(tail.getGlobalBounds()))
	{
		return true;
	}

	return false;
}

void Snake::reset()
{
	snakeParts.clear();
	createHead();
	addPart();
	snakeParts[1].setPosition(sf::Vector2f(snakeParts.begin()->getPosition().x - 32.0f,
		snakeParts.begin()->getPosition().y));
	createTail();
	isAlive = true;
	currentDirection = Direction::RIGHT;
	prevDirection = Direction::RIGHT;
	globalDirection = Direction::RIGHT;
	nextRect = sf::IntRect(size * 2.0f, 0, size, size);
}

void Snake::createHead()
{
	sf::Sprite head(Data::snakeTexture, sf::IntRect(0, size * 2.0f, size, size));
	head.setOrigin(size / 2.0, size / 2.0f);
	head.setPosition(Config::windowSize.x / 2.0f - 16, Config::windowSize.y / 2.0f - 16);
	snakeParts.push_back(head);
}

void Snake::createTail()
{
	tail = sf::Sprite(Data::snakeTexture, sf::IntRect(size * 2, size * 2, size, size));
	tail.setOrigin(tail.getGlobalBounds().width / 2, tail.getGlobalBounds().height / 2);
	tail.setPosition(snakeParts.back().getPosition().x - size, snakeParts.back().getPosition().y);
}

void Snake::addPart()
{
	sf::Sprite body(Data::snakeTexture, sf::IntRect(size * 2.0f, 0, size, size));
	body.setOrigin(size / 2.0f, size / 2.0f);
	body.setPosition(-100.0f, -100.0f);
	snakeParts.push_back(body);
}

void Snake::moveHead()
{
	if (currentDirection == Direction::RIGHT)
	{
		snakeParts.begin()->setRotation(0);
		snakeParts.begin()->move(sf::Vector2f(size, 0));
		prevDirection = Direction::RIGHT;
	}
	else if (currentDirection == Direction::LEFT)
	{
		snakeParts.begin()->setRotation(180);
		snakeParts.begin()->move(sf::Vector2f(-size, 0));
		prevDirection = Direction::LEFT;
	}
	else if (currentDirection == Direction::UP)
	{
		snakeParts.begin()->setRotation(270);
		snakeParts.begin()->move(sf::Vector2f(0, -size));
		prevDirection = Direction::UP;
	}
	else if (currentDirection == Direction::DOWN)
	{
		snakeParts.begin()->setRotation(90);
		snakeParts.begin()->move(sf::Vector2f(0, size));
		prevDirection = Direction::DOWN;
	}
}

void Snake::moveBody(const sf::Vector2f & prevHeadPos, float prevHeadRotation)
{
	//save first part of body parameters before move
	sf::Vector2f pos;
	sf::Vector2f prevPos = snakeParts[1].getPosition();
	float rotation;
	float prevRotation = snakeParts[1].getRotation();
	sf::IntRect rect;
	sf::IntRect prevRect = snakeParts[1].getTextureRect();

	//move first body part
	snakeParts[1].setPosition(prevHeadPos);
	snakeParts[1].setRotation(prevHeadRotation);
	snakeParts[1].setTextureRect(nextRect);
	nextRect = sf::IntRect(size * 2.0f, 0, size, size);

	//move others parts 	
	for (int i = 2; i < snakeParts.size(); i++)
	{
		pos = snakeParts[i].getPosition();
		rotation = snakeParts[i].getRotation();
		rect = snakeParts[i].getTextureRect();

		snakeParts[i].setPosition(prevPos);
		snakeParts[i].setRotation(prevRotation);
		snakeParts[i].setTextureRect(prevRect);

		prevPos = pos;
		prevRotation = rotation;
		prevRect = rect;
	}

	moveTail(prevPos, snakeParts.back().getRotation());
}

void Snake::moveTail(const sf::Vector2f & prevPos, float currentRotation)
{
	// if not waiting for adding any body part (when is adding part this part is on the negative position) 
	if (prevPos.x > 0)
	{
		tail.setPosition(prevPos);
		tail.setRotation(currentRotation);
	}
}

void Snake::changeNextRect() // these values are dependence of the head rotation
{
	// rotation 0
	if (prevDirection == Direction::RIGHT && currentDirection == Direction::UP)
	{
		nextRect = sf::IntRect(size, size, size, size);
	}
	else if (prevDirection == Direction::RIGHT && currentDirection == Direction::DOWN)
	{
		nextRect = sf::IntRect(size, 0, size, size);
	}
	// rotation 180
	else if (prevDirection == Direction::LEFT && currentDirection == Direction::UP)
	{
		nextRect = sf::IntRect(size, 0, size, size);
	}
	else if (prevDirection == Direction::LEFT && currentDirection == Direction::DOWN)
	{
		nextRect = sf::IntRect(size, size, size, size);
	}
	// rotation 270
	else if (prevDirection == Direction::UP && currentDirection == Direction::RIGHT)
	{
		nextRect = sf::IntRect(size, 0, size, size);
	}
	else if (prevDirection == Direction::UP && currentDirection == Direction::LEFT)
	{
		nextRect = sf::IntRect(size, size, size, size);
	}
	// rotation 90
	else if (prevDirection == Direction::DOWN && currentDirection == Direction::RIGHT)
	{
		nextRect = sf::IntRect(size, size, size, size);
	}
	else if (prevDirection == Direction::DOWN && currentDirection == Direction::LEFT)
	{
		nextRect = sf::IntRect(size, 0, size, size);
	}
}