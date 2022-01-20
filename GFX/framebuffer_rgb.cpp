/**
 * Copyright (c) 2021 CharlieYu4994
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include "framebuffer_rgb.h"

framebuffer_rgb::framebuffer_rgb(uint16_t w, uint16_t h, uint16_t s): framebuffer(w, h, s)
{
    _buffer = new pixel[_size];
}

framebuffer_rgb::~framebuffer_rgb()
{
    delete _buffer;
}

void framebuffer_rgb::set_pixel(uint16_t x, uint16_t y, uint32_t data)
{
    uint16_t index = y * _stride + x;

    _buffer[index].r = (data >> 16) & 0xff;
    _buffer[index].g = (data >> 8) & 0xff;
    _buffer[index].b = data & 0xff;
}

pixel framebuffer_rgb::get_pixel(uint16_t x, uint16_t y)
{
    return _buffer[y * _stride + x];
}

void framebuffer_rgb::fill(uint32_t data)
{
    pixel block{
        .r = (data >> 16) & 0xff,
        .g = (data >> 8) & 0xff,
        .b = data & 0xff};

    std::fill_n(_buffer, _size, block);
}

void framebuffer_rgb::fill_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t data)
{
    pixel block{
        .r = (data >> 16) & 0xff,
        .g = (data >> 8) & 0xff,
        .b = data & 0xff};

    for (uint16_t i = y0; i < y1; i++)
    {
        std::fill_n(&_buffer[y0 * _stride + x0], block, x1 - x0);
    }
}