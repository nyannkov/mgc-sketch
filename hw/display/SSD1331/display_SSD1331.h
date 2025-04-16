#ifndef MGC_DISPLAY_SSD1331_H
#define MGC_DISPLAY_SSD1331_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mgc/render/display.h"

extern const mgc_display_if_t display_SSD1331_handler;

#ifdef MGC_SSD1331_USE_FRAME_BUFFER
extern void display_SSD1331_transfer_frame(void);
#endif

#ifdef __cplusplus
}/* extern "C" */
#endif

#endif/*MGC_DISPLAY_SSD1331_H*/
