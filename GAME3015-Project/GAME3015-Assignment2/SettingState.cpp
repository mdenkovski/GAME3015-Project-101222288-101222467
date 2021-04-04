#include "SettingState.h"
#include "Game.hpp"

SettingState::SettingState(StateStack* stack, Context* context)
	: State(stack, context)
	, mOptions()
	, mOptionIndex(0)
	, mBackground(nullptr)
	, mSettingWASD(nullptr)
	, mSettingARROW(nullptr)
	, mMenuQuit(nullptr)
	, mMenuSelector(nullptr)
{
	BuildScene();
}

void SettingState::draw()
{

	mSceneGraph->draw();

	
}

bool SettingState::update(const GameTimer& gt)
{
	mSceneGraph->update(gt);

	float x = mOptions[mOptionIndex]->getWorldPosition().x - 1.6;
	float y = mOptions[mOptionIndex]->getWorldPosition().y;
	float z = mOptions[mOptionIndex]->getWorldPosition().z;

	mMenuSelector->setPosition(x, y, z);

	
	return true;
}

bool SettingState::handleEvent(WPARAM btnState)
{

	if (btnState == VK_RETURN )
	{
		if (mOptionIndex == WASD)
		{ // Set controls to this
			getContext()->player->assignKey(Player::Action::MoveUp, 'W');
			getContext()->player->assignKey(Player::Action::MoveDown, 'S');
			getContext()->player->assignKey(Player::Action::MoveLeft, 'A');
			getContext()->player->assignKey(Player::Action::MoveRight, 'D');
			getContext()->player->resetKeyFlags();

			requestStackPop();
			requestStackPush(States::Menu);
		}
		else if (mOptionIndex == ARROWKEYS)
		{ // Set controls to this
			getContext()->player->assignKey(Player::Action::MoveUp, VK_UP);
			getContext()->player->assignKey(Player::Action::MoveDown, VK_DOWN);
			getContext()->player->assignKey(Player::Action::MoveLeft, VK_LEFT);
			getContext()->player->assignKey(Player::Action::MoveRight, VK_RIGHT);
			getContext()->player->resetKeyFlags();

			requestStackPop();
			requestStackPush(States::Menu);
		}
		else if (mOptionIndex == Return) 
		{
			requestStackPop();
			requestStackPush(States::Menu);
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

void SettingState::updateOptionText()
{
	if (mOptions.empty())
		return;

	
}

void SettingState::BuildScene()
{

	/*getContext()->game->mAllRitems.clear();
	getContext()->game->mOpaqueRitems.clear();*/
	


	getContext()->game->BuildMaterials();

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(this));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(0, 0, 0.0);
	mBackground->setScale(12.0, 1.0, 8.5);
	mBackground->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<SpriteNode> mSettingWASDSprite(new SpriteNode(this, "SettingWASD"));
	mSettingWASD = mSettingWASDSprite.get();
	mSettingWASD->setPosition(0, 0.1, 1.0);
	mSettingWASD->setScale(3.0, 1.0, 2.0);
	mSettingWASD->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(mSettingWASDSprite));
	mOptions.push_back(mSettingWASD);

	std::unique_ptr<SpriteNode> mSettingARROWSprite(new SpriteNode(this, "SettingArrow"));
	mSettingARROW = mSettingARROWSprite.get();
	mSettingARROW->setPosition(0, 0.1, 0.0);
	mSettingARROW->setScale(3.0, 1.0, 2.0);
	mSettingARROW->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(mSettingARROWSprite));
	mOptions.push_back(mSettingARROW);

	std::unique_ptr<SpriteNode> menuQuitSprite(new SpriteNode(this, "SettingReturn"));
	mMenuQuit = menuQuitSprite.get();
	mMenuQuit->setPosition(0, 0.1, -1.0);
	mMenuQuit->setScale(3.0, 1.0, 2.0);
	mMenuQuit->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(menuQuitSprite));

	mOptions.push_back(mMenuQuit);

	std::unique_ptr<SpriteNode> menuArrowSprite(new SpriteNode(this, "MenuArrow"));
	mMenuSelector = menuArrowSprite.get();
	mMenuSelector->setPosition(-0.5, 0.1, 0.0);
	mMenuSelector->setScale(0.5f, 1.0f, 0.5f);
	mMenuSelector->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(menuArrowSprite));

	mSceneGraph->build();


	/*for (auto& e : getContext()->game->mAllRitems)
		getContext()->game->mOpaqueRitems.push_back(e.get());*/

	getContext()->game->ClearFrameResources();
	getContext()->game->BuildFrameResources(mAllRitems.size());

}
