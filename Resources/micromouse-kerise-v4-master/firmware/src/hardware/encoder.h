/**
 * @file encoder.h
 * @brief Encoder Driver
 * @author Ryotaro Onuki <kerikun11+github@gmail.com>
 * @date 2021-11-21
 * @copyright Copyright 2021 Ryotaro Onuki <kerikun11+github@gmail.com>
 */
#pragma once

#include "app_log.h"
#include "config/io_mapping.h"  //< for KERISE_SELECT
#include "config/model.h"       //< for ENCODER_NUM

#include <drivers/as5048a/as5048a.h>
#include <drivers/ma730/ma730.h>
#include <freertospp/semphr.h>

#include <cmath>
#include <iomanip>
#include <mutex>

namespace hardware {

class Encoder {
 public:
  Encoder() {}
  bool init(spi_host_device_t spi_host,
            std::array<gpio_num_t, ENCODER_NUM> pins_cs) {
#if KERISE_SELECT == 4 || KERISE_SELECT == 3
    if (!as.init(spi_host, pins_cs[0])) {
      app_loge << "AS5048A init failed :(" << std::endl;
      return false;
    }
#elif KERISE_SELECT == 5
    if (!ma[0].init(spi_host, pins_cs[0])) {
      app_loge << "Encoder L init failed :(" << std::endl;
      return false;
    }
    if (!ma[1].init(spi_host, pins_cs[1])) {
      app_loge << "Encoder R init failed :(" << std::endl;
      return false;
    }
#endif
    xTaskCreatePinnedToCore(
        [](void* arg) { static_cast<decltype(this)>(arg)->task(); }, "Encoder",
        2048, this, 6, NULL, PRO_CPU_NUM);
    return true;
  }
  int get_raw(uint8_t ch) const { return pulses_raw[ch]; }
  float get_position(uint8_t ch) {
    std::lock_guard<std::mutex> lock_guard(mutex);
    /* the reason the type of pulses is no problem with type int */
    /* estimated position 1,000 [mm/s] * 10 [min] * 60 [s/min] = 600,000 [mm] */
    /* int32_t 2,147,483,647 / 16384 * 1/3 * 3.1415 * 13 [mm] = 1,784,305 [mm]*/
    return positions[ch];
  }
  void clear_offset() {
    std::lock_guard<std::mutex> lock_guard(mutex);
    pulses_ovf[0] = pulses_ovf[1] = 0;
  }
  void csv() {
    std::printf("%d,%d\n", -pulses[0], pulses[1]);  //
  }
  void sampling_sync(portTickType xBlockTime = portMAX_DELAY) const {
    sampling_end_semaphore.take(xBlockTime);
  }

 private:
#if KERISE_SELECT == 3 || KERISE_SELECT == 4
  AS5048A_DUAL as;
#elif KERISE_SELECT == 5
  MA730 ma[2];
#endif
  int pulses[2] = {};
  int pulses_raw[2] = {};
  int pulses_prev[2] = {};
  int pulses_ovf[2] = {};
  float positions[2] = {};
  freertospp::Semaphore sampling_end_semaphore;
  std::mutex mutex;

  void task() {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) {
      vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1));
      update();
      sampling_end_semaphore.give();
    }
  }

  void update() {
    /* fetch data from encoder */
#if KERISE_SELECT == 3 || KERISE_SELECT == 4
    constexpr int pulses_size = AS5048A_DUAL::PULSES_SIZE;
    as.update();
    for (int i = 0; i < 2; i++)
      pulses_raw[i] = as.get(i);
#elif KERISE_SELECT == 5
    constexpr int pulses_size = MA730::PULSES_SIZE;
    for (int i = 0; i < 2; i++) {
      ma[i].update();
      pulses_raw[i] = ma[i].get();
    }
    pulses_raw[0] +=
        9.5e-3f * pulses_size *
            std::sin(2 * PI *
                     (float(pulses_raw[0]) / pulses_size - 0.1e-1f + 0.5f)) -
        (9.7732187836986f);
    pulses_raw[1] +=
        8.0e-3f * pulses_size *
            std::sin(2 * PI *
                     (float(pulses_raw[1]) / pulses_size - 9.9e-1f + 0.5f)) -
        (-8.23007897574619f);
#endif
    /* calculate physical value */
    float mm[2];
    for (int i = 0; i < 2; i++) {
      /* count overflow */
      if (pulses_raw[i] > pulses_prev[i] + pulses_size / 2) {
        pulses_ovf[i]--;
      } else if (pulses_raw[i] < pulses_prev[i] - pulses_size / 2) {
        pulses_ovf[i]++;
      }
      pulses_prev[i] = pulses_raw[i];
      /* calculate position */
      const float SCALE_PULSES_TO_MM =
          model::GearRatio * model::WheelDiameter * PI;
      pulses[i] = pulses_ovf[i] * pulses_size + pulses_raw[i];
      mm[i] = (pulses_ovf[i] + float(pulses_raw[i]) / pulses_size) *
              SCALE_PULSES_TO_MM;
    }
    std::lock_guard<std::mutex> lock_guard(mutex);
    /* fix rotation direction */
#if KERISE_SELECT == 3 || KERISE_SELECT == 4
    positions[0] = +mm[0];
    positions[1] = -mm[1];
#elif KERISE_SELECT == 5
    positions[0] = -mm[0];
    positions[1] = +mm[1];
#endif
  }
};

};  // namespace hardware
