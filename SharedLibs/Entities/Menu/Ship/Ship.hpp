//
// Created by pasteu_e on 08/12/16.
//

#ifndef R_TYPE_SHIP_HPP
#define R_TYPE_SHIP_HPP

#include "PartitionSystem/EntityPartition.hpp"
#include <Time/Timer.hpp>
#include <Base.h>
#include <Entities/Entity.hpp>
#include <EventDispatcher/EventManager.hpp>
#include "PartitionSystem/PartitionSegmentBuilder.hpp"

class Ship : public Entity {
protected:
    EntityPartition _partition = EntityPartition(_timer);

public:
    Ship(const std::initializer_list<void *> init);
    Ship(uint16_t, std::shared_ptr<Timer>, std::shared_ptr<RType::EventManager>, TimeRef const &, vec2<float> const &);

    uint16_t getTypeId() const override;

    void Cycle() override;
    vec2<float> GetRenderRect() override;
    vec2<float> GetPosition() override;

    void Serialize(RType::Packer &packer) override;
};


#endif //R_TYPE_SHIP_HPP
