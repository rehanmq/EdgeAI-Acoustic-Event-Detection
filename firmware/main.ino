from pathlib import Path

# ESP32 firmware code
ino_code = """
#include <Arduino.h>
#include <driver/i2s.h>
#include <edge-impulse-sdk/classifier/ei_run_classifier.h>

#define I2S_WS  15
#define I2S_SD  32
#define I2S_SCK 14
#define BUFFER_SIZE 1024
#define OUTPUT_PIN 2

int16_t audio_buffer[BUFFER_SIZE];

void setup() {
  Serial.begin(115200);
  pinMode(OUTPUT_PIN, OUTPUT);
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = BUFFER_SIZE,
    .use_apll = false
  };
  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
}

void loop() {
  size_t bytes_read;
  i2s_read(I2S_NUM_0, (char *)audio_buffer, BUFFER_SIZE * sizeof(int16_t), &bytes_read, portMAX_DELAY);
  signal_t signal;
  numpy::signal_from_buffer(audio_buffer, bytes_read / sizeof(int16_t), &signal);
  ei_impulse_result_t result;
  EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);
  if (res != EI_IMPULSE_OK) {
    Serial.println("Inference failed");
    return;
  }
  for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
    Serial.printf("%s: %.2f\\n", result.classification[ix].label, result.classification[ix].value);
  }
  if (strcmp(result.classification[0].label, "clap") == 0 && result.classification[0].value > 0.85) {
    digitalWrite(OUTPUT_PIN, HIGH);
    delay(500);
    digitalWrite(OUTPUT_PIN, LOW);
  }
  delay(100);
}
"""

# Save to file
file_path = Path("/mnt/data/main.ino")
file_path.write_text(ino_code.strip())

file_path.name

