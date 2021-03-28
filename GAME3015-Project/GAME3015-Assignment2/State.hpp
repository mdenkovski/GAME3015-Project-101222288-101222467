#ifndef BOOK_STATE_HPP
#define BOOK_STATE_HPP

#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"

#include "../../Common/d3dApp.h"
//#include "Game.hpp"

//#include <SFML/System/Time.hpp>
//#include <SFML/Window/Event.hpp>

#include <memory>

//
//namespace sf
//{
//	class RenderWindow;
//}

class StateStack;
class Player;
class Game;

class State
{
	public:
		typedef std::unique_ptr<State> Ptr;

		struct Context
		{
								Context(Player& player);

			//sf::RenderWindow*	window;
			//TextureHolder*		textures;
			//FontHolder*			fonts;
			Player*				player;
		};


	public:
							State(StateStack& stack, Context context, Game* game);
		virtual				~State();

		virtual void		draw() = 0;
		virtual bool		update(const GameTimer& gt) = 0;
		virtual bool		handleEvent(WPARAM btnState) = 0;

		virtual void		BuildScene() = 0;

		Game*				mGame;
	protected:
		void				requestStackPush(States::ID stateID);
		void				requestStackPop();
		void				requestStateClear();

		Context				getContext() const;

		//Game*				mGame;
		StateStack*			mStack;
	private:
		
		Context				mContext;
};

#endif // BOOK_STATE_HPP
