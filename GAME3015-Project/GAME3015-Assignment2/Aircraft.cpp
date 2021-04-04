#include "Aircraft.hpp"
#include "Game.hpp"

Aircraft::Aircraft(Type type, State* state) : Entity(state)
	, mType(type)
{
	switch (type)
	{
	case (Type::Eagle):
		mSprite = "Eagle";
		break;
	case (Type::Raptor):
		mSprite = "Raptor";
		break;
	default:
		mSprite = "Eagle";
		break;
	}
}

unsigned int Aircraft::getCategory() const
{
	switch (mType)
	{
	case Type::Eagle:
		return Category::PlayerAircraft;

	default:
		return Category::EnemyAircraft;
	}
}

void Aircraft::drawCurrent() const
{
	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	auto objectCB = state->getContext()->game->mCurrFrameResource->ObjectCB->Resource();
	auto matCB = state->getContext()->game->mCurrFrameResource->MaterialCB->Resource();

	if (mAircraftRitem != nullptr)
	{
		state->getContext()->game->getCmdList()->IASetVertexBuffers(0, 1, &mAircraftRitem->Geo->VertexBufferView());
		state->getContext()->game->getCmdList()->IASetIndexBuffer(&mAircraftRitem->Geo->IndexBufferView());
		state->getContext()->game->getCmdList()->IASetPrimitiveTopology(mAircraftRitem->PrimitiveType);

		CD3DX12_GPU_DESCRIPTOR_HANDLE tex(state->getContext()->game->mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
		tex.Offset(mAircraftRitem->Mat->DiffuseSrvHeapIndex, state->getContext()->game->mCbvSrvDescriptorSize);

		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress =  objectCB->GetGPUVirtualAddress() + (UINT64)mAircraftRitem->ObjCBIndex * objCBByteSize;
		D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + (UINT64)mAircraftRitem->Mat->MatCBIndex * matCBByteSize;

		state->getContext()->game->getCmdList()->SetGraphicsRootDescriptorTable(0, tex);
		state->getContext()->game->getCmdList()->SetGraphicsRootConstantBufferView(1, objCBAddress);
		state->getContext()->game->getCmdList()->SetGraphicsRootConstantBufferView(3, matCBAddress);

		state->getContext()->game->getCmdList()->DrawIndexedInstanced(mAircraftRitem->IndexCount, 1, mAircraftRitem->StartIndexLocation, mAircraftRitem->BaseVertexLocation, 0);
	}
}

void Aircraft::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	renderer->ObjCBIndex = (UINT)state->getContext()->game->getRenderItems().size();
	renderer->Mat = state->getContext()->game->getMaterials()[mSprite].get();
	renderer->Geo = state->getContext()->game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;
	mAircraftRitem = render.get();
	state->getContext()->game->getRenderItems().push_back(std::move(render));
}
