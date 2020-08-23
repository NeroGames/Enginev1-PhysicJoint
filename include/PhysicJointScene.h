////////////////////////////////////////////////////////////
// Project Physic Joint Scene
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
#ifndef PHYSICJOINTSCENE_H
#define PHYSICJOINTSCENE_H

#include <Nero/scene/Scene.h>
#include <Nero/model/DistanceJoint.h>
#include <Nero/model/PrismaticJoint.h>

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


	        //01 Distance Joint
        	void                            createDistanceJoint();
        	nero::DistanceJoint::Ptr        mDistanceJoint;
        	//02 Prismatic Joint
        	void                            createPrismaticJoint();
        	nero::PrismaticJoint::Ptr       mPrismaticJoint;



	};
}


#endif // PHYSICJOINTSCENE_H
