#pragma once

#include "header.h"
#include <cstdint>

#pragma pack(push,1)
struct message_reconfigure
{
    header header;
    uint32_t target_id;
    uint32_t frequency;
    uint16_t channel_id;
    uint16_t txpower;
    uint8_t reserved[46];
};
#pragma pack(pop)

static_assert(sizeof(message_reconfigure)==64,"size is not correct");
