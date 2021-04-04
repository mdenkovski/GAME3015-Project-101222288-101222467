#include "SpriteNode.h"
#include "Game.hpp"

SpriteNode::SpriteNode(State* state, std::string spriteImage) : Entity(state)
, mSprite(spriteImage)
{
}

void SpriteNode::drawCurrent() const
{
	//renderer->World = getTransform();
	//renderer->NumFramesDirty++;

	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	auto objectCB = state->getContext()->game->GetCurrFrameResource()->ObjectCB->Resource();
	auto matCB = state->getContext()->game->GetCurrFrameResource()->MaterialCB->Resource();

	if (mSpriteNodeRitem != nullptr)
	{
		state->getContext()->game->getCmdList()->IASetVertexBuffers(0, 1, &mSpriteNodeRitem->Geo->VertexBufferView());
		state->getContext()->game->getCmdList()->IASetIndexBuffer(&mSpriteNodeRitem->Geo->IndexBufferView());
		state->getContext()->game->getCmdList()->IASetPrimitiveTopology(mSpriteNodeRitem->PrimitiveType);

		CD3DX12_GPU_DESCRIPTOR_HANDLE tex(state->getContext()->game->GetSrvSrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart());
		tex.Offset(mSpriteNodeRitem->Mat->DiffuseSrvHeapIndex, state->getContext()->game->GetCbvSrvDescriptorSize());

		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + mSpriteNodeRitem->ObjCBIndex * objCBByteSize;
		D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + mSpriteNodeRitem->Mat->MatCBIndex * matCBByteSize;

		state->getContext()->game->getCmdList()->SetGraphicsRootDescriptorTable(0, tex);
		state->getContext()->game->getCmdList()->SetGraphicsRootConstantBufferView(1, objCBAddress);
		state->getContext()->game->getCmdList()->SetGraphicsRootConstantBufferView(3, matCBAddress);

		state->getContext()->game->getCmdList()->DrawIndexedInstanced(mSpriteNodeRitem->IndexCount, 1, mSpriteNodeRitem->StartIndexLocation, mSpriteNodeRitem->BaseVertexLocation, 0);
	}

}

void SpriteNode::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(1.0f, 1.0f, 1.0f));
	renderer->ObjCBIndex = (UINT)state->mAllRitems.size();
	renderer->Mat = state->getContext()->game->getMaterials()[mSprite].get();
	renderer->Geo = state->getContext()->game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;
	mSpriteNodeRitem = render.get();
	state->mAllRitems.push_back(std::move(render));

}
