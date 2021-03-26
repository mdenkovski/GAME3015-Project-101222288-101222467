#pragma region step 3
#include "PauseState.hpp"
#include "Game.hpp"
/*
#include "Utility.hpp"
#include "ResourceHolder.hpp"*/

//#include <SFML/Graphics/RectangleShape.hpp>
//#include <SFML/Graphics/RenderWindow.hpp>
//#include <SFML/Graphics/View.hpp>


PauseState::PauseState(StateStack& stack, Context context, Game* game)
: State(stack, context, game)
, mBackground(nullptr)
, mPausedText(nullptr)
, mInstructionText(nullptr)
, mSceneGraph(new SceneNode(game))
, pauseStarted(true)
{
	/*sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f viewSize = context.window->getView().getSize();

	mPausedText.setFont(font);
	mPausedText.setString("Game Paused");	
	mPausedText.setCharacterSize(70);
	centerOrigin(mPausedText);
	mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	mInstructionText.setFont(font);
	mInstructionText.setString("(Press Backspace to return to the main menu)");	
	centerOrigin(mInstructionText);
	mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);*/
	BuildScene();
}

PauseState::~PauseState()
{
	/*mGame->mAllRitems.pop_back();
	mGame->mOpaqueRitems.pop_back();

	mGame->mFrameResources.clear();
	mGame->BuildFrameResources();*/
}

void PauseState::draw()
{
	mSceneGraph->draw();

	/*sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mInstructionText);*/
}

bool PauseState::update(const GameTimer& gt)
{
	
	mSceneGraph->update(gt);
	return true;
}

bool PauseState::handleEvent()
{
	//if (event.type != sf::Event::KeyPressed)
	//	return false;

	//if (event.key.code == sf::Keyboard::Escape)
	//{
	//	// Escape pressed, remove itself to return to the game
	//	requestStackPop();
	//}

	//if (event.key.code == sf::Keyboard::BackSpace)
	//{
	//	// Escape pressed, remove itself to return to the game
	//	requestStateClear();
	//	requestStackPush(States::Menu);
	//}

	//return false;


	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 && !pauseStarted)
	{
		// Escape pressed, remove itself to return to the game
		requestStackPop();
		pauseStarted = true;
	}
	else
	{
		pauseStarted = false;
	}

	if (GetAsyncKeyState(VK_BACK) & 0x8000)
	{
		// Escape pressed, remove itself to return to the game
		requestStateClear();
		requestStackPush(States::Menu);
	}
	else
	{
		return false;
	}


	return true;
}


void PauseState::BuildScene()
{
	//mGame->mAllRitems.clear();
	mGame->mOpaqueRitems.clear();
	mGame->mFrameResources.clear();

	
	//mGame->BuildMaterials();

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame, "TitleScreen"));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(25, 0, 12.5);
	mBackground->setScale(500.0, 1.0, 420.0);
	mBackground->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	mSceneGraph->build();


	for (auto& e : mGame->mAllRitems)
		mGame->mOpaqueRitems.push_back(e.get());

	mGame->BuildFrameResources();
}

#pragma endregion