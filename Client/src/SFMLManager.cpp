//
// Created by pasteu_e on 27/11/16.
//

#include <thread>
#include <iostream>
#include "RTypeMenuContext.hpp"
#include "SFMLManager.hpp"
#include "RTypeGameContext.hpp"
#include <SFML/OpenGL.hpp>

SFMLManager::SFMLManager() : _inputListener(new RTypeInputListener()), _gameContext(new RTypeGameContext("sprites/testPartition.partition")), _menuContext(new RTypeMenuContext()) {

}

void SFMLManager::Run() {
    sf::VideoMode desktop =  sf::VideoMode::getDesktopMode();
    sf::RenderWindow _window(sf::VideoMode(Width, Height, desktop.bitsPerPixel), "R-Type");
    glEnable(GL_TEXTURE_2D);
    _window.setVerticalSyncEnabled(true);
    _window.setFramerateLimit(60);
    // Boucle de jeu.
    sf::RenderTexture context;
    context.create(Width, Height);
    while (_window.isOpen()) {
        _inputListener->CheckForInputs(_window);
        _gameContext->Draw(context, _textureBag);
        sf::Sprite sprite(context.getTexture());
        _window.draw(sprite);
        _window.display();
    }
}
