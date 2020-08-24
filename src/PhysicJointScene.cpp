////////////////////////////////////////////////////////////
// Project Physic Joint Scene
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
#include "PhysicJointScene.h"
#include "ConstantPool.h"
#include <Nero/scene/CollisionRule.h>
#include <Nero/object/TextObject.h>
#include <Nero/model/JointProperty.h>

namespace ng
{
	PhysicJointScene::PhysicJointScene(nero::Scene::Context context): nero::Scene(context)
		,mJointType(nero::PhysicJoint::None)
		,mPrismaticJointLimit(300.f)
		,mWheelSpeed(200.f)
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
        //
	    mJointType = nero::PhysicJoint::Gear_Joint;

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
	    mObjectA = nero::PhysicObject::Cast(objectA);
	    mObjectB = nero::PhysicObject::Cast(objectB);

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
        mObjectA = nero::PhysicObject::Cast(objectA);
	    mObjectB = nero::PhysicObject::Cast(objectB);


	    //configure joint
        nero::PrismaticJointProperty prismaticJoint;
        prismaticJoint.name                = "prismatic_joint";
        prismaticJoint.collideConnected    = false;
        prismaticJoint.localAnchorA        = sf::Vector2f(0.f, 0.f);
        prismaticJoint.localAnchorB        = sf::Vector2f(0.f, 0.f);
        prismaticJoint.localAxisA          = sf::Vector2f(0.f, 1.f);
        prismaticJoint.referenceAngle      = 0.f;
        prismaticJoint.enableLimit         = true;
        prismaticJoint.lowerTranslation    = -mPrismaticJointLimit;
        prismaticJoint.upperTranslation    = mPrismaticJointLimit;
        prismaticJoint.enableMotor         = true;
        prismaticJoint.maxMotorForce       = 50.f;
        prismaticJoint.motorSpeed          = 7.f;

        //create joint
        getObjectManager()->createJoint(objectA, objectB, prismaticJoint);

        //retrieve joint
        mPrismaticJoint = nero::PrismaticJoint::Cast(getObjectManager()->findJoint("prismatic_joint"));
    }

    void PhysicJointScene::createRopeJoint()
    {
        //check layer
        auto layer   = getObjectManager()->findLayerObject(LayerPool.ropeJoint);
        if(!layer) {log("ERROR : layer not found"); return;}

        int ropeSegmentCount = layer->getChildCount();

        for(int i  = 0; i < ropeSegmentCount - 1; i++)
        {
            auto objectAName = "rope_" + nero::toString(i);
            auto objectBName = "rope_" + nero::toString(i+1);

            auto objectA = getObjectManager()->findObjectInLayer(objectAName, LayerPool.ropeJoint);
            auto objectB = getObjectManager()->findObjectInLayer(objectBName, LayerPool.ropeJoint);
            if(!objectA || !objectB) {log("ERROR : object not found"); return;}

            //configure joint
            nero::RopeJointProperty ropeJoint;
            ropeJoint.name                = "rope_joint_" + nero::toString(i);
            ropeJoint.collideConnected    = false;
            ropeJoint.maxLength           = 10.f;

            float anchor = 30.f;

            if(i == 0)
            {
                ropeJoint.localAnchorA        = sf::Vector2f(0.f, 0.f);
                ropeJoint.localAnchorB        = sf::Vector2f(0.f, -anchor);
            }
            else
            {
                ropeJoint.localAnchorA        = sf::Vector2f(0.f, anchor);
                ropeJoint.localAnchorB        = sf::Vector2f(0.f, -anchor);
            }

            //create joint
            getObjectManager()->createJoint(objectA, objectB, ropeJoint);

        }
    }

    void PhysicJointScene::createPulleyJoint()
    {
        //retrieve objects
        auto layer   = getObjectManager()->findLayerObject(LayerPool.pulleyJoint);
        if(!layer) {log("ERROR : layer not found"); return;}
	    auto objectA = getObjectManager()->findObjectInLayer(ObjectPool.objectA, LayerPool.pulleyJoint);
	    auto objectB = getObjectManager()->findObjectInLayer(ObjectPool.objectB, LayerPool.pulleyJoint);
        if(!objectA || !objectB) {log("ERROR : object not found"); return;}
        mObjectA = nero::PhysicObject::Cast(objectA);
	    mObjectB = nero::PhysicObject::Cast(objectB);


	    //configure joint
        nero::PulleyJointProperty pulleyJoint;
        pulleyJoint.name    = "pulley_joint";
        pulleyJoint.collideConnected    = false;
        pulleyJoint.groundAnchorA       = sf::Vector2f(200.f, 75.f);
        pulleyJoint.groundAnchorB       = sf::Vector2f(800.f, 75.f);
        pulleyJoint.localAnchorA        = sf::Vector2f(0.f, 0.f);
        pulleyJoint.localAnchorB        = sf::Vector2f(0.f, 0.f);
        pulleyJoint.lengthA             = 300.f;
        pulleyJoint.lengthB             = 300.f;
        pulleyJoint.ratio               = 1.f;

        //create joint
        getObjectManager()->createJoint(objectA, objectB, pulleyJoint);

        //retrieve joint
        mPrismaticJoint = nero::PrismaticJoint::Cast(getObjectManager()->findJoint("pulley_joint"));
    }

    void PhysicJointScene::createWheelJoint()
    {
        //retrieve objects
        auto layer   = getObjectManager()->findLayerObject(LayerPool.wheelJoint);
        if(!layer) {log("ERROR : layer not found"); return;}
	    auto objectA = getObjectManager()->findObjectInLayer(ObjectPool.objectA, LayerPool.wheelJoint);
	    auto objectB = getObjectManager()->findObjectInLayer(ObjectPool.objectB, LayerPool.wheelJoint);
	    auto objectC = getObjectManager()->findObjectInLayer(ObjectPool.objectC, LayerPool.wheelJoint);
        if(!objectA || !objectB|| !objectC) {log("ERROR : object not found"); return;}
        mObjectA = nero::PhysicObject::Cast(objectA);
	    mObjectB = nero::PhysicObject::Cast(objectB);
	    mObjectC = nero::PhysicObject::Cast(objectC);


	    //configure joint (Wheel 1)
        nero::WheelJointProperty wheelJoint;
        wheelJoint.name                = "wheel_joint_a";
        wheelJoint.collideConnected    = true;
        wheelJoint.localAnchorA        = sf::Vector2f(0.f, 0.f);
        wheelJoint.localAnchorB        = sf::Vector2f(0.f, 0.f);
        wheelJoint.localAxisA          = sf::Vector2f(0.f, 1.f);
        wheelJoint.referenceAngle      = 0.f;
        wheelJoint.enableMotor         = true;
        wheelJoint.maxMotorForce       = 100.f;
        wheelJoint.motorSpeed          = 0.f;
        wheelJoint.frequencyHz         = 10.f;
        wheelJoint.dampingRatio        = 0.5f;
        //create joint
        getObjectManager()->createJoint(objectA, objectB, wheelJoint);
        //retrieve joint
        mWheelJointA = nero::WheelJoint::Cast(getObjectManager()->findJoint("wheel_joint_a"));

        //configure joint (Wheel 1)
        wheelJoint.name                 = "wheel_joint_b";
        wheelJoint.enableMotor          = false;
         //create joint
        getObjectManager()->createJoint(objectA, objectC, wheelJoint);
        //retrieve joint
        mWheelJointB = nero::WheelJoint::Cast(getObjectManager()->findJoint("wheel_joint_b"));



        ////////////////////////////////////////////////////////////////////////////////////////////////////
        //configure joint (Wheel 1)
        nero::DistanceJointProperty distanceJoint;
        distanceJoint.name                = "distance_joint_01";
        distanceJoint.collideConnected    = false;
        distanceJoint.localAnchorA        = sf::Vector2f(-150.f, 95.f);
        distanceJoint.localAnchorB        = sf::Vector2f(0.f, 0.f);
        distanceJoint.length              = 0.f;
        distanceJoint.frequencyHz         = 0.f;
        distanceJoint.dampingRatio        = 0.1f;
        //create joint
        getObjectManager()->createJoint(objectA, objectB, distanceJoint);

        //configure joint (Wheel 1)
        distanceJoint.name                = "distance_joint_02";
        distanceJoint.localAnchorA        = sf::Vector2f(150.f, 95.f);
        //create joint
        getObjectManager()->createJoint(objectA, objectC, distanceJoint);

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        setCameraTarget(objectA);
        updateTargetOffset(100.f, 100.f, 400.f, 0.f);

    }

    void PhysicJointScene::createWeldJoint()
    {
        //retrieve objects
        auto layer   = getObjectManager()->findLayerObject(LayerPool.weldJoint);
        if(!layer) {log("ERROR : layer not found"); return;}
	    auto objectA = getObjectManager()->findObjectInLayer(ObjectPool.objectA, LayerPool.weldJoint);
	    auto objectB = getObjectManager()->findObjectInLayer(ObjectPool.objectB, LayerPool.weldJoint);
        if(!objectA || !objectB) {log("ERROR : object not found"); return;}
        mObjectA = nero::PhysicObject::Cast(objectA);
	    mObjectB = nero::PhysicObject::Cast(objectB);

	    //configure joint
        nero::WeldJointProperty weldJoint;
        weldJoint.name                = "weld_joint";
        weldJoint.collideConnected    = false;
        weldJoint.localAnchorA        = sf::Vector2f(0.f, 50.f);
        weldJoint.localAnchorB        = sf::Vector2f(0.f, -50.f);
        weldJoint.referenceAngle      = 0.f;
        weldJoint.frequencyHz         = 5.f;
        weldJoint.dampingRatio        = 0.5f;

        //create joint
        getObjectManager()->createJoint(objectA, objectB, weldJoint);

        //retrieve joint
        mWeldJoint = nero::WeldJoint::Cast(getObjectManager()->findJoint("weld_joint"));
    }

    void PhysicJointScene::createRevoluteJoint()
    {
        //retrieve objects
        auto layer   = getObjectManager()->findLayerObject(LayerPool.revoluteJoint);
        if(!layer) {log("ERROR : layer not found"); return;}
	    auto objectA = getObjectManager()->findObjectInLayer(ObjectPool.objectA, LayerPool.revoluteJoint);
	    auto objectB = getObjectManager()->findObjectInLayer(ObjectPool.objectB, LayerPool.revoluteJoint);
        if(!objectA || !objectB) {log("ERROR : object not found"); return;}
        mObjectA = nero::PhysicObject::Cast(objectA);
	    mObjectB = nero::PhysicObject::Cast(objectB);

	    //configure joint
        nero::RevoluteJointProperty revoluteJoint;
        revoluteJoint.name                = "revolute_joint";
        revoluteJoint.collideConnected    = false;
        revoluteJoint.localAnchorA        = sf::Vector2f(0.f, 0.f);
        revoluteJoint.localAnchorB        = sf::Vector2f(0.f, -220.f);
        revoluteJoint.referenceAngle      = 0.f;
        revoluteJoint.enableLimit         = false;
        revoluteJoint.lowerAngle          = 0.f;
        revoluteJoint.upperAngle          = 0.f;
        revoluteJoint.enableMotor         = true;
        revoluteJoint.maxMotorForce       = 50.f;
        revoluteJoint.motorSpeed          = 10.f;

        //create joint
        getObjectManager()->createJoint(objectA, objectB, revoluteJoint);

        //retrieve joint
        mRevoluteJoint = nero::RevoluteJoint::Cast(getObjectManager()->findJoint("revolute_joint"));
    }

    void PhysicJointScene::createGearJoint()
    {
        //retrieve objects
        auto layer   = getObjectManager()->findLayerObject(LayerPool.gearJoint);
        if(!layer) {log("ERROR : layer not found"); return;}
	    auto objectA = getObjectManager()->findObjectInLayer(ObjectPool.objectA, LayerPool.gearJoint);
	    auto objectB = getObjectManager()->findObjectInLayer(ObjectPool.objectB, LayerPool.gearJoint);
	    auto objectC = getObjectManager()->findObjectInLayer(ObjectPool.objectC, LayerPool.gearJoint);
	    auto objectD = getObjectManager()->findObjectInLayer(ObjectPool.objectD, LayerPool.gearJoint);
        if(!objectA || !objectB || !objectC || !objectD) {log("ERROR : object not found"); return;}
        mObjectA = nero::PhysicObject::Cast(objectA);
	    mObjectB = nero::PhysicObject::Cast(objectB);
	    mObjectC = nero::PhysicObject::Cast(objectC);
	    mObjectC = nero::PhysicObject::Cast(objectD);


	    //////////////////////////////////////////////////////////////////////////////
        //configure joint
        nero::RevoluteJointProperty revoluteJoint;
        revoluteJoint.name                = "revolute_joint";
        revoluteJoint.collideConnected    = false;
        revoluteJoint.localAnchorA        = sf::Vector2f(0.f, 0.f);
        revoluteJoint.localAnchorB        = sf::Vector2f(0.f, 0.f);
        revoluteJoint.referenceAngle      = 0.f;
        revoluteJoint.enableLimit         = false;
        revoluteJoint.lowerAngle          = 0.f;
        revoluteJoint.upperAngle          = 0.f;
        revoluteJoint.enableMotor         = false;
        revoluteJoint.maxMotorForce       = 50.f;
        revoluteJoint.motorSpeed          = 10.f;
        //create joint
        getObjectManager()->createJoint(objectC, objectA, revoluteJoint);
        //retrieve joint
        mRevoluteJoint = nero::RevoluteJoint::Cast(getObjectManager()->findJoint("revolute_joint"));
        //////////////////////////////////////////////////////////////////////////////
        //configure joint
        nero::PrismaticJointProperty prismaticJoint;
        prismaticJoint.name                = "prismatic_joint";
        prismaticJoint.collideConnected    = false;
        prismaticJoint.localAnchorA        = sf::Vector2f(0.f, 0.f);
        prismaticJoint.localAnchorB        = sf::Vector2f(0.f, 0.f);
        prismaticJoint.localAxisA          = sf::Vector2f(0.f, 1.f);
        prismaticJoint.referenceAngle      = 0.f;
        prismaticJoint.enableLimit         = true;
        prismaticJoint.lowerTranslation    = -mPrismaticJointLimit;
        prismaticJoint.upperTranslation    = mPrismaticJointLimit;
        prismaticJoint.enableMotor         = true;
        prismaticJoint.maxMotorForce       = 50.f;
        prismaticJoint.motorSpeed          = 7.f;
        //create joint
        getObjectManager()->createJoint(objectD, objectB, prismaticJoint);
        //retrieve joint
        mPrismaticJoint = nero::PrismaticJoint::Cast(getObjectManager()->findJoint("prismatic_joint"));
        //////////////////////////////////////////////////////////////////////////////

	    //configure joint
        nero::GearJointProperty gearJoint;
        gearJoint.name                = "gear_joint";
        gearJoint.collideConnected    = false;
        gearJoint.jointAId            = mRevoluteJoint->getJointId();
        gearJoint.jointBId            = mPrismaticJoint->getJointId();
        gearJoint.ratio               = 1.f;

        //create joint
        getObjectManager()->createJoint(objectA, objectB, gearJoint);

        //retrieve joint
        mGearJoint = nero::GearJoint::Cast(getObjectManager()->findJoint("gear_joint"));
    }

    void PhysicJointScene::createFrictionJoint()
    {

    }

	void PhysicJointScene::handleKeyboardInput(const sf::Keyboard::Key& key, const bool& isPressed)
    {
        if(mDistanceJoint && isPressed)
        {
            if(key == sf::Keyboard::Up)
                mDistanceJoint->getJoint()->SetLength(mDistanceJoint->getJoint()->GetLength() - 0.1f);
            else if(key == sf::Keyboard::Down)
                mDistanceJoint->getJoint()->SetLength(mDistanceJoint->getJoint()->GetLength() + 0.1f);
        }

        if(mWheelJointA && isPressed)
        {
            if(key == sf::Keyboard::Left)
                mWheelJointA->getJoint()->SetMotorSpeed(-mWheelSpeed);
            else if(key == sf::Keyboard::Right)
                mWheelJointA->getJoint()->SetMotorSpeed(mWheelSpeed);
            else if(key == sf::Keyboard::Down)
            {
                mWheelJointA->getJoint()->SetMotorSpeed(0.f);
                //mObjectA->clearForce();
                mObjectB->clearAngularVelocity();
                mObjectC->clearAngularVelocity();
            }

        }
        else if(mWheelJointA && !isPressed)
        {
            if(key == sf::Keyboard::Left || key == sf::Keyboard::Right)
                mWheelJointA->getJoint()->SetMotorSpeed(0.f);
        }
    }

    void PhysicJointScene::handleMouseButtonInput(const sf::Event::MouseButtonEvent& mouse, const bool& isPressed)
    {

    }

    void PhysicJointScene::handleMouseMoveInput(const sf::Event::MouseMoveEvent& mouse)
    {

    }

    void PhysicJointScene::handleMouseWheelInput(const sf::Event::MouseWheelScrollEvent& mouse)
    {

    }

    void PhysicJointScene::update(const sf::Time& timeStep)
    {
        nero::Scene::update(timeStep);

        if(mPrismaticJoint)
        {
            if(distance(mObjectA, mObjectB) >= (mPrismaticJointLimit -1.f))
            {
                mPrismaticJoint->getJoint()->SetMotorSpeed(-mPrismaticJoint->getJoint()->GetMotorSpeed());
            }
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

            case nero::PhysicJoint::Rope_Joint:
            {
                createRopeJoint();

                joint_type = "Rope Joint";

            }break;

            case nero::PhysicJoint::Pulley_Joint:
            {
                createPulleyJoint();

                joint_type = "Pulley Joint";

            }break;

            case nero::PhysicJoint::Wheel_Joint:
            {
                createWheelJoint();

                joint_type = "Wheel Joint";

            }break;

            case nero::PhysicJoint::Weld_Joint:
            {
                createWeldJoint();

                joint_type = "Weld Joint";

            }break;

            case nero::PhysicJoint::Revolute_Joint:
            {
                createRevoluteJoint();

                joint_type = "Revolute Joint";

            }break;

            case nero::PhysicJoint::Gear_Joint:
            {
                createGearJoint();

                joint_type = "Gear Joint";

            }break;

            case nero::PhysicJoint::Friction_Joint:
            {
                createFrictionJoint();

                joint_type = "Friction Joint";

            }break;
        }

        nero::TextObject::Cast(getObjectManager()->findObject(ObjectPool.jointType))->setContent(joint_type);

    }

    float PhysicJointScene::distance(nero::PhysicObject::Ptr objectA, nero::PhysicObject::Ptr objectB)
    {
        return nero::distance(objectA->getCenter(), objectB->getCenter());
    }


}
