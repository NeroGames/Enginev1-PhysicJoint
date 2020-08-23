////////////////////////////////////////////////////////////
// Project Physic Joint Scene
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
#ifndef PLAYER_H
#define PLAYER_H

#include <Nero/gamelib.h>
#include <Nero/object/PhysicObject.h>

namespace ng
{
	class Player : public nero::PhysicActionObject
	{
	    public:
	                                	Player();
	        virtual                	   ~Player();

	        void                    	update(const sf::Time& timeStep);
	        void                    	setObject(Object::Ptr object);

	    private:
	        nero::PhysicObject::Ptr		mPhysic;
	};
}

#endif // PLAYER_H
