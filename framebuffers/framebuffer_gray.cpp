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
    uint16_t index = y * _stride + x;

    if (index % 2)
    {
        data <<= 4;
        _buffer[index / 2] &= 0x0F;
    }
    else
    {
        data &= 0x0F;
        _buffer[index / 2] &= 0xF0;
    }

    _buffer[index / 2] |= data;
}

uint8_t framebuffer_gray16::get_pixel(uint16_t x, uint16_t y)
{
    uint16_t index = y * _stride + x;

    if (index % 2)
    {
        return _buffer[index / 2] >> 4;
    }
    else
    {
        return _buffer[index / 2] &= 0x0F;
    }
}

void framebuffer_gray16::fill(uint8_t data)
{
    data = (data << 4) & (data & 0x0F);
    std::fill_n(_buffer, _size, data);
}

void framebuffer_gray16::fill_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t data)
{
    uint8_t data_h = data << 4;
    uint8_t data_l = data & 0x0F;
    data = data_h & data_l;

    for (uint16_t i = y0; i < y1; i++)
    {
        uint16_t index = i * _stride + x0;
        std::fill_n(&_buffer[index / 2 + index % 2], (x1-x0) / 2, data);

        if (x0 % 2)
        {;
            _buffer[x0 / 2] &= 0xF0;
            _buffer[x0 / 2] &= data_h;
        }
        if (x1 % 2) {
            _buffer[x1 / 2] &= 0x0F;
            _buffer[x1 / 2] &= data_l;
        }
    }
}

framebuffer_gray256::framebuffer_gray256(uint16_t w, uint16_t h, uint16_t s) : framebuffer(w, h, s) {}