#ifndef MGC_GAMEPAD_IF_H
#define MGC_GAMEPAD_IF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mgc/mgc.h"

typedef struct mgc_gamepad_if {
    int (*init)(void);
    int (*deinit)(void);
    bool (*get_key_state)(uint16_t key);
    bool (*is_key_state_changed)(uint16_t key);
    bool (*is_key_on_edge)(uint16_t key);
    bool (*is_key_off_edge)(uint16_t key);
    void (*proc)(void);
    size_t (*get_key_count)(void);
} mgc_gamepad_if_t;

#ifdef __cplusplus
}/* extern "C" */
#endif

#endif/*MGC_GAMEPAD_IF_H*/
