#include "SettingState.h"

#include "Game.hpp"
//#include "Utility.hpp"
//#include "ResourceHolder.hpp"

//#include <SFML/Graphics/RenderWindow.hpp>
//#include <SFML/Graphics/View.hpp>


SettingState::SettingState(StateStack& stack, Context context, Game* game)
	: State(stack, context, game)
	, mOptions()
	, mOptionIndex(0)
	, mSceneGraph(new SceneNode(game))
	, mBackground(nullptr)
	, mSettingWASD(nullptr)
	, mSettingARROW(nullptr)
	, mMenuQuit(nullptr)
	, mMenuSelector(nullptr)
{
	BuildScene();

	/*mOptions.push_back(new SpriteNode(mGame));
	mOptions.push_back(new SpriteNode(mGame));*/

	//sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	//sf::Font& font = context.fonts->get(Fonts::Main);

	//mBackgroundSprite.setTexture(texture);
	//
	//// A simple menu demonstration
	//sf::Text playOption;
	//playOption.setFont(font);
	//playOption.setString("Play");
	//centerOrigin(playOption);
	//playOption.setPosition(context.window->getView().getSize() / 2.f);
	//mOptions.push_back(playOption);

	//sf::Text exitOption;
	//exitOption.setFont(font);
	//exitOption.setString("Exit");
	//centerOrigin(exitOption);
	//exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
	//mOptions.push_back(exitOption);

	//updateOptionText();
}

void SettingState::draw()
{

	mSceneGraph->draw();

	/*sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	for(const sf::Text& text: mOptions)
		window.draw(text);*/
}

bool SettingState::update(const GameTimer& gt)
{
	mSceneGraph->update(gt);

	float x = mOptions[mOptionIndex]->getWorldPosition().x;
	float y = mOptions[mOptionIndex]->getWorldPosition().y - 0.6;
	float z = mOptions[mOptionIndex]->getWorldPosition().z;

	mMenuSelector->setPosition(x, y, z);

	/*if (mOptionIndex == 0)
	{
		mMenuSelector->setPosition(-0.5f, 0.1f, 0.0f);
	}
	else
	{
		mMenuSelector->setPosition(-0.5f, 0.1f, -1.0f);
	}*/
	return true;
}

bool SettingState::handleEvent(WPARAM btnState)
{
	

	if (btnState == VK_RETURN )
	{
		if (mOptionIndex == WASD)
		{ // Set controls to this
			mGame->mPlayer.assignKey(Player::Action::MoveUp, 'W');
			mGame->mPlayer.assignKey(Player::Action::MoveDown, 'S');
			mGame->mPlayer.assignKey(Player::Action::MoveLeft, 'A');
			mGame->mPlayer.assignKey(Player::Action::MoveRight, 'D');
			mGame->mPlayer.resetKeyFlags();
		}
		else if (mOptionIndex == ARROWKEYS)
		{ // Set controls to this
			mGame->mPlayer.assignKey(Player::Action::MoveUp, VK_UP);
			mGame->mPlayer.assignKey(Player::Action::MoveDown, VK_DOWN);
			mGame->mPlayer.assignKey(Player::Action::MoveLeft, VK_LEFT);
			mGame->mPlayer.assignKey(Player::Action::MoveRight, VK_RIGHT);
			mGame->mPlayer.resetKeyFlags();
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

	//// White all texts
	//for(sf::Text& text : mOptions)
	//	text.setFillColor(sf::Color::White);

	//// Red the selected text
	//mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}

void SettingState::BuildScene()
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

	std::unique_ptr<SpriteNode> mSettingWASDSprite(new SpriteNode(mGame, "SettingWASD"));
	mSettingWASD = mSettingWASDSprite.get();
	mSettingWASD->setPosition(0, 0.1, 1.0);
	mSettingWASD->setScale(3.0, 1.0, 2.0);
	mSettingWASD->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(mSettingWASDSprite));
	mOptions.push_back(mSettingWASD);

	std::unique_ptr<SpriteNode> mSettingARROWSprite(new SpriteNode(mGame, "SettingARROW"));
	mSettingARROW = mSettingARROWSprite.get();
	mSettingARROW->setPosition(0, 0.1, 0.0);
	mSettingARROW->setScale(3.0, 1.0, 2.0);
	mSettingARROW->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(mSettingARROWSprite));
	mOptions.push_back(mSettingARROW);

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

	//mGame->BuildRenderItems();
	mGame->BuildFrameResources();

}
