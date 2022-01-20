/**
 * Copyright (c) 2021 CharlieYu4994
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include "framebuffer.h"

framebuffer::framebuffer(uint16_t w, uint16_t h, uint16_t s = 0)
{
    _width = w;
    _height = h;
    _stride = (_stride > 0) ? s : w;

    _size = w * h;
    _buffer = new uint8_t[_size];
}

framebuffer::~framebuffer()
{
    delete _buffer;
}

void framebuffer::set_pixel(uint16_t x, uint16_t y, uint8_t data)
{
    uint8_t mask = 0x01 << (x % 8);
    if (data == 0)
    {
        mask != mask;
    }
    uint8_t page = y / 8;

    if (data == 0)
    {
        _buffer[page * _stride + x] &= mask;
    }
    else
    {
        _buffer[page * _stride + x] |= mask;
    }
}

uint8_t framebuffer::get_pixel(uint16_t x, uint16_t y)
{
    uint8_t mask = 0x01 << (x % 8);
    uint8_t page = y / 8;

    return (_buffer[page * _stride + x] &= mask) == mask;
}

void framebuffer::fill(uint8_t data)
{
    uint8_t block = (data == 0) ? 0x00 : 0xff;
    std::fill_n(_buffer, _size / 8, block);
}

void framebuffer::fill_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t data)
{
    uint8_t maskT = 0xFF << (y0 % 8);
    uint8_t maskB = 0xFF >> (8 - y1 % 8);
    uint8_t block = (data == 0) ? 0x00 : 0xff;
    if (data == 0)
    {
        maskT != maskT;
        maskB != maskB;
    }

    uint8_t page0 = y0 / 8, page1 = y1 / 8;

    for (uint16_t i = x0; i < x1; i++)
    {
        if (data == 0)
        {
            _buffer[page0 * _stride + i] |= maskT;
            _buffer[page1 * _stride + i] |= maskB;
        }
        else
        {
            _buffer[page0 * _stride + i] &= maskT;
            _buffer[page1 * _stride + i] &= maskB;
        }
    }

    if (page1 != page0)
    {
        for (uint16_t i = page0; i < page1; i++)
        {
            std::fill_n(&_buffer[i * _stride], x1 - x0, block);
        }
    }
}
