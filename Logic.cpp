#include "Logic.h"

Logic::Logic()
{
	;
}

void Logic::reset()
{
	state = State::Playing;
	points = 0;
}
