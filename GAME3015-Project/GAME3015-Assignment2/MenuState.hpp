#ifndef BOOK_MENUSTATE_HPP
#define BOOK_MENUSTATE_HPP

#include "State.hpp"
#include "SpriteNode.h"
#include "../../Common/d3dApp.h"

//#include <SFML/Graphics/Sprite.hpp>
//#include <SFML/Graphics/Text.hpp>


class MenuState : public State
{
	public:
								MenuState(StateStack& stack, Context context, Game* game);

		virtual void			draw();
		virtual bool			update(const GameTimer& gt);
		virtual bool			handleEvent();

		void					updateOptionText();


	private:
		enum OptionNames
		{
			Play,
			Exit,
		};


	private:

		SceneNode* mSceneGraph;
		SpriteNode* mBackground;

		std::vector<SpriteNode*>	mOptions;
		std::size_t				mOptionIndex;

		// Inherited via State
		virtual void BuildScene() override;
};

#endif // BOOK_MENUSTATE_HPP
