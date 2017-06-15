#pragma once

#include "header.h"
#include <cstdint>

#pragma pack(push,1)
typedef struct message_inforequest
{
    uint32_t target_id;
    uint8_t reserved[54];
};
#pragma pack(pop)

static_assert(sizeof(message_echo)==64,"size is not correct");
