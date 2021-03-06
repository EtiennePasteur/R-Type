//
// Created by hippolyteb on 12/5/16.
//

#include "BigProjectile.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>
#include <Messages/ProjectilePositionChangedMessage.hpp>

#ifndef ENTITY_DRW_CTOR
RTYPE_ENTITY_REGISTER(BigProjectile)
#endif

BigProjectile::BigProjectile(const std::initializer_list<void *> init) :
        BigProjectile(*GetParamFromInitializerList<uint16_t *>(init, 0),
                         *GetParamFromInitializerList<std::shared_ptr<Timer>*>(init, 1),
                         *GetParamFromInitializerList<std::shared_ptr<RType::EventManager>*>(init, 2),
                         *GetParamFromInitializerList<TimeRef*>(init, 3),
                         *GetParamFromInitializerList<vec2<float>*>(init, 4),
                         GetParamFromInitializerList<std::initializer_list<void *>*>(init, 5))
{ }

BigProjectile::BigProjectile(uint16_t id,
                                   std::shared_ptr<Timer> timer,
                                   std::shared_ptr<RType::EventManager> eventManager,
                                   TimeRef const &timeRef,
                                   vec2<float> const &startPosition,
                                   const std::initializer_list<void *> *params) : Entity(id, timer, eventManager) {
    auto dest = vec2<float>(0, 0);

    if (params != nullptr) {
        _origin = *GetParamFromInitializerList<FireProjectileMessage::Origin *>(*params, 0);
        float direction = *GetParamFromInitializerList<float *>(*params, 1);
        dest = vec2<float>(1920 * cosf((float) ((direction * M_PI) / 90)),
                           1920 * sinf((float) ((direction * M_PI) / 90)));
    }
    _partition = EntityPartitionBuilder(timer, timeRef, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(timeRef)
                            .For(std::chrono::milliseconds(1200))
                            .Translate(dest))
            .Build();
}

void BigProjectile::Cycle() {
    if (_partition.isPartitionPlayed(_timer->getCurrent()))
        this->Destroy();
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    _eventManager->Emit(ProjectilePositionChangedMessage::EventType, new ProjectilePositionChangedMessage(_origin, pos, true), this);
}

vec2<float> BigProjectile::GetRenderRect() {
    return vec2<float>(65 * 2, 14 * 2);
}

vec2<float> BigProjectile::GetPosition() {
    auto pos = _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
    return pos;
}

void BigProjectile::Serialize(RType::Packer &packer) {
    Entity::Serialize(packer);
    _partition.Serialize(packer);
    packer.Pack(_origin);
}

uint16_t BigProjectile::getTypeId() const {
    return Entity::BIG_PROJECTILE;
}