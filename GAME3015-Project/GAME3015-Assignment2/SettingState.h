#pragma once


#include "State.hpp"
#include "SpriteNode.h"
#include "../../Common/d3dApp.h"

class SettingState : public State
{
public: 
	SettingState(StateStack& stack, Context context, Game* game);
	virtual void			draw();
	virtual bool			update(const GameTimer& gt);
	virtual bool			handleEvent(WPARAM btnState);

	void					updateOptionText();


private:
	enum OptionNames
	{
		WASD,
		ARROWKEYS,
		Return
	};


private:

	SceneNode* mSceneGraph;
	SpriteNode* mBackground;
	SpriteNode* mSettingWASD;
	SpriteNode* mSettingARROW;
	SpriteNode* mMenuQuit;
	SpriteNode* mMenuSelector;
	std::vector<SpriteNode*>	mOptions;
	std::size_t				mOptionIndex;
	int mTotalNumOptions;
	//std::size_t				mOptionIndex;

	// Inherited via State
	virtual void BuildScene() override;
};
