#include "GameState.hpp"


GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window)
, mPlayer(*context.player)
{
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(const GameTimer& gt)
{
	mWorld.update(gt);

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);

	return true;
}

bool GameState::handleEvent()
{
	// Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(commands);

	// Escape pressed, trigger the pause screen

#pragma region step 1
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		requestStackPush(States::Pause);
	}
#pragma endregion
	return true;
}