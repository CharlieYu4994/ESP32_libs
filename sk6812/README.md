## 简介
一个简约的 sk6812/ws2812 驱动，基于 ESP-IDF 提供的 RMT

## 用法
``` C++
#include "sk6812.h"

sk6812 led (27, 1);

led.set(0, 0xFF000000);
led.set(0, 255, 0, 0);
led.show();
```
1. 引入库
2. 实例化 `sk6812` 类，并传入引脚和 LED 数量
3. 调用 `set` 方法对 LED 的颜色进行设置
    + set 方法有两个重载，可以接受分开的 RGB 值，也可以接受 RGB888 格式的值
4. 调用 `show` 方法显示结果