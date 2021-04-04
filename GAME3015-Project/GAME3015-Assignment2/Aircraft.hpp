#pragma once
#include "Entity.hpp"
#include <string>

class Aircraft :
    public Entity
{
public:

	enum class Type
	{
		Eagle,
		Raptor,
	};


public:
	Aircraft(Type type, State* state);
	virtual unsigned int getCategory() const;


private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();


private:
	Type				mType;
	std::string			mSprite;
	RenderItem* mAircraftRitem;
};
