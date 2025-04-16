#ifndef MGC_MML_LIST_H
#define MGC_MML_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "game_io/hw/sound/sound_mml_if.h"

#define MML_SE_0            (0)
#define MML_SE_1            (1)
#define MML_SE_LIST_COUNT   (2)

#define MML_BGM_0           (0)
#define MML_BGM_1           (1)
#define MML_BGM_2           (2)
#define MML_BGM_3           (3)
#define MML_BGM_LIST_COUNT  (4)

extern mgc_mml_record_t mml_se_list[MML_SE_LIST_COUNT];
extern mgc_mml_record_t mml_bgm_list[MML_BGM_LIST_COUNT];

#ifdef __cplusplus
}/*extern "C"*/
#endif

#endif/*MGC_MML_LIST_H*/
