#ifndef BOOK_STATE_HPP
#define BOOK_STATE_HPP

#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp""

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

class State
{
	public:
		typedef std::unique_ptr<State> Ptr;

		struct Context
		{
								Context(Player& player);
			Player*				player;
		};


	public:
							State(StateStack& stack, Context context);
		virtual				~State();

		virtual void		draw() = 0;
		virtual bool		update(const GameTimer& gt) = 0;
		virtual bool		handleEvent() = 0;


	protected:
		void				requestStackPush(States::ID stateID);
		void				requestStackPop();
		void				requestStateClear();

		Context				getContext() const;


	private:
		StateStack*			mStack;
		Context				mContext;
};

#endif // BOOK_STATE_HPP
