/**
 * Copyright (C) 2021 CharlieYu
 * 
 * This file is part of ESP32_libs.
 * 
 * ESP32_libs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ESP32_libs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with ESP32_libs.  If not, see <http://www.gnu.org/licenses/>.
 */

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