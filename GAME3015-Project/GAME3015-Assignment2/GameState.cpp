#include "GameState.hpp"
#include "Game.hpp"

GameState::GameState(StateStack& stack, Context context, Game* game)
: State(stack, context, game)
, mWorld(&(mGame->mWorld))
, mPlayer(*context.player)
{
}

void GameState::draw()
{
	mWorld->draw();
}

bool GameState::update(const GameTimer& gt)
{
	ProcessInput();
	mWorld->update(gt);


	return true;
}

bool GameState::handleEvent()
{

	// Escape pressed, trigger the pause screen

#pragma region step 1
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		requestStackPush(States::Pause);
	}
#pragma endregion
	return true;
}

void GameState::ProcessInput()
{
	CommandQueue& commands = mWorld->getCommandQueue();
	mPlayer.handleEvent(commands);
	mPlayer.handleRealtimeInput(commands);
}
