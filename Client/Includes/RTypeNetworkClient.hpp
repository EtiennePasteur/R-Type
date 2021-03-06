//
// Created by pasteu_e on 27/11/16.
//

#ifndef R_TYPE_RTYPENETWORKCLIENT_HPP
#define R_TYPE_RTYPENETWORKCLIENT_HPP


#include <memory>
#include <thread>
#include <Socket/IRTypeSocket.hpp>
#include <RTypeSocket.hpp>
#include <Socket/Enum/RTypeSocketType.h>
#include <EventDispatcher/EventListener.hpp>

class RTypeNetworkClient {
private:
    std::string _currentServerIp = "127.0.0.1";
    std::unique_ptr<IRTypeSocket> _networkClient = nullptr;
    std::unique_ptr<IRTypeSocket> _networkGameClient = std::unique_ptr<IRTypeSocket>(new RTypeSocket<UDP>(9875));
    std::unique_ptr<IRTypeSocket> _networkGameUpClient = nullptr;
    std::shared_ptr<RType::EventManager> _eventManager;
    RType::EventListener _eventListener;
    std::unique_ptr<std::thread> _receiverThread = nullptr;

    bool _poisonPill = false;

public:
    RTypeNetworkClient(const std::shared_ptr<RType::EventManager> &eventManager, const std::string &serverIp);

private:
    void StartReceive();

public:
    void StopReceive();
    bool TryToConnect();
    bool TryReceive(const int timeout, std::shared_ptr<RTypeNetworkPayload> payload);
    bool TryToSend(const int timeout, std::shared_ptr<RTypeNetworkPayload> payload);
};


#endif //R_TYPE_RTYPENETWORKCLIENT_HPP
