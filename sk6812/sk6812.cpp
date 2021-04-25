#include "sk6812.h"
#include "driver/rmt.h"

sk6812::sk6812()
{
  _skconfig.rmt_mode = RMT_MODE_TX;
  _skconfig.channel = RMT_CHANNEL_7;
  _skconfig.mem_block_num = 1;
  _skconfig.tx_config.loop_en = 0;
  _skconfig.tx_config.carrier_en = 0;
  _skconfig.tx_config.idle_output_en = 1;
  _skconfig.tx_config.idle_level = RMT_IDLE_LEVEL_LOW;
  _skconfig.clk_div = 4;
}

sk6812::~sk6812()
{
  free(_buffer);
  rmt_driver_uninstall(_skconfig.channel);
}

/**
 * @brief Start the SK6821 Matrix
 * 
 * @param pin the GPIO id
 * @param num the led numbers
 * 
 * @return status
 *     - ESP_ERR_INVALID_STATE Driver is already installed, call rmt_driver_uninstall first.
 *     - ESP_ERR_NO_MEM Memory allocation failure
 *     - ESP_ERR_INVALID_ARG Parameter error
 *     - ESP_OK Success
 */
esp_err_t sk6812::begin(int pin, int num)
{

  _bitnum = num * 24;
  _lednum = num;

  esp_err_t status;

  _buffer = (rmt_item32_t *)calloc(_bitnum, sizeof(rmt_item32_t));

  _skconfig.gpio_num = (gpio_num_t)pin;
  rmt_config(&_skconfig);
  status = rmt_driver_install(_skconfig.channel, 0, 0);

  return (status);
}

/**
 * @brief End the SK6821 Matrix
 * 
 * @return status
 *     - ESP_ERR_INVALID_STATE Driver is already installed, call rmt_driver_uninstall first.
 *     - ESP_ERR_NO_MEM Memory allocation failure
 *     - ESP_ERR_INVALID_ARG Parameter error
 *     - ESP_OK Success
 */
esp_err_t sk6812::end()
{
  esp_err_t status;
  free(_buffer);
  status = rmt_driver_uninstall(_skconfig.channel);
  return (status);
}

/**
 * @brief Pack the RGB value
 * 
 * @param r red
 * @param g green
 * @param b blue
 * 
 * @return grb888 formated data
 */
uint32_t sk6812::packcolor(uint8_t r, uint8_t g, uint8_t b)
{
  uint32_t data;
  data = (uint32_t)g << 16 | (uint32_t)r << 8 | (uint32_t)b;
  return (data);
}

/**
 * @brief Set the led with r,g,b value
 * 
 * @param led the id of the led
 * @param r red
 * @param g green
 * @param b blue
 */
void sk6812::setLED(int led, uint8_t r, uint8_t g, uint8_t b)
{
  uint32_t data;

  data = packcolor(r, g, b);

  setLED(led, data);
  return;
}

/**
 * @brief Set the led with rgb888 data
 */
void sk6812::setLED(int led, uint32_t rgb888)
{
  int i, bit;
  uint8_t r, g, b;
  uint32_t data;

  r = (rgb888 >> 16) & 0xff;
  g = (rgb888 >> 8) & 0xff;
  b = rgb888 & 0xff;

  data = packcolor(r, g, b);

  if (led < 0 || led >= _lednum)
    return;

  for (i = led * 24, bit = 0; bit < 24; bit++)
  {
    if (data & (1 << (23 - bit)))
    {
      _buffer[i].level0 = 1;
      _buffer[i].duration0 = 12;
      _buffer[i].level1 = 0;
      _buffer[i].duration1 = 12;
    }
    else
    {
      _buffer[i].level0 = 1;
      _buffer[i].duration0 = 9;
      _buffer[i].level1 = 0;
      _buffer[i].duration1 = 18;
    }
    ++i;
  }
  return;
}

/**
 * @brief Show the buffer
 */
esp_err_t sk6812::show()
{
  esp_err_t status;
  status = rmt_write_items(_skconfig.channel, _buffer, _bitnum, 1);
  return status;
}

/**
 * @brief Clear the buffer
 */
void sk6812::clear()
{
  for (int i = 0; i < _lednum; ++i)
  {
    setLED(i, 0, 0, 0);
  }
}
