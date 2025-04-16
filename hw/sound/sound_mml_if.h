#ifndef MGC_SOUND_MML_IF_H
#define MGC_SOUND_MML_IF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mgc/mgc.h"

typedef struct mgc_mml_record {
    uint16_t id;
    const char * mml;
} mgc_mml_record_t;

typedef struct mgc_sound_mml_if {
    int  (*init)(void);
    int  (*deinit)(void);
    int  (*play_BGM)(uint16_t id);
    int  (*play_SE)(uint16_t id);
    void (*stop_BGM)(void);
    void (*stop_SE)(void);
    bool (*is_BGM_done)(void);
    bool (*is_SE_done)(void);
    void (*set_BGM_table)(const mgc_mml_record_t *record, size_t count);
    void (*set_SE_table)(const mgc_mml_record_t *record, size_t count);
} mgc_sound_mml_if_t;

#ifdef __cplusplus
}/* extern "C" */
#endif

#endif/*MGC_SOUND_MML_IF_H*/
