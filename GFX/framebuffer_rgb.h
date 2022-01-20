/**
 * Copyright (c) 2021 CharlieYu4994
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include "framebuffer.h"
#include <stdint.h>
#include <algorithm>

struct pixel
{
    uint8_t r, g, b;
};

class framebuffer_rgb: public framebuffer
{
protected:
    pixel *_buffer = NULL;
public:
    void set_pixel(uint16_t x, uint16_t y, uint32_t data);
    pixel get_pixel(uint16_t x, uint16_t y);
    void fill(uint32_t data);
    void fill_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color);

    framebuffer_rgb(uint16_t width, uint16_t height, uint16_t stride);
    ~framebuffer_rgb();
};
