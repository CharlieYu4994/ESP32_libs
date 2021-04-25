#ifndef SK6812_H
#define SK6812_H

#include "driver/rmt.h"

class sk6812
{
private:
  int _lednum;
  int _bitnum;
  rmt_item32_t *_buffer = NULL;
  rmt_config_t _skconfig;
  uint32_t packcolor(uint8_t r, uint8_t g, uint8_t b);

public:
  sk6812();
  ~sk6812();
  esp_err_t begin(int pin, int num);
  esp_err_t end();
  esp_err_t show();
  void setLED(int led, uint32_t rgb888);
  void setLED(int led, uint8_t r, uint8_t g, uint8_t b);
  void clear(void);
};

#endif
