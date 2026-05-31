//
// Created by Renan Costa Sales on 31/05/26.
//

#pragma once

#include <cstdint>


struct Block
{
    enum
    {
        air = 0,
        dirt,

        BLOCKS_COUNT,
    };

    std::uint16_t type = 0;
};