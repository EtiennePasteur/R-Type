//
// Created by pasteu_e on 17/12/16.
//

#include <Messages/NewClientConnectionMessage.hpp>
#include <Messages/ReceivedTCPNetworkPayloadMessage.hpp>
#include "LobbyManager/LobbyManager.hpp"
#include <Messages/SendTCPNetworkPayloadMessage.hpp>

void LobbyManager::Start() {
    auto sub = RType::EventListener(_eventManager);
    sub.Subscribe<void, NewClientConnectionMessage>(NewClientConnectionMessage::EventType, [&](void *sender, NewClientConnectionMessage *message) {
        _clients[_i++] = message->getClient();
    });
    sub.Subscribe<void, SendTCPNetworkPayloadMessage>(SendTCPNetworkPayloadMessage::EventType, [&](void *sender, SendTCPNetworkPayloadMessage *message) {
        _toSend.push_back(std::make_pair(message->getDestination(), message->ConvertToSocketMessage()));
    });
    sub.Subscribe<void, ReceivedTCPNetworkPayloadMessage>(ReceivedTCPNetworkPayloadMessage::EventType, [&](void *sender, ReceivedTCPNetworkPayloadMessage *message) {
        std::string data = std::string(message->getPayload()->Payload);
        if (data.find("[CREATE]") != std::string::npos) {
            std::string roomName = data.substr(data.find("]") + 1);
            if (CreateInstance(roomName)) {
                auto player = std::make_shared<PlayerRef>(message->getId(), message->getPayload()->Ip);
                JoinInstance(roomName, player);
            }
        } else if (data.find("[JOIN]") != std::string::npos) {
            std::string roomName = data.substr(data.find("]") + 1);
            auto player = std::make_shared<PlayerRef>(message->getId(), message->getPayload()->Ip);
            JoinInstance(roomName, player);
        } else if (data.find("[READY]") != std::string::npos) {
            std::string roomName = data.substr(data.find("]") + 1);
            if (_instances.find(roomName) != _instances.end()) {
                _instances[roomName]->SetReady(message->getId(), true);
            }
        } else if (data.find("[QUIT]") != std::string::npos) {
            std::string roomName = data.substr(data.find("]") + 1);
            LeftInstance(roomName, message->getId());
        }
    });
    Run();
}

void LobbyManager::Run() {
    while (true) {
        _networkManager.IsThereNewClient();
        _networkManager.CheckForIncomingMessage(_clients);
        CheckInstance();
        SendToClients();
    }
}

bool LobbyManager::CreateInstance(std::string &roomName) {
    if (_instances.find(roomName) == _instances.end()) {
        auto lobby = std::make_shared<LobbyInstance>(_eventManager, roomName);
        _instances[roomName] = lobby;
        return true;
    }
    return false;
}

bool LobbyManager::JoinInstance(std::string &roomName, std::shared_ptr<PlayerRef> &ref) {
    if (_instances.find(roomName) != _instances.end()) {
        return _instances[roomName]->AddPlayerToInstance(ref->GetId(), _clients[ref->GetId()], ref);
    }
    return false;
}

void LobbyManager::LeftInstance(std::string &roomName, uint8_t id) {
    if (_instances.find(roomName) != _instances.end()) {
        _instances[roomName]->PlayerLeft(id);
    }
}

void LobbyManager::CheckInstance() {
    for (auto const &instance : _instances) {
        if (!instance.second->IsThereAnyone()) {
            _instances.erase(instance.first);
            break;
        }
        if (instance.second->IsReady()) {
            //TODO: Transform LobbyInstance into GameInstance and remove LobbyInstance and close clients TCP connections
        }
    }
}

void LobbyManager::SendToClients() {
    if (_toSend.size() != 0) {
        for (auto it = _toSend.begin(); it != _toSend.end();) {
            if (_networkManager.SendOverTCP(it->second, it->first, 100)) {
                it = _toSend.erase(it);
            } else {
                ++it;
            }
        }
    }
}