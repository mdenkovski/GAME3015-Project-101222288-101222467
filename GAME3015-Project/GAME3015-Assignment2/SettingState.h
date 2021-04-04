#pragma once


#include "State.hpp"
#include "SpriteNode.h"
#include "../../Common/d3dApp.h"

class SettingState : public State
{
public: 
	SettingState(StateStack* stack, Context* context);
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

	SpriteNode* mBackground;
	SpriteNode* mSettingWASD;
	SpriteNode* mSettingARROW;
	SpriteNode* mMenuQuit;
	SpriteNode* mMenuSelector;
	std::vector<SpriteNode*>	mOptions;
	std::size_t				mOptionIndex;
	int mTotalNumOptions;

	// Inherited via State
	virtual void BuildScene() override;
};
