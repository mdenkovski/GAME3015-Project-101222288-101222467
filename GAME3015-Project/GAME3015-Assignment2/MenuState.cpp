#include "MenuState.hpp"
#include "Game.hpp"


MenuState::MenuState(StateStack& stack, Context context, Game* game)
: State(stack, context, game)
, mOptionIndex(0)
, mSceneGraph(new SceneNode(game))
, mBackground(nullptr)
, mMenuPlay(nullptr)
, mMenuSetting(nullptr)
, mMenuQuit(nullptr)
, mMenuSelector (nullptr)
{
	BuildScene();

}

void MenuState::draw()
{
	mSceneGraph->draw();
}

bool MenuState::update(const GameTimer& gt)
{
	mSceneGraph->update(gt);

	float x = mOptions[mOptionIndex]->getWorldPosition().x - 0.9;
	float y = mOptions[mOptionIndex]->getWorldPosition().y;
	float z = mOptions[mOptionIndex]->getWorldPosition().z;

	mMenuSelector->setPosition(x, y, z);
	return true;
}

bool MenuState::handleEvent(WPARAM btnState)
{
	if (btnState == VK_RETURN)
	{
		if (mOptionIndex == Play)
		{
			requestStackPop();
			requestStackPush(States::Game);
		}
		else if (mOptionIndex == Setting)
		{
			requestStackPop();
			requestStackPush(States::Setting);
		}
		else if (mOptionIndex == Exit)
		{
			// The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to close.
			requestStackPop();
		}
	}
	else if (btnState == VK_UP)
	{
		// Decrement and wrap-around
		if (mOptionIndex > 0)
			mOptionIndex--;
		else
			mOptionIndex = mOptions.size() - 1;

		updateOptionText();
	}
	else if (btnState == VK_DOWN)
	{
		// Increment and wrap-around
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;

		updateOptionText();
	}
	else
	{
		return false;
	}

	return true;
}

void MenuState::updateOptionText()
{
	if (mOptions.empty())
		return;
}

void MenuState::BuildScene()
{

	mGame->mAllRitems.clear();
	mGame->mOpaqueRitems.clear();
	mGame->mFrameResources.clear();


	mGame->BuildMaterials();

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(0, 0, 0.0);
	mBackground->setScale(12.0, 1.0, 8.5);
	mBackground->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<SpriteNode> menuPlaySprite(new SpriteNode(mGame, "MenuPlay"));
	mMenuPlay = menuPlaySprite.get();
	mMenuPlay->setPosition(0, 0.1, 1.0);
	mMenuPlay->setScale(3.0, 1.0, 2.0);
	mMenuPlay->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(menuPlaySprite));
	mOptions.push_back(mMenuPlay);

	std::unique_ptr<SpriteNode> menuSettingSprite(new SpriteNode(mGame, "MenuSettingTex"));
	mMenuSetting = menuSettingSprite.get();
	mMenuSetting->setPosition(0, 0.1, 0.0);
	mMenuSetting->setScale(3.0, 1.0, 2.0);
	mMenuSetting->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(menuSettingSprite));
	mOptions.push_back(mMenuSetting);

	std::unique_ptr<SpriteNode> menuQuitSprite(new SpriteNode(mGame, "MenuQuit"));
	mMenuQuit = menuQuitSprite.get();
	mMenuQuit->setPosition(0, 0.1, -1.0);
	mMenuQuit->setScale(3.0, 1.0, 2.0);
	mMenuQuit->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(menuQuitSprite));

	mOptions.push_back(mMenuQuit);

	std::unique_ptr<SpriteNode> menuArrowSprite(new SpriteNode(mGame, "MenuArrow"));
	mMenuSelector = menuArrowSprite.get();
	mMenuSelector->setPosition(-0.5, 0.1, 0.0);
	mMenuSelector->setScale(0.5f, 1.0f, 0.5f);
	mMenuSelector->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(menuArrowSprite));

	mSceneGraph->build();


	for (auto& e : mGame->mAllRitems)
		mGame->mOpaqueRitems.push_back(e.get());

	mGame->BuildFrameResources();

}
