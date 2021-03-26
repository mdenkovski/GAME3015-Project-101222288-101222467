#include "GameState.hpp"
#include "Game.hpp"

GameState::GameState(StateStack& stack, Context context, Game* game)
: State(stack, context, game)
, mWorld(&(mGame->mWorld))
, mPlayer(*context.player)
, isPaused(false)
{
	BuildScene();
}

void GameState::draw()
{
	mWorld->draw();
}

bool GameState::update(const GameTimer& gt)
{
	if (isPaused) return false;

	ProcessInput();
	mWorld->update(gt);


	return true;
}

bool GameState::handleEvent()
{
	if (isPaused) return false;
	// Escape pressed, trigger the pause screen

#pragma region step 1
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		requestStackPush(States::Pause);
		isPaused = true;
	}
	else
	{
		isPaused = false;
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

void GameState::BuildScene()
{

	mGame->mAllRitems.clear();
	mGame->mOpaqueRitems.clear();
	mGame->mFrameResources.clear();

	mGame->BuildMaterials();


	mWorld->buildScene();

	for (auto& e : mGame->mAllRitems)
		mGame->mOpaqueRitems.push_back(e.get());

	mGame->BuildFrameResources();




}
