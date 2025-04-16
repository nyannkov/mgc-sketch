#include "mgc/mgc.h"
#include <FspTimer.h>
#include <Psgino.h>
#include "emu2149/emu2149.h"
#include "sound_mml_psg.h"

constexpr uint32_t PSG_EMU_CLOCK = 2000000; // 2 MHz
constexpr uint32_t PSG_RATE = 30000;        // 30 kHz
constexpr uint16_t MML_PROC_RATE = 400;     // 400 Hz
constexpr unsigned long EXEC_CYCLE_MML = (1000*1000uL)/MML_PROC_RATE; // unit: usec.

static const mgc_mml_record_t *mml_BGM_records;
static size_t mml_BGM_records_count;

static const mgc_mml_record_t *mml_SE_records;
static size_t mml_SE_records_count;

static FspTimer fsp_timer_psg;
static FspTimer fsp_timer_mml;
static PSG *psg;            // PSG emulator
static PsginoZ psgino;       // MML decoder for PSGs

static bool initialized = false;

static int sound_mml_psg__init(void) {

    if ( initialized ) {
        return 1;
    }

    mml_BGM_records = nullptr;
    mml_BGM_records_count = 0;

    mml_SE_records = nullptr;
    mml_SE_records_count = 0;

    psg = PSG_new(PSG_EMU_CLOCK, PSG_RATE);
    PSG_reset(psg);

    psgino.Initialize([](uint8_t addr, uint8_t data) -> void {
            __disable_irq();
            PSG_writeReg(psg, addr, data);
            __enable_irq();
        },
        PSG_EMU_CLOCK,
        MML_PROC_RATE
    );

    fsp_timer_psg.begin(TIMER_MODE_PERIODIC, GPT_TIMER, 0, static_cast<float>(PSG_RATE), 50.0F);
    fsp_timer_psg.setup_overflow_irq(0, []() -> void {
            if ( psg ) {
                int16_t output;
                output = PSG_calc(psg)>>4;
                analogWrite(DAC, output);
            }
            R_BSP_IrqStatusClear(fsp_timer_psg.get_cfg()->cycle_end_irq);
        }
    );
    fsp_timer_psg.open();
    fsp_timer_psg.start();
    R_BSP_IrqCfg(fsp_timer_psg.get_cfg()->cycle_end_irq, 0, nullptr);
    fsp_timer_psg.enable_overflow_irq();

    fsp_timer_mml.begin(TIMER_MODE_PERIODIC, GPT_TIMER, 3, static_cast<float>(MML_PROC_RATE), 50.0F);
    fsp_timer_mml.setup_overflow_irq(12, []() -> void {
        psgino.Proc();
        R_BSP_IrqStatusClear(fsp_timer_mml.get_cfg()->cycle_end_irq);
    });
    fsp_timer_mml.open();
    fsp_timer_mml.start();
    R_BSP_IrqCfg(fsp_timer_mml.get_cfg()->cycle_end_irq, 12, nullptr);
    fsp_timer_mml.enable_overflow_irq();

    analogWriteResolution(12);

    initialized = true;

    return 0;
}

static int sound_mml_psg__deinit(void) {

    if (!initialized) {
        return 1;
    }

    psgino.Stop();
    psgino.StopSe();

    fsp_timer_mml.disable_overflow_irq();
    fsp_timer_mml.stop();
    fsp_timer_mml.close();

    fsp_timer_psg.disable_overflow_irq();
    fsp_timer_psg.stop();
    fsp_timer_psg.close();

    if ( psg ) {
        PSG_delete(psg);
        psg = NULL;
    }

    initialized = false;

    return 0;
}

static int sound_mml_psg__play_BGM(uint16_t id) {
    if ( ( mml_BGM_records == nullptr ) ||
         ( mml_BGM_records_count == 0 )
    ) {
        return -1;
    }

    for ( size_t i = 0; i < mml_BGM_records_count; i++ ) {
        if ( mml_BGM_records[i].id == id ) {
            psgino.SetMML(mml_BGM_records[i].mml);
            psgino.Play();
            return 0;
        }
    }
    return -2;
}

static int sound_mml_psg__play_SE(uint16_t id) {
    if ( ( mml_SE_records == nullptr ) ||
         ( mml_SE_records_count == 0 )
    ) {
        return -1;
    }

    for ( size_t i = 0; i < mml_SE_records_count; i++ ) {
        if ( mml_SE_records[i].id == id ) {
            psgino.SetSeMML(mml_SE_records[i].mml);
            psgino.PlaySe();
            return 0;
        }
    }
    return -2;
}

static void sound_mml_psg__stop_BGM(void) {
    psgino.Stop();
}

static void sound_mml_psg__stop_SE(void) {
    psgino.StopSe();
}

static bool sound_mml_psg__is_BGM_done(void) {
    return psgino.GetStatus() == Psgino::PlayEnd;
}

static bool sound_mml_psg__is_SE_done(void) {
    return psgino.GetSeStatus() == Psgino::PlayEnd;
}

static void sound_mml_psg__set_BGM_table(const mgc_mml_record_t *record, size_t count) {
    mml_BGM_records = record;
    mml_BGM_records_count = count;
}

static void sound_mml_psg__set_SE_table(const mgc_mml_record_t *record, size_t count) {
    mml_SE_records = record;
    mml_SE_records_count = count;
}

//TODO reset
const mgc_sound_mml_if_t sound_mml_psg = {
    sound_mml_psg__init,
    sound_mml_psg__deinit,
    sound_mml_psg__play_BGM,
    sound_mml_psg__play_SE,
    sound_mml_psg__stop_BGM,
    sound_mml_psg__stop_SE,
    sound_mml_psg__is_BGM_done,
    sound_mml_psg__is_SE_done,
    sound_mml_psg__set_BGM_table,
    sound_mml_psg__set_SE_table,
};

void sound_mml_psg__finish_primary_loop(bool force) {
    if ( initialized ) {
        psgino.FinishPrimaryLoop(force);
    }
}

void sound_mml_psg__set_BGM_callback(void (*cb)(uint8_t ch, int32_t param)) {
    if ( initialized ) {
        psgino.SetUserCallback(cb);
    }
}

void sound_mml_psg__set_SE_callback(void (*cb)(uint8_t ch, int32_t param)) {
    if ( initialized ) {
        psgino.SetSeUserCallback(cb);
    }
}

