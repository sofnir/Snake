#pragma once

class Logic
{
public:	

	Logic();
	const enum class State { Waiting, Playing };
	void setState(const State & newState) { state = newState; }	
	const State & getState() const { return state; }
	int getPoints() { return points; }
	void increasePoints() { points++; }
	void reset();

private:
	State state = State::Waiting;
	int points = 0;
};