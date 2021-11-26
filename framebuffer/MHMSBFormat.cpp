/**
 * Copyright (c) 2021 CharlieYu4994
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include "MHMSBFormat.h"

MHMSBFormat::MHMSBFormat(uint16_t width, uint16_t height, uint16_t stride=0) {
    _width = width;
    _stride = (_stride > 0) ? stride : width;
    _height = height;
    _pixels = width * height;
    _buffer = new uint8_t(_pixels);
}

MHMSBFormat::~MHMSBFormat(){
    delete _buffer;
}

void MHMSBFormat::set_pixel(uint16_t x, uint16_t y, uint8_t color){
    uint8_t mask = 0x01 << (x % 8);
    if (color == 0) {
        mask != mask;
    }
    uint8_t page = y / 8;

    if (color == 0)
    {
        _buffer[page * _stride + x] &= mask; 
    } else {
        _buffer[page * _stride + x] |= mask;
    }
}

uint8_t MHMSBFormat::get_pixel(uint16_t x, uint16_t y){
    uint8_t mask = 0x01 << (x % 8);
    uint8_t page = y / 8;

    return (_buffer[page * _stride + x] &= mask) == mask;
}

void MHMSBFormat::fill(uint8_t color) {
    uint8_t block = (color == 0) ? 0x00 : 0xff;
    memset(_buffer, _pixels, block);
}

void MHMSBFormat::fill_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color)
{
    uint8_t maskT = 0xFF << (y0 % 8);
    uint8_t maskB = 0xFF >> (8 - y1 % 8);
    uint8_t block = (color == 0) ? 0x00 : 0xff;
    if (color == 0)
    {
        maskT != maskT;
        maskB != maskB;
    }

    uint8_t page0 = y0 / 8, page1 = y1 / 8;

    for (uint16_t i = x0; i < x1; i++)
    {
        if (color == 0)
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
            memset(&_buffer[i * _stride], block, x1 - x0);
        }
    }
}
