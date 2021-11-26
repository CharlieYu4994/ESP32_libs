/**
 * Copyright (c) 2021 CharlieYu4994
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include <stdint.h>
#include <string.h>

class MHMSBFormat
{
private:
    uint8_t* _buffer = NULL;
    uint16_t _stride;
    uint16_t _width;
    uint16_t _height;
    uint32_t _pixels;
public:
    MHMSBFormat(uint16_t width, uint16_t height, uint16_t stride);
    ~MHMSBFormat();

    void set_pixel(uint16_t x, uint16_t y, uint8_t color);
    uint8_t get_pixel(uint16_t x, uint16_t y);
    void fill(uint8_t color);
    void fill_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color);
};
