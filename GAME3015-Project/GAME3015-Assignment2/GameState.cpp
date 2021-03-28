#include "GameState.hpp"
#include "Game.hpp"

GameState::GameState(StateStack& stack, Context context, Game* game)
: State(stack, context, game)
, mWorld(&(mGame->mWorld))
, mPlayer(*context.player)
, mPauseBackground(nullptr)
, mPausedText(nullptr)
, mPauseInstructionText(nullptr)
, mPauseSceneGraph(new SceneNode(game))
{
	BuildScene();
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

bool GameState::handleEvent(WPARAM btnState)
{
#pragma region step 1
	if (btnState == 'P')
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

void GameState::BuildScene()
{

	mGame->mAllRitems.clear();
	mGame->mOpaqueRitems.clear();
	mGame->mFrameResources.clear();

	mGame->BuildMaterials();


	mWorld->buildScene();

	//pause stuff
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame, "PauseDisplay"));
	mPauseBackground = backgroundSprite.get();
	mPauseBackground->setPosition(25, 0.15, 12.5);
	mPauseBackground->setScale(500.0, 1.0, 420.0);
	mPauseBackground->setVelocity(0, 0, 0);
	mPauseSceneGraph->attachChild(std::move(backgroundSprite));

	mPauseSceneGraph->build();
	//pause stuff end
	for (auto& e : mGame->mAllRitems)
		mGame->mOpaqueRitems.push_back(e.get());

	mGame->BuildFrameResources();




}
