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
	virtual bool			handleEvent();

	void					updateOptionText();


private:
	enum OptionNames
	{
		MoveUP,
		MoveDown,
		MoveLeft,
		MoveRight,
		Return
	};


private:

	SceneNode* mSceneGraph;
	SpriteNode* mBackground;
	SpriteNode* mMenuPlay;
	SpriteNode* mMenuQuit;
	SpriteNode* mMenuSelector;

	int		mOptions;
	int mTotalNumOptions;
	std::size_t				mOptionIndex;

	// Inherited via State
	virtual void BuildScene() override;
};
