#include "simManager.h"

Vector2 SimManager::mouseTileCollision()
{
	for (int i = 0; i < level.gridSide; i++)
	{
		for (int j = 0; j < level.gridSide; j++)
		{
			//if(GetMousePosition().x )
		}
	}
}

void SimManager::update()
{
	if (currentState == SimState::EDIT)
	{
		// check for click on specific tile
		if(IsMouseButtonPressed)

		switch (editState) //change position or tile property based on editing state
		{
		case EditState::BLOCK:
			break;
		case EditState::STARCHASER:
			break;
		case EditState::STAR:
			break;
		case EditState::SHIP:
			break;
		case EditState::TRADING:
			break;
		}
	}
}

void SimManager::render()
{
	level.render();

	//show graphically which states that are toggled
}