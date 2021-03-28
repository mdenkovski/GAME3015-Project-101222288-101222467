#include "TitleState.hpp"
#include "World.hpp"
#include "Game.hpp"


TitleState::TitleState(StateStack& stack, Context context, Game* game)
: State(stack, context, game)
, mBackground(nullptr)
, mSceneGraph(new SceneNode(game))
{
	BuildScene();
}

void TitleState::draw()
{
	mSceneGraph->draw();
}

bool TitleState::update(const GameTimer& gt)
{
	mSceneGraph->update(gt);
	return true;
}

bool TitleState::handleEvent(WPARAM btnState)
{
	//key pressed
	requestStackPop();
	requestStackPush(States::Menu);

	return true;
}



void TitleState::BuildScene()
{
	mGame->mAllRitems.clear();
	mGame->mOpaqueRitems.clear();
	mGame->mFrameResources.clear();
	mGame->BuildMaterials();


	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame, "TitleScreen"));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(0, 0, 0);
	mBackground->setScale(12.0, 1.0, 8.5);
	mBackground->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<SpriteNode> TitlePrompt(new SpriteNode(mGame, "TitleScreenPrompt"));
	mPrompt = TitlePrompt.get();
	mPrompt->setPosition(0, 0.1, 0);
	mPrompt->setScale(6, 1.0, 5);
	mPrompt->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(TitlePrompt));


	mSceneGraph->build();


	for (auto& e : mGame->mAllRitems)
		mGame->mOpaqueRitems.push_back(e.get());

	mGame->BuildFrameResources();
	
}
