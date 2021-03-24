#ifndef BOOK_GAMESTATE_HPP
#define BOOK_GAMESTATE_HPP


#include "Player.hpp"
#include "State.hpp"
#include "World.hpp"
//#include "../../Common/d3dApp.h"

//#include <SFML/Graphics/Sprite.hpp>
//#include <SFML/Graphics/Text.hpp>


class GameState : public State
{
	public:
							GameState(StateStack& stack, Context context, Game* game);

		virtual void		draw();
		virtual bool		update(const GameTimer& gt);
		virtual bool		handleEvent();


		void ProcessInput();


	private:
		World				mWorld;
		Player&				mPlayer;
};

#endif // BOOK_GAMESTATE_HPP