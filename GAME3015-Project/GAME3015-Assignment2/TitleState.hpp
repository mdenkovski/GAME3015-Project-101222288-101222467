#ifndef BOOK_TITLESTATE_HPP
#define BOOK_TITLESTATE_HPP

#include "State.hpp"
#include "SpriteNode.h"
#include "../../Common/d3dApp.h"

//#include <SFML/Graphics/Sprite.hpp>
//#include <SFML/Graphics/Text.hpp>


class TitleState : public State
{
	public:
							TitleState(StateStack& stack, Context context, Game* game);

		virtual void		draw();
		virtual bool		update(const GameTimer& gt);
		virtual bool		handleEvent();



	private:

		//sf::Text			mText;

		bool				mShowText;
		float			mTextEffectTime;

		SpriteNode* mBackground;
		SpriteNode* mPrompt;

		Game* mGame;
		SceneNode* mSceneGraph;

		// Inherited via State
		virtual void BuildScene() override;
};

#endif // BOOK_TITLESTATE_HPP
