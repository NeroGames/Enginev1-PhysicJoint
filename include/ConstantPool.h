////////////////////////////////////////////////////////////
// Project Physic Joint Scene
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
#ifndef CONSTANTPOOL_H
#define CONSTANTPOOL_H

namespace ng
{
	struct _ObjectPool
	{
		//Player
	    const std::string player			= "player";
	    const std::string ground			= "ground";
	    const std::string objectA			= "object_a";
	    const std::string objectB			= "object_b";
	    const std::string objectC			= "object_c";
	    const std::string jointType			= "joint_type";
	    const std::string ropeAnchor	    = "rope_anchor";
	};

	const struct
	{
	    const std::string distanceJoint      = "distance_joint";
	    const std::string prismaticJoint     = "prismatic_joint";
	    const std::string ropeJoint          = "rope_joint";
	    const std::string pulleyJoint        = "pulley_joint";
	    const std::string wheelJoint        = "wheel_joint";

	} LayerPool;

	struct _CategoryPool
	{
	    const std::string player             = "player";
	    const std::string ground             = "ground";
	    const std::string wall               = "wall";
	    const std::string power              = "power";
	    const std::string platform           = "platform";
	};

	struct _SoundPool
	{
	    const std::string sound01			= "sound01";
	};

	struct _MusicPool
	{
	    const std::string music01			= "music01";
	};

	struct _ScreenPool
	{
	    const std::string startScreen      	= "Start Screen";
	};

	struct _PlayerActionPool
	{
	    const std::string move_left          = "move_left";
	    const std::string move_right         = "move_right";
	    const std::string move_none          = "move_none";
	};


	const _ObjectPool           ObjectPool;
	const _CategoryPool         CategoryPool;
	const _SoundPool     		SoundPool;
	const _MusicPool   			MusicPool;
	const _ScreenPool           ScreenPool;
	const _PlayerActionPool		PlayerActionPool;
}

#endif // CONSTANTPOOL_H
