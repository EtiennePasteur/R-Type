//
// Created by hippolyteb on 11/25/16.
//

#include "DummyMonster.hpp"
#include <PartitionSystem/EntityPartitionBuilder.hpp>
#include <Messages/FireProjectileMessage.hpp>
#include <Messages/ProjectilePositionChangedMessage.hpp>

DummyMonster::DummyMonster(const std::initializer_list<void *> init) : DummyMonster(*GetParamFromInitializerList<uint16_t *>(init, 0),
                                                                                    *GetParamFromInitializerList<std::shared_ptr<Timer>*>(init, 1),
                                                                                    *GetParamFromInitializerList<std::shared_ptr<RType::EventManager>*>(init, 2),
                                                                                    *GetParamFromInitializerList<TimeRef*>(init, 3),
                                                                                    *GetParamFromInitializerList<vec2<float>*>(init, 4)) { }

DummyMonster::DummyMonster(uint16_t id, std::shared_ptr<Timer> timer, std::shared_ptr<RType::EventManager> eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) :
        Entity(id, timer, eventManager), _eventListener(std::unique_ptr<RType::EventListener>(new RType::EventListener(eventManager)))
{
    _partition = EntityPartitionBuilder(timer, timeRef, startPosition).AddSegment(
                    PartitionSegmentBuilder()
                            .Begins(timeRef)
                            .For(std::chrono::seconds(10000))
                            .Translate(vec2<float>(0, 0))
                            .Fire(Entity::SIMPLE_PROJECTILE, 5))
            /*.AddSegment(PartitionSegmentBuilder()
                                .For(std::chrono::seconds(5))
                                .Translate(vec2<float>(-400, -400))
                                .WithCurving(new EaseOutCurve())
                                .Fire("SimpleProjectile", 3))
            .Loop(3)*/
            .Build();

    _eventListener->Subscribe<Entity, ProjectilePositionChangedMessage>(ProjectilePositionChangedMessage::EventType, [&](Entity *sender, ProjectilePositionChangedMessage *message) {
        auto segment = _partition.GetCurrentSegment(_timer->getCurrent());
        if (message->TestHitBox(segment->getLocationVector().GetTweened(), vec2<float>(32 * 5, 14 * 5), FireProjectileMessage::Origin::PROJECTILE_ORIGIN_ENVIRONEMENT))
        {
            message->DidHit(sender);
            this->Destroy();
        }
    });
}

void DummyMonster::Cycle() {
    auto now = _timer->getCurrent();
    if (_partition.ShouldFire(now)) {
        auto segment = _partition.GetCurrentSegment(now);
        std::uniform_int_distribution<uint16_t > uni(100, UINT16_MAX);
        _eventManager->Emit(FireProjectileMessage::EventType, new FireProjectileMessage(uni(_ramdomGenerator), segment->getCurrentProjectile(), segment->getLocationVector().GetTweened(), 180, FireProjectileMessage::Origin::PROJECTILE_ORIGIN_ENVIRONEMENT), this);
    }
}

vec2<float> DummyMonster::GetRenderRect() {
    return vec2<float>(32 * 5, 14 * 5);
}

vec2<float> DummyMonster::GetPosition() {
    return _partition.GetCurrentSegment(_timer->getCurrent())->getLocationVector().GetTweened();
}

void DummyMonster::Serialize(RType::Packer &packer) {
    Entity::Serialize(packer);
    _partition.Serialize(packer);
}

uint16_t DummyMonster::getTypeId() const {
    return Entity::DUMMY_MONSTER;
}

#ifndef ENTITY_DRW_CTOR
RTYPE_ENTITY_REGISTER(DummyMonster)
#endif