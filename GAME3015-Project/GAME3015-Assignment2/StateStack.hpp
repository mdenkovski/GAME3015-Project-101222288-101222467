#ifndef BOOK_STATESTACK_HPP
#define BOOK_STATESTACK_HPP

#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"
#include "../../Common/d3dApp.h"
//#include "Game.hpp"

//#include <SFML/System/NonCopyable.hpp>
//#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>

//
//namespace sf
//{
//	class Event;
//	class RenderWindow;
//}

class Game;

class StateStack //: private sf::NonCopyable
{
	public:
		enum Action
		{
			Push,
			Pop,
			Clear,
		};


	public:		
		explicit			StateStack(State::Context context);

		template <typename T>
		void				registerState(States::ID stateID, Game* game);

		void				update(const GameTimer& gt);
		void				draw();
		void				handleEvent();

		void				pushState(States::ID stateID);
		void				popState();
		void				clearStates();

		bool				isEmpty() const;


	private:
		State::Ptr			createState(States::ID stateID);
	public:
		void				applyPendingChanges();


	private:
		struct PendingChange
		{
			explicit			PendingChange(Action action, States::ID stateID = States::None);

			Action				action;
			States::ID			stateID;
		};


	private:
		std::vector<State::Ptr>								mStack;
		std::vector<PendingChange>							mPendingList;

		State::Context										mContext;
		std::map<States::ID, std::function<State::Ptr()>>	mFactories;
};


template <typename T>
void StateStack::registerState(States::ID stateID, Game* game)
{
	mFactories[stateID] = [this, game] ()
	{
		return State::Ptr(new T(*this, mContext, game));
	};

}

#endif // BOOK_STATESTACK_HPP
