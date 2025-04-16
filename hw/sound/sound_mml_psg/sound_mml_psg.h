#ifndef MGC_SOUND_MML_PSG_H
#define MGC_SOUND_MML_PSG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sound_mml_if.h"

extern const mgc_sound_mml_if_t sound_mml_psg;

extern void sound_mml_psg__finish_primary_loop(bool force);
extern void sound_mml_psg__set_BGM_callback(void (*cb)(uint8_t ch, int32_t param));
extern void sound_mml_psg__set_SE_callback(void (*cb)(uint8_t ch, int32_t param));

#ifdef __cplusplus
}/* extern "C" */
#endif

#endif/*MGC_SOUND_MML_PSG_H*/
