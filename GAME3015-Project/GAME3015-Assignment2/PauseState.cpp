#pragma region step 3
#include "PauseState.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "State.hpp"

PauseState::PauseState(StateStack& stack, Context context, Game* game)
: State(stack, context, game)

{
	BuildScene();
}

PauseState::~PauseState()
{
}

void PauseState::draw()
{
	((GameState*)((*mStack->GetStateStack())[0].get()))->mPauseSceneGraph->draw();
	
}

bool PauseState::update(const GameTimer& gt)
{
	((GameState*)((*mStack->GetStateStack())[0].get()))->mPauseSceneGraph->update(gt);
	
	return false;
}

bool PauseState::handleEvent(WPARAM btnState)
{
	
	if (btnState == 'O' )
	{
		// O pressed, remove itself to return to the game
		requestStackPop();
	}
	else if (btnState == VK_BACK)
	{
		// Escape pressed, remove itself to return to the game
		requestStateClear();
		requestStackPush(States::Menu);
	}


	return true;
}


void PauseState::BuildScene()
{
	
}

#pragma endregion