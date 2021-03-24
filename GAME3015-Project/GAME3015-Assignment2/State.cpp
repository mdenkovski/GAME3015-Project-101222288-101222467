#include "State.hpp"
#include "StateStack.hpp"


State::Context::Context(Player& player)
:  player(&player)
{
}

State::State(StateStack& stack, Context context, World* world)
: mStack(&stack)
, mContext(context)
, mWorld(world)
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}

State::Context State::getContext() const
{
	return mContext;
}
