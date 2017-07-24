/* -*- mode: c++ -*-
 * Kaleidoscope-LED-AlphaSquare -- 4x4 pixel LED alphabet
 * Copyright (C) 2017  Gergely Nagy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Kaleidoscope-LED-AlphaSquare.h>
#include <Kaleidoscope/LED-AlphaSquare-4x4.h>

namespace kaleidoscope {

static const uint16_t alphabet[] PROGMEM = {
  ALPHASQUARE_SYMBOL_A,
  ALPHASQUARE_SYMBOL_B,
  ALPHASQUARE_SYMBOL_C,
  ALPHASQUARE_SYMBOL_D,
  ALPHASQUARE_SYMBOL_E,
  ALPHASQUARE_SYMBOL_F,
  ALPHASQUARE_SYMBOL_G,
  ALPHASQUARE_SYMBOL_H,
  ALPHASQUARE_SYMBOL_I,
  ALPHASQUARE_SYMBOL_J,
  ALPHASQUARE_SYMBOL_K,
  ALPHASQUARE_SYMBOL_L,
  ALPHASQUARE_SYMBOL_M,
  ALPHASQUARE_SYMBOL_N,
  ALPHASQUARE_SYMBOL_O,
  ALPHASQUARE_SYMBOL_P,
  ALPHASQUARE_SYMBOL_Q,
  ALPHASQUARE_SYMBOL_R,
  ALPHASQUARE_SYMBOL_S,
  ALPHASQUARE_SYMBOL_T,
  ALPHASQUARE_SYMBOL_U,
  ALPHASQUARE_SYMBOL_V,
  ALPHASQUARE_SYMBOL_W,
  ALPHASQUARE_SYMBOL_X,
  ALPHASQUARE_SYMBOL_Y,
  ALPHASQUARE_SYMBOL_Z,
  ALPHASQUARE_SYMBOL_1,
  ALPHASQUARE_SYMBOL_2,
  ALPHASQUARE_SYMBOL_3,
  ALPHASQUARE_SYMBOL_4,
  ALPHASQUARE_SYMBOL_5,
  ALPHASQUARE_SYMBOL_6,
  ALPHASQUARE_SYMBOL_7,
  ALPHASQUARE_SYMBOL_8,
  ALPHASQUARE_SYMBOL_9,
  ALPHASQUARE_SYMBOL_0
};


cRGB AlphaSquare::color = {0x80, 0x80, 0x80};

AlphaSquare::AlphaSquare(void) {
}

void AlphaSquare::begin(void) {
}

void AlphaSquare::display(Key key, uint8_t row, uint8_t col, cRGB key_color) {
  if (key < Key_A || key > Key_0)
    return;

  uint8_t index = key.keyCode - Key_A.keyCode;
  uint16_t symbol = pgm_read_word(&alphabet[index]);

  display(symbol, row, col, key_color);
}

void AlphaSquare::display(Key key, uint8_t row, uint8_t col) {
  display(key, row, col, color);
}

void AlphaSquare::display(uint16_t symbol, uint8_t row, uint8_t col, cRGB key_color) {
  for (uint8_t r = 0; r < 4; r++) {
    for (uint8_t c = 0; c < 4; c++) {
      uint8_t pixel = bitRead(symbol, r * 4 + c);
      if (!pixel)
        continue;

      LEDControl.setCrgbAt(row + r, col + c, key_color);
    }
  }

  LEDControl.syncLeds();
}

void AlphaSquare::display(uint16_t symbol, uint8_t row, uint8_t col) {
  display(symbol, row, col, color);
}

}

kaleidoscope::AlphaSquare AlphaSquare;
