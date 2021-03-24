#ifndef BOOK_MENUSTATE_HPP
#define BOOK_MENUSTATE_HPP

#include "State.hpp"

//#include <SFML/Graphics/Sprite.hpp>
//#include <SFML/Graphics/Text.hpp>


class MenuState : public State
{
	public:
								MenuState(StateStack& stack, Context context);

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
		sf::Sprite				mBackgroundSprite;

		std::vector<sf::Text>	mOptions;
		std::size_t				mOptionIndex;
};

#endif // BOOK_MENUSTATE_HPP
