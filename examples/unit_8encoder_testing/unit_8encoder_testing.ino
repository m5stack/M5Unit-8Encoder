/*
    Description: Provide three LEGO motor drive modes。Press button B to switch
   the mode, button A and C control parameter value increase and decrease
*/

#include <M5Stack.h>
#include "UNIT_8ENCODER.h"
#include <M5GFX.h>

M5GFX display;
M5Canvas canvas(&display);
UNIT_8ENCODER sensor;

long delay_time = 0;

void show_rgb_led(void) {
    sensor.setAllLEDColor(0xff0000);
    delay(1000);
    sensor.setAllLEDColor(0x00ff00);
    delay(1000);
    sensor.setAllLEDColor(0x0000ff);
    delay(1000);
    sensor.setAllLEDColor(0x000000);
}

void show_encoder_value(void) {
    int32_t encoder[8]    = {0};
    uint8_t btn_stauts[8] = {0};
    bool switch_status    = false;

    canvas.clear(BLACK);
    canvas.setCursor(80, 0);
    canvas.setTextSize(2);
    canvas.setTextColor(YELLOW);
    canvas.printf("8Encoder Demo");
    canvas.setColor(ORANGE);
    canvas.drawLine(0, 25, 320, 25);
    canvas.drawLine(0, 25 + 30, 320, 25 + 30);
    canvas.setCursor(0, 30);
    canvas.setTextSize(2);
    canvas.setTextColor(WHITE);
    canvas.printf("1-4");
    canvas.setColor(ORANGE);
    canvas.drawLine(60, 30, 60, 25 + 30);
    canvas.drawLine(125, 30, 125, 25 + 30);
    canvas.drawLine(190, 30, 190, 25 + 30);
    canvas.drawLine(255, 30, 255, 25 + 30);

    canvas.setColor(ORANGE);
    canvas.drawLine(0, 55 + 30, 320, 55 + 30);
    canvas.setCursor(0, 30 + 30);
    canvas.setTextSize(2);
    canvas.setTextColor(WHITE);
    canvas.printf("5-8");
    canvas.setColor(ORANGE);
    canvas.drawLine(60, 25 + 30, 60, 55 + 30);
    canvas.drawLine(125, 25 + 30, 125, 55 + 30);
    canvas.drawLine(190, 25 + 30, 190, 55 + 30);
    canvas.drawLine(255, 25 + 30, 255, 55 + 30);

    canvas.setTextColor(GREEN);
    for (int i = 0; i < 8; i++) {
        encoder[i]    = sensor.getEncoderValue(i);
        btn_stauts[i] = sensor.getButtonStatus(i);
    }
    for (int i = 0; i < 8; i++) {
        if (!btn_stauts[i]) {
            if (i < 4)
                canvas.fillRect(60 + 65 * i, 30, 65, 25, GREEN);
            else
                canvas.fillRect(60 + 65 * (i - 4), 60, 65, 25, GREEN);
        }
    }
    canvas.drawString(String(encoder[0]), 60, 30);
    canvas.drawString(String(encoder[1]), 125, 30);
    canvas.drawString(String(encoder[2]), 190, 30);
    canvas.drawString(String(encoder[3]), 255, 30);
    canvas.drawString(String(encoder[4]), 60, 60);
    canvas.drawString(String(encoder[5]), 125, 60);
    canvas.drawString(String(encoder[6]), 190, 60);
    canvas.drawString(String(encoder[7]), 255, 60);

    switch_status = sensor.getSwitchStatus();
    canvas.setCursor(10, 120);
    canvas.setTextColor(WHITE);
    canvas.printf("switch:");
    if (switch_status) {
        canvas.fillRect(100, 110, 50, 30, GREEN);
    } else {
        canvas.fillRect(100, 110, 50, 30, RED);
    }

    canvas.setColor(ORANGE);
    canvas.drawLine(0, 185, 320, 185);
    canvas.drawLine(120, 185, 120, 320);
    canvas.drawLine(210, 185, 210, 320);
    canvas.setTextColor(YELLOW);
    canvas.drawString("RGB", 30, 190);
    canvas.drawString("Show", 30, 220);
    canvas.drawString("Encoder", 130, 190);
    canvas.drawString("Reset", 130, 220);

    canvas.pushSprite(0, 0);
}

void setup() {
    M5.begin(true, false, true);
    M5.Power.begin();
    display.begin();
    sensor.begin(&Wire, ENCODER_ADDR, 21, 22, 100000UL);
    canvas.setColorDepth(8);  // mono color
    // canvas.setFont(&fonts::efontCN_12);
    canvas.createSprite(display.width(), display.height());

    delay_time = millis() + 10;
}

void loop() {
    show_encoder_value();
    M5.update();
    if (M5.BtnA.wasPressed()) {
        show_rgb_led();
    } else if (M5.BtnB.wasPressed()) {
        for (int i = 0; i < 8; i++) {
            sensor.resetCounter(i);
        }
    }
}