#include <Adafruit_NeoPixel.h>

#define LED_PIN   (22)
#define NUM_LEDS  (239)
#define NUM_ROWS  (10)
#define NUM_COLS  (22)


Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.clear();
  strip.show();
  strip.setBrightness(50);
}

void loop() {
  for (int t = 0; t < 10; t++) {
    colRainbow(1, 2000, 100);
  }
  
  for (int t = 0; t < 10; t++) {
    rowRainbow(1, 2000, 100);
  }
}

void rowRainbow(int wait, int hue_row_gap, int hue_inc)
{
  // Do one cycle of the rainbow!
  for (uint32_t first_hue = 0; first_hue < 65536; first_hue += hue_inc) {
    for (int row = 0; row < NUM_ROWS; row++) {
      fillRow(strip.ColorHSV(first_hue + (hue_row_gap * row), 255, 255), row);
    }
    strip.show();
    delay(wait);
  }
}

void colRainbow(int wait, int hue_col_gap, int hue_inc)
{
  for (uint32_t first_hue = 0; first_hue < 65536; first_hue += hue_inc) {
    for (int col = 0; col < NUM_COLS; col++) {
      fillCol(strip.ColorHSV(first_hue + (hue_col_gap * col), 255, 255), col);
    }
    strip.show();
    delay(wait);
  }
}

const int row_lens[NUM_ROWS] = {25, 24, 24, 24, 23, 24, 24, 23, 24, 24};

// origin is bottom left of the frame
void setCoord(uint32_t color, int row, int col)
{
  int row_bodge[NUM_ROWS] = {2, 0, 2, 0, 1, 0, 2, 0, 1, 1};
  int led_idx = 0;
  for (int r = 0; r < row; r++) {
    led_idx += row_lens[r];
  }

  // Odd rows are "backwards"
  if ((row % 2) == 0) {
    led_idx += row_lens[row];
    led_idx -= col;
    led_idx -= row_bodge[row];
    led_idx--;
    
  } else {
    led_idx += col;
    led_idx += row_bodge[row];
  }

  strip.setPixelColor(led_idx, color);
}

void fillCol(uint32_t color, int col)
{
  for (int row = 0; row < NUM_ROWS; row++) {
    setCoord(color, row, col);
  }
}

void fillRow(uint32_t color, int row)
{
  int led_offset = 0;
  for (int r = 0; r < row; r++) {
    led_offset += row_lens[r];
  }
  
  for (int idx = 0; idx < row_lens[row]; idx++) {
    strip.setPixelColor(led_offset + idx, color);
  }
}
