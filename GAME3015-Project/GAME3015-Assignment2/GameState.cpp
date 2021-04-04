#include "GameState.hpp"
#include "Game.hpp"

GameState::GameState(StateStack* stack, Context* context)
: State(stack, context)
, mWorld(this)
, mPauseBackground(nullptr)
, mPausedText(nullptr)
, mPauseInstructionText(nullptr)
, mPauseSceneGraph(new SceneNode(this))
{
	BuildScene();
}

void GameState::draw()
{
	mWorld.draw();
	
}

bool GameState::update(const GameTimer& gt)
{
	ProcessInput();
	mWorld.update(gt);

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
	CommandQueue& commands = mWorld.getCommandQueue();
	getContext()->player->handleEvent(commands);
	getContext()->player->handleRealtimeInput(commands);
}

void GameState::BuildScene()
{

	getContext()->game->mAllRitems.clear();
	getContext()->game->mOpaqueRitems.clear();
	getContext()->game->mFrameResources.clear();

	getContext()->game->BuildMaterials();


	mWorld.buildScene();

	//pause stuff
	
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(this, "PauseDisplay"));
	mPauseBackground = backgroundSprite.get();
	mPauseBackground->setPosition(0, 0.15, 0);
	mPauseBackground->setScale(6, 1.0, 6);
	mPauseBackground->setVelocity(0, 0, 0);
	mPauseSceneGraph->attachChild(std::move(backgroundSprite));

	mPauseSceneGraph->build();
	//pause stuff end
	for (auto& e : getContext()->game->mAllRitems)
		getContext()->game->mOpaqueRitems.push_back(e.get());

	getContext()->game->BuildFrameResources();




}
