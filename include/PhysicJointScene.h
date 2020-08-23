////////////////////////////////////////////////////////////
// Project Physic Joint Scene
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
#ifndef PHYSICJOINTSCENE_H
#define PHYSICJOINTSCENE_H

#include <Nero/scene/Scene.h>
#include <Nero/object/PhysicObject.h>
#include <Nero/model/DistanceJoint.h>
#include <Nero/model/PrismaticJoint.h>
#include <Nero/model/RopeJoint.h>
#include <Nero/model/PulleyJoint.h>

namespace ng
{
	class PhysicJointScene : public nero::Scene
	{
	    public:
                                            PhysicJointScene(nero::Scene::Context context);
	        virtual                        ~PhysicJointScene();

	        void                            createJoint(nero::PhysicJoint::Type jointType);

	    protected:
	        void                            init();
			void                            checkSceneObject();
			sf::Vector2f		            getSceneResolution();
            void                            update(const sf::Time& timeStep);

            void                            handleKeyboardInput(const sf::Keyboard::Key& key, const bool& isPressed);
            void                            handleMouseButtonInput(const sf::Event::MouseButtonEvent& mouse, const bool& isPressed);
            void                            handleMouseMoveInput(const sf::Event::MouseMoveEvent& mouse);
            void                            handleMouseWheelInput(const sf::Event::MouseWheelScrollEvent& mouse);

	    private:
	        //joint selector
        	nero::PhysicJoint::Type         mJointType;
        	nero::PhysicObject::Ptr         mObjectA;
        	nero::PhysicObject::Ptr         mObjectB;


	        //01 Distance Joint
        	void                            createDistanceJoint();
        	nero::DistanceJoint::Ptr        mDistanceJoint;
        	//02 Prismatic Joint
        	void                            createPrismaticJoint();
        	nero::PrismaticJoint::Ptr       mPrismaticJoint;
        	float                           mPrismaticJointLimit;
        	//03 Rope Joint
        	void                            createRopeJoint();
        	//04 Rope Joint
        	void                            createPulleyJoint();
        	nero::PulleyJoint::Ptr          mPulleyJoint;

        private:
            float                           distance(nero::PhysicObject::Ptr objectA, nero::PhysicObject::Ptr objectB);



	};
}


#endif // PHYSICJOINTSCENE_H
