#include <Arduino.h>
#include "mgc/mgc.h"
#include "gamepad_tiny.h"

#define NUM_OF_KEY_TABLE            (3)

#ifndef GAMEPAD_TINY_PIN_KEY0
#define GAMEPAD_TINY_PIN_KEY0       PIN_D6
#endif/*GAMEPAD_TINY_PIN_KEY0*/

#ifndef GAMEPAD_TINY_PIN_KEY1
#define GAMEPAD_TINY_PIN_KEY1       PIN_D5
#endif/*GAMEPAD_TINY_PIN_KEY1*/

#ifndef GAMEPAD_TINY_PIN_KEY2
#define GAMEPAD_TINY_PIN_KEY2       PIN_D4
#endif/*GAMEPAD_TINY_PIN_KEY2*/


struct key_table {
    const uint16_t key;
    bool key_stat;
    bool prev_key_stat;
    bool is_key_state_changed;
    uint8_t key_on_counter;
    uint8_t pin;
};

static struct key_table key_table[NUM_OF_KEY_TABLE] = {
    {0, false, false, false, 0, GAMEPAD_TINY_PIN_KEY0},
    {1, false, false, false, 0, GAMEPAD_TINY_PIN_KEY1},
    {2, false, false, false, 0, GAMEPAD_TINY_PIN_KEY2},
};

static struct key_table *get_key_table(uint16_t key) {
    for ( size_t i = 0; i < NUM_OF_KEY_TABLE; i++ ) {
        if ( key_table[i].key == key ) {
            return &key_table[i];
        }
    }
    return NULL;
}

static int gamepad_tiny__init(void) {

    for ( size_t i = 0; i < NUM_OF_KEY_TABLE; i++ ) {
        pinMode(key_table[i].pin, INPUT_PULLUP);
        key_table[i].key_stat = false;
        key_table[i].is_key_state_changed = false;
        key_table[i].key_on_counter = 0;
    }
    return 0;
}

static int gamepad_tiny__deinit(void) {
    return 0;
}

static bool gamepad_tiny__get_key_state(uint16_t key) {
    for ( size_t i = 0; i < NUM_OF_KEY_TABLE; i++ ) {
        if ( key_table[i].key == key ) {
            return key_table[i].key_stat;
        }
    }
    return false;
}

static bool gamepad_tiny__is_key_state_changed(uint16_t key) {
    for ( size_t i = 0; i < NUM_OF_KEY_TABLE; i++ ) {
        if ( key_table[i].key == key ) {
            return key_table[i].is_key_state_changed;
        }
    }
    return false;
}

static bool gamepad_tiny__is_key_on_edge(uint16_t key) {
    for ( size_t i = 0; i < NUM_OF_KEY_TABLE; i++ ) {
        if ( key_table[i].key == key ) {
            return (
                (key_table[i].key_stat == true) &&
                (key_table[i].is_key_state_changed == true)
            );
        }
    }
    return false;
}

static bool gamepad_tiny__is_key_off_edge(uint16_t key) {
    for ( size_t i = 0; i < NUM_OF_KEY_TABLE; i++ ) {
        if ( key_table[i].key == key ) {
            return (
                (key_table[i].key_stat == false) &&
                (key_table[i].is_key_state_changed == true)
            );
        }
    }
    return false;
}

static void gamepad_tiny__proc(void) {

    struct key_table *tbl;

    for ( size_t i = 0; i < NUM_OF_KEY_TABLE; i++ ) {
        // Update previous key state.
        tbl = &key_table[i];
        tbl->prev_key_stat = tbl->key_stat;

        // Update key state.
        tbl->key_stat = (digitalRead(tbl->pin) == LOW);

        // Detect of key_stat changes.
        tbl->is_key_state_changed = (tbl->key_stat != tbl->prev_key_stat);
    }
}

static size_t gamepad_tiny__get_key_count(void) {
    return NUM_OF_KEY_TABLE;
}

const mgc_gamepad_if_t gamepad_tiny = {
    gamepad_tiny__init,
    gamepad_tiny__deinit,
    gamepad_tiny__get_key_state,
    gamepad_tiny__is_key_state_changed,
    gamepad_tiny__is_key_on_edge,
    gamepad_tiny__is_key_off_edge,
    gamepad_tiny__proc,
    gamepad_tiny__get_key_count,
};

