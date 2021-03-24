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

class World;

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
		void				registerState(States::ID stateID, World* world = nullptr);

		void				update(const GameTimer& gt);
		void				draw();
		void				handleEvent();

		void				pushState(States::ID stateID);
		void				popState();
		void				clearStates();

		bool				isEmpty() const;


	private:
		State::Ptr			createState(States::ID stateID);
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
void StateStack::registerState(States::ID stateID, World* world)
{
	mFactories[stateID] = [this, world] ()
	{
		return State::Ptr(new T(*this, mContext, world));
	};
}

#endif // BOOK_STATESTACK_HPP
