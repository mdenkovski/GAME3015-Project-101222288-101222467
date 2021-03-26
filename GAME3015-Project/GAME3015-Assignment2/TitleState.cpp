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
, mSceneGraph(new SceneNode(game))

{

	BuildScene();
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


	mSceneGraph->draw();
}

bool TitleState::update(const GameTimer& gt)
{
	mTextEffectTime += gt.DeltaTime();

	if (mTextEffectTime >= 0.5f)
	{
		//mShowText = !mShowText;
		mTextEffectTime = 0;
	}
	mSceneGraph->update(gt);

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
			requestStackPush(States::Menu);
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



void TitleState::BuildScene()
{
	mGame->mAllRitems.clear();
	mGame->mOpaqueRitems.clear();
	mGame->mFrameResources.clear();

	//// Reset the command list to prep for initialization commands.
	//ThrowIfFailed(mGame->GetCommandList()->Reset(mGame->GetCommandAllocator(), nullptr));

	// Get the increment size of a descriptor in this heap type.  This is hardware specific, 
	// so we have to query this information.
	//mGame->mCbvSrvDescriptorSize = mGame->GetD3DDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//mGame->LoadTextures();
	//mGame->BuildRootSignature();
	//mGame->BuildDescriptorHeaps();
	//mGame->BuildShadersAndInputLayout();
	//mGame->BuildShapeGeometry();
	mGame->BuildMaterials();

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame, "TitleScreen"));
	mBackground = backgroundSprite.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 0);
	mBackground->setScale(12.0, 1.0, 8.0);
	mBackground->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<SpriteNode> TitlePrompt(new SpriteNode(mGame, "TitleScreenPrompt"));
	mPrompt = TitlePrompt.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mPrompt->setPosition(0, 0.1, 0);
	mPrompt->setScale(6, 1.0, 5);
	mPrompt->setVelocity(0, 0, 0);
	mSceneGraph->attachChild(std::move(TitlePrompt));


	mSceneGraph->build();


	for (auto& e : mGame->mAllRitems)
		mGame->mOpaqueRitems.push_back(e.get());

	//mGame->BuildRenderItems();
	mGame->BuildFrameResources();
	//mGame->BuildPSOs();
	





	////// Execute the initialization commands.
	//ThrowIfFailed(mGame->GetCommandList()->Close());
	//ID3D12CommandList* cmdsLists[] = { mGame->GetCommandList() };
	//mGame->GetCommandQueue()->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	//// Wait until initialization is complete.
	//mGame->FlushCommandQueueGame();



	
}
