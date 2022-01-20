/**
 * Copyright (c) 2021 CharlieYu4994
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#pragma once
#include "framebuffer.h"

#define RGB565_MASK_R 0xF800
#define RGB565_MASK_G 0x07E0
#define RGB565_MASK_B 0x001F

struct pixel
{
    uint8_t r, g, b;
};

class framebuffer_rgb888: public framebuffer
{
protected:
    pixel *_buffer = NULL;
public:
    void set_pixel(uint16_t x, uint16_t y, uint32_t data);
    pixel get_pixel(uint16_t x, uint16_t y);
    void fill(uint32_t data);
    void fill_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color);

    framebuffer_rgb888(uint16_t width, uint16_t height, uint16_t stride);
    ~framebuffer_rgb888();
};

class framebuffer_rgb565: public framebuffer
{
protected:
    uint16_t *_buffer = NULL;
public:
    void set_pixel(uint16_t x, uint16_t y, uint16_t data);
    pixel get_pixel(uint16_t x, uint16_t y);
    void fill(uint16_t data);
    void fill_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t data);

    framebuffer_rgb565(uint16_t width, uint16_t height, uint16_t stride);
    ~framebuffer_rgb565();
};
