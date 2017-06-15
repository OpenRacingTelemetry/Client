#pragma once

#include "header.h"

#pragma pack(push,1)
struct message
{
    header header;
    uint8_t payload[58];
};
#pragma pack(pop)

static_assert(sizeof(message)==64,"Size is incorrect");
