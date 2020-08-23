////////////////////////////////////////////////////////////
// Project Physic Joint Scene
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
#include "PhysicJointScene.h"
#include "ConstantPool.h"
#include <Nero/scene/CollisionRule.h>
#include <Nero/object/TextObject.h>
#include <Nero/model/DistanceJoint.h>
#include <Nero/model/JointProperty.h>

namespace ng
{
	PhysicJointScene::PhysicJointScene(nero::Scene::Context context): nero::Scene(context)
		,mJointType(nero::PhysicJoint::None)
	{
		//ctr
	}

	PhysicJointScene::~PhysicJointScene()
	{
	    //dtr
	}

	void PhysicJointScene::checkSceneObject()
    {
    	log("checking Scene Objects ...");

    	log("checking World Objects ...");
	    getObjectManager()->checkWorldObject(
	    {
           //list of objects here
	    });

	    log("checking Screen Objects ...");
	    getObjectManager()->checkScreenObject(

	       ScreenPool.startScreen,

	       {
                //list of objects here
	       }
	    );
    }

	sf::Vector2f PhysicJointScene::getSceneResolution()
	{
        log("Setting up Resolution ...");

	    return sf::Vector2f(1280.f, 720.f);
	}

	void PhysicJointScene::init()
	{
	    log("PhysicJointScene Scene v0.1");

        //select joint type
	    mJointType = nero::PhysicJoint::Distance_Joint;

        createJoint(mJointType);

	}

	void PhysicJointScene::createDistanceJoint()
	{

        //retrieve objects
        auto layer   = getObjectManager()->findLayerObject(LayerPool.distanceJoint);
        if(!layer) {log("ERROR : layer not found"); return;}
        auto objectA =  getObjectManager()->findObjectInLayer(ObjectPool.objectA, LayerPool.distanceJoint);
	    auto objectB =  getObjectManager()->findObjectInLayer(ObjectPool.objectB, LayerPool.distanceJoint);
	    if(!objectA || !objectB) {log("ERROR : object not found"); return;}

	    //configure joint
        nero::DistanceJointProperty distanceJoint;
        distanceJoint.name                = "distance_joint";
        distanceJoint.collideConnected    = false;
        distanceJoint.localAnchorA        = sf::Vector2f(0.f, 0.f);
        distanceJoint.localAnchorB        = sf::Vector2f(0.f, 0.f);
        distanceJoint.length              = 300.f;
        distanceJoint.frequencyHz         = 5.f;
        distanceJoint.dampingRatio        = 0.5f;

        //create joint
        getObjectManager()->createJoint(objectA, objectB, distanceJoint);

        //retrieve joint
        mDistanceJoint = nero::DistanceJoint::Cast(getObjectManager()->findJoint("distance_joint"));
	}

    void PhysicJointScene::createPrismaticJoint()
    {
        //retrieve objects
        auto layer   = getObjectManager()->findLayerObject(LayerPool.prismaticJoint);
        if(!layer) {log("ERROR : layer not found"); return;}
	    auto objectA = getObjectManager()->findObjectInLayer(ObjectPool.objectA, LayerPool.prismaticJoint);
	    auto objectB = getObjectManager()->findObjectInLayer(ObjectPool.objectB, LayerPool.prismaticJoint);
        if(!objectA || !objectB) {log("ERROR : object not found"); return;}

	    //configure joint
        nero::PrismaticJointProperty prismaticJoint;
        prismaticJoint.name                = "prismatic_joint";
        prismaticJoint.collideConnected    = false;
        prismaticJoint.localAnchorA        = sf::Vector2f(0.f, 0.f);
        prismaticJoint.localAnchorB        = sf::Vector2f(0.f, 0.f);
        prismaticJoint.localAxisA          = sf::Vector2f(1.f, 0.f);
        prismaticJoint.referenceAngle      = 0.f;
        prismaticJoint.enableLimit         = true;
        prismaticJoint.lowerTranslation    = -500.f;
        prismaticJoint.upperTranslation    = 500.f;
        prismaticJoint.enableMotor         = true;
        prismaticJoint.maxMotorForce       = 50.f;
        prismaticJoint.motorSpeed          = -10.f;

        //create joint
        getObjectManager()->createJoint(objectA, objectB, prismaticJoint);

        //retrieve joint
        mPrismaticJoint = nero::PrismaticJoint::Cast(getObjectManager()->findJoint("prismatic_joint"));
    }


	void PhysicJointScene::handleKeyboardInput(const sf::Keyboard::Key& key, const bool& isPressed)
    {
        switch(mJointType)
        {
            case nero::PhysicJoint::Distance_Joint:
            {
                if(key == sf::Keyboard::Up)
                    mDistanceJoint->getJoint()->SetLength(mDistanceJoint->getJoint()->GetLength() - 0.1f);
                else if(key == sf::Keyboard::Down)
                    mDistanceJoint->getJoint()->SetLength(mDistanceJoint->getJoint()->GetLength() + 0.1f);
            }break;
        }
    }

    void PhysicJointScene::handleMouseButtonInput(const sf::Event::MouseButtonEvent& mouse, const bool& isPressed)
    {
        switch(mJointType)
        {
            case nero::PhysicJoint::Distance_Joint:
            {

            }break;
        }
    }

    void PhysicJointScene::handleMouseMoveInput(const sf::Event::MouseMoveEvent& mouse)
    {
        switch(mJointType)
        {
            case nero::PhysicJoint::Distance_Joint:
            {

            }break;
        }
    }

    void PhysicJointScene::handleMouseWheelInput(const sf::Event::MouseWheelScrollEvent& mouse)
    {
        switch(mJointType)
        {
            case nero::PhysicJoint::Distance_Joint:
            {

            }break;
        }
    }

    void PhysicJointScene::update(const sf::Time& timeStep)
    {
        nero::Scene::update(timeStep);

        switch(mJointType)
        {
            case nero::PhysicJoint::Distance_Joint:
            {

            }break;
        }
    }

    void PhysicJointScene::createJoint(nero::PhysicJoint::Type jointType)
    {
        std::string joint_type = "Joint Type";

        switch(jointType)
        {
            case nero::PhysicJoint::Distance_Joint:
            {
                createDistanceJoint();

                joint_type = "Distance Joint";

            }break;

            case nero::PhysicJoint::Prismatic_Joint:
            {
                createPrismaticJoint();

                joint_type = "Prismatic Joint";

            }break;
        }

        nero::TextObject::Cast(getObjectManager()->findObject(ObjectPool.jointType))->setContent(joint_type);

    }

}
