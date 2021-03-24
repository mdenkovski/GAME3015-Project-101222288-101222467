#include "TitleState.hpp"
#include "World.hpp"
#include "Game.hpp"
//#include <Utility.hpp>
//#include <ResourceHolder.hpp>


TitleState::TitleState(StateStack& stack, Context context, Game* game)
: State(stack, context, game)
//, mText()
, mShowText(true)
, mTextEffectTime()
, mBackground(nullptr)
, mGame(game)
, mSceneGraph(new SceneNode(game))

{
	/*mText.setFont(context.fonts->get(Fonts::Main));
	mText.setString("Press any key to start");
	centerOrigin(mText);
	mText.setPosition(context.window->getView().getSize() / 2.f);*/
}

void TitleState::draw()
{
	/*sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	if (mShowText)
		window.draw(mText);*/


	//mSceneGraph->draw();
}

bool TitleState::update(const GameTimer& gt)
{
	mTextEffectTime += gt.DeltaTime();

	if (mTextEffectTime >= 0.5f)
	{
		//mShowText = !mShowText;
		mTextEffectTime = 0;
	}

	return true;
}

bool TitleState::handleEvent()
{
	//check if any key pressed
	for (int i = 0; i < 256; i++) {
		if (GetAsyncKeyState(i) & 0x8000)
		{
			////key pressed
			requestStackPop();
			requestStackPush(States::Game);
			break;
		}
	}

	

	//// If any key is pressed, trigger the next screen
	//if (event.type == sf::Event::KeyPressed)
	//{
	//	requestStackPop();
	//	requestStackPush(States::Menu);
	//}

	return true;
}

void TitleState::buildScene()
{
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame, "TitleScreen"));
	mBackground = backgroundSprite.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 0.0);
	mBackground->setScale(200.0, 1.0, 200.0);
	mBackground->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	mSceneGraph->build();
}
