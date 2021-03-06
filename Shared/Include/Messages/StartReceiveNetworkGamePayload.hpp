//
// Created by hippolyteb on 12/18/16.
//

#ifndef R_TYPE_RECEIVENETWORKPAYLOADMESSAGE_HPP
#define R_TYPE_RECEIVENETWORKPAYLOADMESSAGE_HPP

#include <EventDispatcher/IMessage.hpp>
#include <EventDispatcher/Events.h>

class StartReceiveNetworkGamePayload : public IMessage {
public:
    static constexpr RType::Event EventType = RType::START_RECEIVE_NET_MESSAGE;

public:
    StartReceiveNetworkGamePayload() {}
};

#endif //R_TYPE_RECEIVENETWORKPAYLOADMESSAGE_HPP
