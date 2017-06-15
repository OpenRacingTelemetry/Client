#pragma once

#include "header.h"
#include <cstdint>

#pragma pack(push,1)
struct message_inforequest
{
    header header;
    uint32_t target_id;
    uint8_t reserved[54];
};
#pragma pack(pop)

static_assert(sizeof(message_inforequest)==64,"size is not correct");
