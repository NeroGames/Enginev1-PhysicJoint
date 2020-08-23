////////////////////////////////////////////////////////////
// Project Physic Joint Scene
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////

// The Macro NERO_RENDER_ENGINE allows you to run the DevEngine when CodeBlocks is in Debug Mode
// and the Render Engine CodeBlocks is in Release Mode

#ifndef NERO_RENDER_ENGINE

    #include <Nero/engine/DevEngine.h>
    #include "PhysicJointScene.h"


    int main()
    {
        nero::DevEngine engine(1900);
            engine.addScene<ng::PhysicJointScene>("PhysicJointScene");
        engine.run();

        return 0;
    }

#else

    #include <Nero/engine/RenderEngine.h>
    #include "PhysicJointScene.h"
    #include "LoadingScreen.h"

    int main()
    {
        auto startupScreen = std::make_shared<ng::LoadingScreen>();

        nero::RenderEngine engine(startupScreen);
            engine.setScene<ng::PhysicJointScene>("PhysicJointScene");
        engine.run();

        return 0;
    }

#endif // NERO_RENDER_ENGINE

