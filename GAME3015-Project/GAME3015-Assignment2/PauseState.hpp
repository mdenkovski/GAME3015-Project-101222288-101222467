#pragma region step 2
#pragma once

#include "State.hpp"

#include "SpriteNode.h"
#include "../../Common/d3dApp.h"



class PauseState : public State
{
	public:
							PauseState(StateStack& stack, Context context, Game* game);

		virtual void		draw();
		virtual bool		update(const GameTimer& gt);
		virtual bool		handleEvent();


	private:
		SceneNode* mSceneGraph;
		SpriteNode* mBackground;
		SpriteNode* mPausedText;
		SpriteNode* mInstructionText;

		// Inherited via State
		virtual void BuildScene() override;
};

#pragma endregion