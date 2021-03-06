//
// Created by pasteu_e on 02/12/16.
//

#ifndef R_TYPE_RTYPESOCKETTYPE_H
#define R_TYPE_RTYPESOCKETTYPE_H

enum SocketType {
        UDP = 0,
        TCP = 1
};

enum SocketIdentity {
    Server = 0,
    Client = 1
};

enum SocketEvent {
    SOCKET_CLOSED,
    DATA_INCOMING,
    SOMEONE_LISTENING
};

#endif //R_TYPE_RTYPESOCKETTYPE_H
