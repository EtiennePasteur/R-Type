//
// Created by hippolyteb on 11/25/16.
//

#include "Player.hpp"
#include <Messages/FireProjectileMessage.hpp>

Player::Player(const std::initializer_list<void *> init) : Player(*GetParamFromInitializerList<uint16_t  *>(init, 0), *GetParamFromInitializerList<std::shared_ptr<Timer>*>(init, 1), *GetParamFromInitializerList<std::shared_ptr<RType::EventManager>*>(init, 2), *GetParamFromInitializerList<TimeRef*>(init, 3), *GetParamFromInitializerList<vec2<float>*>(init, 4)) { }

Player::Player(uint16_t id, std::shared_ptr<Timer> timer, std::shared_ptr<RType::EventManager> eventManager, TimeRef const &timeRef, vec2<float> const &startPosition) : Entity(id, timer, eventManager) {

}

void Player::Cycle() {
//    auto now = _timer->getCurrent();
//    if (_partition.ShouldFire(now)) {
//        auto segment = _partition.GetCurrentSegment(now);
//        _eventManager->Emit(FireProjectileMessage::EventType, new FireProjectileMessage(segment->getCurrentProjectile(), segment->getLocationVector().GetTweened()), this);
//    }
}

void Player::Serialize(RType::Packer &packer) {

}

RTYPE_ENTITY_REGISTER(Player)