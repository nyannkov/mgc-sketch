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

#ifdef MGC_SSD1331_USE_FRAME_BUFFER
static uint16_t frame_buffer[Adafruit_SSD1331::TFTWIDTH * Adafruit_SSD1331::TFTHEIGHT];
#endif

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

#ifdef MGC_SSD1331_USE_FRAME_BUFFER
    uint16_t* src = (uint16_t*)buf;
    const int16_t width = x1 - x0 + 1;
    const int16_t buffer_width = Adafruit_SSD1331::TFTWIDTH;

    int16_t dst_row_start = y0 * buffer_width;
    int16_t src_row_start = 0;

    for (int16_t Y = y0; Y <= y1; Y++) {
        int16_t dst_index = dst_row_start + x0;
        int16_t src_index = src_row_start;

        for (int16_t X = x0; X <= x1; X++) {
            frame_buffer[dst_index++] = src[src_index++];
        }

        dst_row_start += buffer_width;
        src_row_start += width;
    }
#else
    display_SSD1331.drawBitmap(x0, y0, (uint16_t*)buf, x1-x0+1, y1-y0+1);
#endif

    return 0;
}

#ifdef MGC_SSD1331_USE_FRAME_BUFFER
void display_SSD1331_transfer_frame(void) {
    display_SSD1331.drawBitmap(0, 0, frame_buffer, 96, 64);
}
#endif

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

