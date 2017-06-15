#pragma once

#include "header.h"
#include <cstdint>

#pragma pack(push,1)
struct message_eventacquired
{
    header header;
    uint32_t target_id;
    uint32_t event_id;
    uint8_t reserved[50];
};
#pragma pack(pop)

static_assert(sizeof(message_eventacquired)==64,"size is not correct");
