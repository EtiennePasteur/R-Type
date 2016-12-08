//
// Created by pasteu_e on 29/11/16.
//

#ifndef R_TYPE_RTYPENETWORKPAYLOAD_H
#define R_TYPE_RTYPENETWORKPAYLOAD_H

#include <iostream>

class RTypeNetworkPayload {
public:
    std::string Ip = "";
    char *Payload;
    int Length;

    RTypeNetworkPayload(char *payload, int length) : Payload(payload), Length(length) {}
    RTypeNetworkPayload(const RTypeNetworkPayload& payload) : Payload(payload.Payload), Length(payload.Length) {}
    const RTypeNetworkPayload& operator=(const RTypeNetworkPayload& payload) { return *this; }
};

#endif //R_TYPE_RTYPENETWORKPAYLOAD_H
