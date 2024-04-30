/* -*- mode: c++ -*-
 * Atreus -- Chrysalis-enabled Sketch for the Keyboardio Atreus
 * Copyright (C) 2018-2022  Keyboard.io, Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built on " __DATE__ " at " __TIME__
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-FirmwareVersion.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Qukeys.h"
#include "Kaleidoscope-SpaceCadet.h"
#include "Kaleidoscope-DynamicMacros.h"
#include "Kaleidoscope-LayerNames.h"

#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

enum {
  MACRO_VERSION_INFO
};

#define Key_Exclamation LSHIFT(Key_1)
#define Key_At          LSHIFT(Key_2)
#define Key_Hash        LSHIFT(Key_3)
#define Key_Dollar      LSHIFT(Key_4)
#define Key_Percent     LSHIFT(Key_5)
#define Key_Caret       LSHIFT(Key_6)
#define Key_And         LSHIFT(Key_7)
#define Key_Star        LSHIFT(Key_8)
#define Key_Plus        LSHIFT(Key_Equals)

// Other symbol aliases
#define Key_Tilde LSHIFT(Key_Backtick)
#define Key_Underscore LSHIFT(Key_Minus)
#define Key_Plus LSHIFT(Key_Equals)
#define Key_LeftCurly Key_LeftCurlyBracket
#define Key_RightCurly Key_RightCurlyBracket

// OS controls
#define Key_VolDown Consumer_VolumeDecrement
#define Key_VolUp   Consumer_VolumeIncrement
#define Key_BriDown Key_F14
#define Key_BriUp   Key_F15

// Meta key aliases
#define CAG(k) LALT(LCTRL(LGUI((k))))
#define Key_Cag LALT(LCTRL(Key_LeftGui))
#define CG(k) LCTRL(LGUI((k)))

enum {
  DVORAK,
  FUN,
  UPPER,
};

// clang-format off
KEYMAPS(
  [DVORAK] = KEYMAP_STACKED
  (
       Key_Quote     ,Key_Comma ,Key_Period   ,Key_P          ,Key_Y
      ,Key_A         ,Key_O     ,Key_E        ,Key_U          ,Key_I
      ,Key_Semicolon ,Key_Q     ,Key_J        ,Key_K          ,Key_X         ,Key_Backtick
      ,Key_Esc       ,Key_Tab   ,Key_LeftGui  ,Key_LeftShift  ,Key_Backspace ,Key_LeftControl

                      ,Key_F     ,Key_G   ,Key_C     ,Key_R     ,Key_L
                      ,Key_D     ,Key_H   ,Key_T     ,Key_N     ,Key_S
       ,Key_Backslash ,Key_B     ,Key_M   ,Key_W     ,Key_V     ,Key_Z
       ,Key_LeftAlt   ,Key_Space ,MO(FUN) ,Key_Minus ,Key_Slash ,Key_Enter
  ),

  [FUN] = KEYMAP_STACKED
  (
       Key_Exclamation ,Key_At           ,Key_UpArrow   ,Key_Dollar           ,Key_Percent
      ,Key_LeftParen   ,Key_LeftArrow    ,Key_DownArrow ,Key_RightArrow       ,Key_RightParen
      ,Key_LeftBracket ,Key_RightBracket ,Key_Hash      ,Key_LeftCurlyBracket ,Key_RightCurlyBracket ,Key_Caret
      ,TG(UPPER)       ,Key_Insert       ,Key_LeftGui   ,Key_LeftShift        ,Key_Delete            ,Key_LeftControl

                   ,Key_PageUp   ,Key_7 ,Key_8      ,Key_9 ,Key_Backspace
                   ,Key_PageDown ,Key_4 ,Key_5      ,Key_6 ,___
      ,Key_And     ,Key_Star     ,Key_1 ,Key_2      ,Key_3 ,Key_Plus
      ,Key_LeftAlt ,Key_Space    ,___   ,Key_Period ,Key_0 ,Key_Equals
   ),

  [UPPER] = KEYMAP_STACKED
  (
       Key_Insert            ,Key_Home           ,CAG(Key_UpArrow)   ,Key_End             ,Key_PageUp
      ,Key_Delete            ,CAG(Key_LeftArrow) ,CAG(Key_DownArrow) ,CAG(Key_RightArrow) ,Key_PageDown
      ,M(MACRO_VERSION_INFO) ,Key_Mute           ,Key_VolDown        ,Key_VolUp           ,Key_BriDown   ,Key_BriUp
      ,MoveToLayer(DVORAK)   ,___                ,___                ,___                 ,___           ,___

                ,Key_Home ,Key_F7              ,Key_F8          ,Key_F9         ,Key_F10
                ,Key_End  ,Key_F4              ,Key_F5          ,Key_F6         ,Key_F11
      ,___      ,XXX      ,Key_F1              ,Key_F2          ,Key_F3         ,Key_F12
      ,___      ,___      ,MoveToLayer(DVORAK) ,Key_PrintScreen ,Key_ScrollLock ,Consumer_PlaySlashPause
   )
)
// clang-format on

KALEIDOSCOPE_INIT_PLUGINS(
  EscapeOneShot,
  EEPROMSettings,
  EEPROMKeymap,
  Focus,
  FocusEEPROMCommand,
  FocusSettingsCommand,
  Qukeys,
  SpaceCadet,
  OneShot,
  Macros,
  DynamicMacros,
  MouseKeys,
  EscapeOneShotConfig,
  FirmwareVersion,
  LayerNames);

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    switch (macro_id) {
    case MACRO_VERSION_INFO:
      Macros.type(PSTR("Keyboardio Atreus - Kaleidoscope "));
      Macros.type(PSTR(BUILD_INFORMATION));
      break;
    default:
      break;
    }
  }
  return MACRO_NONE;
}

void setup() {
  Kaleidoscope.setup();
  SpaceCadet.disable();
  EEPROMKeymap.setup(9);

  DynamicMacros.reserve_storage(48);

  LayerNames.reserve_storage(63);

  Layer.move(DVORAK);
}

void loop() {
  Kaleidoscope.loop();
}
