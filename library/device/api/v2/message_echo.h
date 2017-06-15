#pragma once

#include "header.h"
#include <cstdint>

#pragma pack(push,1)
struct message_echo
{
    header header;
    uint32_t unixtime;
    float position_lat;
    float position_lon;
    uint16_t txpower;
    uint8_t reserved[44];
};
#pragma pack(pop)

static_assert(sizeof(message_echo)==64,"size is not correct");
