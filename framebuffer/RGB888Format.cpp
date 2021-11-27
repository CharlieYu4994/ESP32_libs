/**
 * Copyright (c) 2021 CharlieYu4994
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include "RGB888Format.h"

RGB888Format::RGB888Format(uint16_t width, uint16_t height, uint16_t stride)
{
    _width = width;
    _height = height;
    _stride = (_stride > 0) ? stride : width;

    _pixels = width * height;
    _buffer = new pixel[width * height];
}

RGB888Format::~RGB888Format()
{
    delete _buffer;
}

void RGB888Format::set_pixel(uint16_t x, uint16_t y, uint32_t data)
{
    uint16_t index = y * _stride + x;

    _buffer[index].r = (data >> 16) & 0xff;
    _buffer[index].g = (data >> 8) & 0xff;
    _buffer[index].b = data & 0xff;
}

pixel RGB888Format::get_pixel(uint16_t x, uint16_t y)
{
    return _buffer[y * _stride + x];
}

void RGB888Format::fill(uint32_t data)
{
    pixel block{
        .r = (data >> 16) & 0xff,
        .g = (data >> 8) & 0xff,
        .b = data & 0xff};

    std::fill_n(_buffer, _pixels, block);
}

void RGB888Format::fill_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t data)
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