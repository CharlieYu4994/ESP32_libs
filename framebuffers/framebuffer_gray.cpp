/**
 * Copyright (c) 2022 CharlieYu4994
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include "framebuffer_gray.h"

framebuffer_gray16::framebuffer_gray16(uint16_t w, uint16_t h, uint16_t s) : framebuffer(w, h, s)
{
    _size = s / 2 + s % 2;
    _buffer = new uint8_t[_size];
}

void framebuffer_gray16::set_pixel(uint16_t x, uint16_t y, uint8_t data)
{
    uint16_t raw_index = y * _stride + x;
    uint16_t index = raw_index / 2;

    if (raw_index % 2)
    {
        data <<= 4;
        _buffer[index] &= 0x0F;
    }
    else
    {
        data &= 0x0F;
        _buffer[index] &= 0xF0;
    }

    _buffer[index] |= data;
}

uint8_t framebuffer_gray16::get_pixel(uint16_t x, uint16_t y)
{
    uint16_t raw_index = y * _stride + x;
    uint16_t index = raw_index / 2;

    if (raw_index % 2)
    {
        return _buffer[index] >> 4;
    }
    else
    {
        return _buffer[index] &= 0x0F;
    }
}

void framebuffer_gray16::fill(uint8_t data)
{
    data = (data << 4) & (data & 0x0F);
    std::fill_n(_buffer, _size, data);
}

void framebuffer_gray16::fill_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t data)
{
    uint8_t block = (data << 4) & (data & 0x0F);
}

framebuffer_gray256::framebuffer_gray256(uint16_t w, uint16_t h, uint16_t s) : framebuffer(w, h, s) {}