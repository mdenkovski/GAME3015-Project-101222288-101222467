#include "GameState.hpp"
#include "Game.hpp"

GameState::GameState(StateStack& stack, Context context, Game* game)
: State(stack, context, game)
, mWorld(&(mGame->mWorld))
, mPlayer(*context.player)
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

bool GameState::handleEvent()
{

	// Escape pressed, trigger the pause screen

#pragma region step 1
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
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

	//mGame->mAllRitems.clear();
	//mGame->mOpaqueRitems.clear();

	// Reset the command list to prep for initialization commands.
	ThrowIfFailed(mGame->GetCommandList()->Reset(mGame->GetCommandAllocator(), nullptr));

	// Get the increment size of a descriptor in this heap type.  This is hardware specific, 
	// so we have to query this information.
	mGame->mCbvSrvDescriptorSize = mGame->GetD3DDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	mGame->LoadTextures();
	mGame->BuildRootSignature();
	mGame->BuildDescriptorHeaps();
	mGame->BuildShadersAndInputLayout();
	mGame->BuildShapeGeometry();
	mGame->BuildMaterials();


	mWorld->buildScene();

	for (auto& e : mGame->mAllRitems)
		mGame->mOpaqueRitems.push_back(e.get());

	//mGame->BuildRenderItems();
	mGame->BuildFrameResources();
	mGame->BuildPSOs();






	// Execute the initialization commands.
	ThrowIfFailed(mGame->GetCommandList()->Close());
	ID3D12CommandList* cmdsLists[] = { mGame->GetCommandList() };
	mGame->GetCommandQueue()->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until initialization is complete.
	mGame->FlushCommandQueueGame();


}
