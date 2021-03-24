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
							TitleState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(const GameTimer& gt);
		virtual bool		handleEvent();


	private:

		SpriteNode* mBackground;
		//sf::Text			mText;

		bool				mShowText;
		float			mTextEffectTime;


		Game* mGame;
		SceneNode* mSceneGraph;
		std::vector<std::unique_ptr<RenderItem>>* mAllRitems;
};

#endif // BOOK_TITLESTATE_HPP
