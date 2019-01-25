#pragma once

#include "entity.h"
#include "util.h"

struct tile_t {
    // for SDL rendering system
    u32_t color;

    // contains information about the entity 
    // on this tile (if there is one)
    entity_t entity;

};
