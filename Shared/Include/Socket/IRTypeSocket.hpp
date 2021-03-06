//
// Created by pasteu_e on 28/11/16.
//

#ifndef R_TYPE_IRTYPESOCKET_HPP
#define R_TYPE_IRTYPESOCKET_HPP

#include <iostream>
#include <memory>
#include <vector>
#include "RTypeNetworkPayload.h"
#include "Enum/RTypeSocketType.h"

class IRTypeSocket {
public:
    virtual ~IRTypeSocket() {}

    virtual void Bind() = 0;

    virtual bool Connect() = 0;

    virtual std::shared_ptr<IRTypeSocket> Accept() = 0;

    virtual bool Receive(std::shared_ptr<RTypeNetworkPayload>) = 0;

    virtual bool Send(std::shared_ptr<RTypeNetworkPayload> payload) = 0;

    virtual void *GetNativeSocket() = 0;

    virtual bool PoolEventOnSocket(SocketEvent, int) = 0;
};

#endif //R_TYPE_IRTYPESOCKET_HPP
