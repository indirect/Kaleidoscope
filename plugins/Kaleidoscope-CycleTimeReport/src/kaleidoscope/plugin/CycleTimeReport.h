/* -*- mode: c++ -*-
 * Kaleidoscope-CycleTimeReport -- Scan cycle time reporting
 * Copyright (C) 2017, 2018  Keyboard.io, Inc
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h>  // for uint32_t, uint16_t

#include "kaleidoscope/event_handler_result.h"  // for EventHandlerResult
#include "kaleidoscope/plugin.h"                // for Plugin
// -----------------------------------------------------------------------------
// Deprecation warning messages
#include "kaleidoscope_internal/deprecations.h"  // for DEPRECATED

#define _DEPRECATED_MESSAGE_CYCLETIMEREPORT_AVG_TIME                      \
  "The `CycleTimeReport.average_loop_time` variable is deprecated. See\n" \
  "the current documentation for CycleTimeReport for details.\n"          \
  "This variable will be removed after 2022-09-01."
// -----------------------------------------------------------------------------

namespace kaleidoscope {
namespace plugin {
class CycleTimeReport : public kaleidoscope::Plugin {
 public:
  EventHandlerResult onSetup();
  EventHandlerResult beforeEachCycle();
  EventHandlerResult afterEachCycle();

#ifndef NDEPRECATED
  DEPRECATED(CYCLETIMEREPORT_AVG_TIME)
  static uint32_t average_loop_time;
#endif

 private:
  static uint16_t last_report_time_;
  static uint32_t loop_start_time_;
};

}  // namespace plugin
}  // namespace kaleidoscope

void cycleTimeReport(void);

extern kaleidoscope::plugin::CycleTimeReport CycleTimeReport;
