////////////////////////////////////////////////////////////
// Project Physic Joint Scene
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
#include "Player.h"
#include "ConstantPool.h"
#include <Nero/utility/Utility.h>

namespace ng
{
	Player::Player(): PhysicActionObject()
	{
	    registerAction<nero::MoveAction>(PlayerActionPool.move_left, nero::getMoveLeftAction(100.f));
	    registerAction<nero::MoveAction>(PlayerActionPool.move_right, nero::getMoveRightAction(100.f));
	    registerAction<nero::MoveAction>(PlayerActionPool.move_none, nero::getMoveNoneXAction());
	}

	Player::~Player()
	{
	    //dtor
	}

	void Player::setObject(Object::Ptr object)
	{
	    nero::PhysicActionObject::setObject(object);

	    mPhysic     = nero::PhysicObject::Cast(getObject());
	}


	void Player::update(const sf::Time& timeStep)
	{
	    //update parent
	    nero::PhysicActionObject::update(timeStep);
	}
}



