#ifndef BOOK_GAMESTATE_HPP
#define BOOK_GAMESTATE_HPP


#include "Player.hpp"
#include "State.hpp"
#include "World.hpp"
#include "SpriteNode.h"

class GameState : public State
{
	public:
							GameState(StateStack* stack, Context* context);

		virtual void		draw();
		virtual bool		update(const GameTimer& gt);
		virtual bool		handleEvent(WPARAM btnState);


		void ProcessInput();


	private:
		World				mWorld;
	public:
		SceneNode* mPauseSceneGraph;
		/*
		SpriteNode* mPauseBackground;
		SpriteNode* mPausedText;
		SpriteNode* mPauseInstructionText;*/
private:
		// Inherited via State
		virtual void BuildScene() override;
};

#endif // BOOK_GAMESTATE_HPP