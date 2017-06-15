#pragma once

#include "header.h"
#include <cstdint>

#pragma pack(push,1)
struct message_event
{
    header header;
    uint32_t event_id;
    uint32_t time;
    uint16_t msec;
    uint8_t reserved[48];
};
#pragma pack(pop)

static_assert(sizeof(message_event)==64,"size is not correct");
