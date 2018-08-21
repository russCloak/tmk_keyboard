#include "action.h"
#include "actionmap.h"
#include "hook.h"
#include "fc660c.h"


#define AC_L3       ACTION_LAYER_MOMENTARY(3)
#define AC_L4       ACTION_LAYER_MOMENTARY(4)
#define AC_LS_2     ACTION_LAYER_MODS(2, MOD_LSFT)
#define AC_RS_2     ACTION_LAYER_MODS(2, MOD_RSFT)
#define AC_LG_3     ACTION_LAYER_MODS(1, MOD_LGUI)
#define AC_TGL1     ACTION_LAYER_TOGGLE(1)

/* #define AC_FGRV ACTION_FUNCTION_TAP(LONGF1) */

// emulates FC660C default keymap
#ifdef KEYMAP_SECTION_ENABLE
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const action_t actionmaps[][UNIMAP_ROWS][UNIMAP_COLS] PROGMEM = {
#endif
    [0] = KMAP(
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     TGL1,
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     DEL,
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,
        LS_2,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RS_2,UP,
        LCTL,LALT,LG_3,          SPC,                     RGUI,RALT,L3,  LEFT,DOWN,RGHT
    ),
    [1] = KMAP(
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     TGL1,
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     DEL,
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT,UP,
        LCTL,LALT,LGUI,          SPC,                     RGUI,RALT,L4,  LEFT,DOWN,RGHT
    ),
    [2] = KMAP(
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     TGL1,
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     DEL,
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT,UP,
        TRNS,TRNS,TRNS,          TRNS,                    RGUI,RALT,L4,  LEFT,DOWN,RGHT
    ),
    [3] = KMAP(
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,     PGUP,
        TAB, TGL1,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS,TRNS,TRNS,TRNS,     PGDN,
        TRNS,VOLD,VOLU,MUTE,TRNS,TRNS,TRNS,TRNS,HOME,PGUP,TRNS,TRNS,     TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,END, PGDN,TRNS,          TRNS,PGUP,
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,APP, L3,  HOME,PGDN,END
    ),
    [4] = KMAP(
        ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,     PGUP,
        TAB, TGL1,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS,TRNS,TRNS,TRNS,     PGDN,
        TRNS,VOLD,VOLU,MUTE,TRNS,TRNS,TRNS,TRNS,HOME,PGUP,TRNS,TRNS,     TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,END, PGDN,TRNS,          TRNS,PGUP,
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,APP, L4,  HOME,PGDN,END
    ),
};


void hook_layer_change(uint32_t layer_state)
{
    // lights LED on Insert when layer 1 is enabled
    if (layer_state & (1L<<1)) {
        PORTB &= ~(1<<5);
    } else {
        PORTB |=  (1<<5);
    }
};

enum function_id {
    LONGF1,
    LONGF2,
    LONGF3,
    LONGF4,
    LONGF5,
    LONGF6,
    LONGF7,
    LONGF8,
    LONGF9,
    LONGF10,
    LONGF11,
    LONGF12
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    /* if (record->event.pressed) dprint("P"); else dprint("R"); */
    /* dprintf("%d", record->tap.count); */
    /* if (record->tap.interrupted) dprint("i"); */
    /* dprint("\n"); */

    switch (id) {
        case LONGF1:
        case LONGF2:
        case LONGF3:
        case LONGF4:
        case LONGF5:
        case LONGF6:
        case LONGF7:
        case LONGF8:
        case LONGF9:
        case LONGF10:
        case LONGF11:
        case LONGF12:
            longfunc_function(record, id, opt);
            break;
    }
}

void longfunc_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    uint8_t tapkey;
    uint8_t longkey;

    switch (id) {
        case LONGF1:
            tapkey = KC_1;
            longkey = KC_F1;
            break;
        case LONGF2:
            tapkey = KC_2;
            longkey = KC_F2;
            break;
        case LONGF3:
            tapkey = KC_3;
            longkey = KC_F3;
            break;
        case LONGF4:
            tapkey = KC_4;
            longkey = KC_F4;
            break;
        case LONGF5:
            tapkey = KC_5;
            longkey = KC_F5;
            break;
        case LONGF6:
            tapkey = KC_6;
            longkey = KC_F6;
            break;
        case LONGF7:
            tapkey = KC_7;
            longkey = KC_F7;
            break;
        case LONGF8:
            tapkey = KC_8;
            longkey = KC_F8;
            break;
        case LONGF9:
            tapkey = KC_9;
            longkey = KC_F9;
            break;
        case LONGF10:
            tapkey = KC_0;
            longkey = KC_F10;
            break;
        case LONGF11:
            tapkey = KC_MINS;
            longkey = KC_F11;
            break;
        case LONGF12:
            tapkey = KC_EQL;
            longkey = KC_F12;
            break;
    }

    if (record->event.pressed) {
        if (record->tap.count <= 0) {
            register_code(longkey);
            unregister_code(longkey);
            record->tap.count = 0;  // ad hoc: cancel tap
        }
    } else {
        if (record->tap.count > 0) {
            register_code(tapkey);
            unregister_code(tapkey);
            record->tap.count = 0;  // ad hoc: cancel tap
        }
    }
}
