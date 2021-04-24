#include "sk6812.h"
#include "driver/rmt.h"

class sk6812
{
private:
  int _lednum;
  int _bitnum;
  rmt_item32_t *_buffer = NULL;
  rmt_config_t _skconfig;

public:
  esp_err_t begin(int pin, int num);
  esp_err_t end();
  esp_err_t show();
  uint32_t packcolor(uint8_t r, uint8_t g, uint8_t b);
  void setLED(int led, uint32_t grb888);
  void setLED(int led, uint8_t r, uint8_t g, uint8_t b);
  void clear(void);
};

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

  _skconfig.rmt_mode = RMT_MODE_TX;
  _skconfig.channel = RMT_CHANNEL_7;
  _skconfig.gpio_num = (gpio_num_t)pin;
  _skconfig.mem_block_num = 1;
  _skconfig.tx_config.loop_en = 0;
  _skconfig.tx_config.carrier_en = 0;
  _skconfig.tx_config.idle_output_en = 1;
  _skconfig.tx_config.idle_level = RMT_IDLE_LEVEL_LOW;
  _skconfig.tx_config.carrier_level = RMT_CARRIER_LEVEL_HIGH;
  _skconfig.clk_div = 8;

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
  uint32_t grb888 = 0;

  grb888 |= (uint32_t)g << 16;
  grb888 |= (uint32_t)r << 8;
  grb888 |= (uint32_t)b;

  return (grb888);
}

/**
 * @brief Set the led with r,g,b value
 * 
 * @param led the id of the led
 * @param r red
 * @param g green
 * @param b blue
 * 
 * @return grb888 formated data
 */
void sk6812::setLED(int led, uint8_t r, uint8_t g, uint8_t b)
{
  uint32_t grb888;

  grb888 = packcolor(r, g, b);

  setLED(led, grb888);
  return;
}

/**
 * @brief Set the led with grb888 data
 * 
 * @param grb888 the grb888 formated data
 */
void sk6812::setLED(int led, uint32_t grb888)
{
  int i, bit;

  if (led < 0 || led >= _lednum)
    return;

  for (i = led * 24, bit = 0; bit < 24; bit++)
  {
    if (grb888 & (1 << (23 - bit)))
    {
      _buffer[i].level0 = 1;
      _buffer[i].duration0 = 6;
      _buffer[i].level1 = 0;
      _buffer[i].duration1 = 6;
    }
    else
    {
      _buffer[i].level0 = 1;
      _buffer[i].duration0 = 3;
      _buffer[i].level1 = 0;
      _buffer[i].duration1 = 9;
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
