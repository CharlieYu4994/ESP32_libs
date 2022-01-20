/**
 * Copyright (c) 2022 CharlieYu4994
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#pragma once
#include "framebuffer.h"

class framebuffer_gray16 : public framebuffer
{
public:
    void set_pixel(uint16_t x, uint16_t y, uint8_t data);
    uint8_t get_pixel(uint16_t x, uint16_t y);
    void fill(uint8_t data);
    void fill_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t data);

    framebuffer_gray16(uint16_t width, uint16_t height, uint16_t stride);
    ~framebuffer_gray16();
};

class framebuffer_gray256 : public framebuffer
{
public:
    void set_pixel(uint16_t x, uint16_t y, uint8_t data);
    uint8_t get_pixel(uint16_t x, uint16_t y);
    void fill(uint8_t data);
    void fill_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t data);

    framebuffer_gray256(uint16_t width, uint16_t height, uint16_t stride);
    ~framebuffer_gray256();
};
