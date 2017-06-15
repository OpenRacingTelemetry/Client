#pragma once

#include <cstdint>

#pragma pack(push,1)
struct header
{
    uint8_t protocol_version;
    uint32_t id;
    uint8_t package_type;
};
#pragma pack(pop)

static_assert(sizeof(header)==6,"Size is incorrect");
