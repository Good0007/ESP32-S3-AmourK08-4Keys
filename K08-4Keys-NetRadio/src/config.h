
#define AMOUR_K08_VERSION 2

#define PIN_LED 48
#define PIN_RED_LED 47

//判断 Version =1 

// 1.0版本
#if AMOUR_K08_VERSION == 1

#define DISPLAY_BACKLIGHT_PIN 15
#define DISPLAY_MOSI_PIN      18
#define DISPLAY_CLK_PIN       8
#define DISPLAY_DC_PIN        16
#define DISPLAY_RST_PIN       17
#define DISPLAY_CS_PIN        -1

#define PIN_I2S_DOUT 5
#define PIN_I2S_BCLK 6
#define PIN_I2S_LRC 7

#define PIN_KEY_ADD 9
#define PIN_KEY_MINUS 21
#define PIN_KEY_MODE 14

#define PIN_I2C_SDA 1
#define PIN_I2C_SCL 2

#else
// 1.1版本
#define DISPLAY_BACKLIGHT_PIN 13
#define DISPLAY_MOSI_PIN 10
#define DISPLAY_CLK_PIN 9
#define DISPLAY_DC_PIN 8
#define DISPLAY_CS_PIN 14
#define DISPLAY_RST_PIN 18

#define PIN_I2S_DOUT 7
#define PIN_I2S_BCLK 15
#define PIN_I2S_LRC 16

#define PIN_KEY_ADD 40
#define PIN_KEY_MINUS 39
#define PIN_KEY_MODE 0

#define PIN_I2C_SDA 1
#define PIN_I2C_SCL 2

#endif
