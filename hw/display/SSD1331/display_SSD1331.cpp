#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include "display_SSD1331.h"

#ifndef DISPLAY_SSD1331_PIN_CS
#define DISPLAY_SSD1331_PIN_CS  D1
#endif/*DISPLAY_SSD1331_PIN_CS*/

#ifndef DISPLAY_SSD1331_PIN_DC
#define DISPLAY_SSD1331_PIN_DC  D7
#endif/*DISPLAY_SSD1331_PIN_DC*/

#ifndef DISPLAY_SSD1331_PIN_RST
#define DISPLAY_SSD1331_PIN_RST D2
#endif/*DISPLAY_SSD1331_PIN_RST*/

class Adafruit_SSD1331_ex : public Adafruit_SSD1331 {
public:
    Adafruit_SSD1331_ex(SPIClass *spi, int8_t cs, int8_t dc, int8_t rst = -1)
    : Adafruit_SSD1331(spi, cs, dc, rst)
    {
    }

    void drawBitmap(int16_t x, int16_t y, uint16_t *pcolors, int16_t w, int16_t h) {
        startWrite();
        setAddrWindow(x, y, w, h);
        hwspi._spi->transfer(pcolors, w*h*2);
        endWrite();
    }
};

static Adafruit_SSD1331_ex display_SSD1331 = Adafruit_SSD1331_ex(
        &SPI,
        DISPLAY_SSD1331_PIN_CS,
        DISPLAY_SSD1331_PIN_DC,
        DISPLAY_SSD1331_PIN_RST
);

int display_SSD1331_init(void) {
#ifdef MGC_DISPLAY_SSD1331_CLOCK_HZ
    display_SSD1331.begin(MGC_DISPLAY_SSD1331_CLOCK_HZ);
#else
    display_SSD1331.begin();
#endif

    display_SSD1331.fillScreen(0x0000);
    return 0;
}

int display_SSD1331_draw_rect(uint8_t *buf, size_t len, int16_t x0, int16_t y0, int16_t x1, int16_t y1) {

    if (buf == NULL) {
        return -1;
    }

    if ( (x0 < 0) ||
         (y0 < 0) ||
         (x1 >= Adafruit_SSD1331::TFTWIDTH) ||
         (y1 >= Adafruit_SSD1331::TFTHEIGHT)||
         (x0 > x1) ||
         (y0 > y1)
    ) {
        return -2;
    }

    size_t required_size = (x1 - x0 + 1) * (y1 - y0 + 1);
    if (len < required_size) {
        return -3;
    }

    display_SSD1331.drawBitmap(x0, y0, (uint16_t*)buf, x1-x0+1, y1-y0+1);

    return 0;
}

int display_SSD1331_deinit(void) {
    return 0;
}

void display_SSD1331_reset(void) {
}

uint16_t display_SSD1331_get_width(void) {
    return display_SSD1331.TFTWIDTH;
}

uint16_t display_SSD1331_get_height(void) {
    return display_SSD1331.TFTHEIGHT;
}

void display_SSD1331_clear_screen(void) {
    display_SSD1331.fillScreen(0x0000);
}

const mgc_display_if_t display_SSD1331_handler = {
    display_SSD1331_init,
    display_SSD1331_deinit,
    display_SSD1331_reset,
    display_SSD1331_draw_rect,
    display_SSD1331_get_width,
    display_SSD1331_get_height,
    display_SSD1331_clear_screen,
};

