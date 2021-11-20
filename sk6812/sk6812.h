#pragma once

#include "driver/rmt.h"

#if SOC_RMT_CHANNELS_NUM > 4
    #define CH RMT_CHANNEL_7
#else
    #define CH RMT_CHANNEL_3
#endif

class sk6812
{
private:
    int _lednum;
    int _bitnum;
    rmt_item32_t *_buffer = NULL;
    rmt_config_t _config;
    uint32_t packcolor(uint8_t r, uint8_t g, uint8_t b);
    uint32_t repackcolor(uint32_t rgb888);
    void _set(int led, uint32_t rgb888);

public:
    sk6812(int pin, int num);
    ~sk6812();

    void show();
    void set(int led, uint32_t rgb888);
    void set(int led, uint8_t r, uint8_t g, uint8_t b);
};