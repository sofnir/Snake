#pragma once
#include "Data.h"
#include "SFML\Graphics\Drawable.hpp"
#include "SFML\Graphics\RenderTarget.hpp"
#include "SFML\Graphics\RectangleShape.hpp"
#include <vector>

class Snake : public sf::Drawable
{
public:
	Snake();

	enum class Direction { UP, DOWN, LEFT, RIGHT };

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void move();
	void changeDirection(const Direction & direction);
	bool isSelfBitting();
	bool isWallCollision(const sf::RectangleShape & area);
	bool isEatingDiamond(const sf::Sprite & diamond);
	bool isDiamondOnTheBody(const sf::Sprite & diamond);
	void setAliveState(bool state) { isAlive = state; }
	void reset();
	void addPart();

private:
	std::vector <sf::Sprite> snakeParts;
	sf::Sprite tail;
	Direction currentDirection = Direction::RIGHT;
	Direction prevDirection = Direction::RIGHT;
	Direction globalDirection = Direction::RIGHT;
	const int size = 32; // snake part size
	bool isAlive = true;
	sf::IntRect nextRect = sf::IntRect(size * 2.0f, 0, size, size); // next texture rect for first part of body

	void createHead();
	void createTail();

	void moveHead();
	void moveBody(const sf::Vector2f &prevHeadPos, float prevHeadRotation);
	void moveTail(const sf::Vector2f & prevPos, float currentRotation);
	void changeNextRect(); // set next texture rect for the first part of body when snake changes direction 
};
