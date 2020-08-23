////////////////////////////////////////////////////////////
// Project Physic Joint Scene
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include <Nero/engine/StartupScreen.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace ng
{
    class LoadingScreen : public nero::StartupScreen
    {
        public:
                                    LoadingScreen();
            void                    init();
            void                    handleEvent(sf::Event& event);
            void                    update(const sf::Time& timeStep);
            void                    render();
            const sf::Color         getBackgroundColor()    const;
            const float             getMinTime()            const;

        private:
            sf::Texture             m_LogoTexture;
            sf::Sprite              m_LogoSprite;
    };

}

#endif // LOADINGSCREEN_H
