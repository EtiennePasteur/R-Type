//
// Created by aguado_e on 12/22/16.
//

#ifndef R_TYPE_GRAPHICBACKGROUND_HPP
#define R_TYPE_GRAPHICBACKGROUND_HPP

#include <AAnimatable.hpp>
#include <TextureBag.hpp>
#include "Background.hpp"

class GraphicBackground : public Background, public AAnimatable {

public:
    GraphicBackground(const std::initializer_list<void *> init);

    void Draw(sf::RenderTexture *rect, TextureBag &) override;
    void Cycle() override;
};


#endif //R_TYPE_GRAPHICBACKGROUND_HPP
