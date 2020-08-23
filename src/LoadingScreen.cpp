////////////////////////////////////////////////////////////
// Project Physic Joint Scene
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
#include "LoadingScreen.h"
#include <Nero/utility/Utility.h>

namespace ng
{
    LoadingScreen::LoadingScreen(): nero::StartupScreen()
    {

    }

    void LoadingScreen::init()
    {
        /*
        //Build the Logo sprite
        m_LogoTexture.loadFromFile(nero::STARTUP_FOLDER + "/logo.png");
        m_LogoSprite.setTexture(m_LogoTexture);
        nero::centerOrigin(m_LogoSprite);
        m_LogoSprite.setPosition(sf::Vector2f(m_RenderWindow->getSize().x / 2.f, m_RenderWindow->getSize().x / 3.f));
        //*/
    }

    void LoadingScreen::handleEvent(sf::Event& event)
    {
        //handle events
    }

    void LoadingScreen::update(const sf::Time& timeStep)
    {
        //update
    }

    void LoadingScreen::render()
    {
         //m_RenderWindow->draw(m_LogoSprite);
    }

    const sf::Color LoadingScreen::getBackgroundColor() const
    {
        return sf::Color::White;
    }

    const float LoadingScreen::getMinTime() const
    {
        return 10.f; //seconds
    }
}

