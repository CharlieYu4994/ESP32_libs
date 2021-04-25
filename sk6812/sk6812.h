#ifndef SK6812_H
#define SK6812_H

#include "driver/rmt.h"

class sk6812
{
private:
  int _lednum;
  int _bitnum;
  rmt_item32_t *_buffer = NULL;
  rmt_config_t _config;
  uint32_t packcolor(uint8_t r, uint8_t g, uint8_t b);

public:
  sk6812(int pin, int num);
  ~sk6812();

  void show();
  void set(int led, uint32_t rgb888);
  void set(int led, uint8_t r, uint8_t g, uint8_t b);
};

#endif