#include <Arduino.h>
#include <BleKeyboard.h>
#include <U8g2lib.h>
#include <EEPROM.h>
#include "heltec.h"

#define BUTTON_PIN GPIO_NUM_14

#define Fbattery 3700 //The default battery is 3700mv when the battery is fully charged.

//float XS = 0.00225; //The returned reading is multiplied by this XS to get the battery voltage.
float XS = (0.00225) * 3700 / 5450; //Empirical fudge
uint16_t MUL = 1000;
uint16_t MMUL = 100;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, 16, 15, 4);
char chBuffer[128];

BleKeyboard bleKeyboard("Panic Button");

int32_t meetingCount = 0;

void setup()
{
  Serial.begin(115200);
  //delay(500);
  //print_wakeup_reason();
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
  bleKeyboard.begin();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  adcAttachPin(13);
  analogSetClockDiv(255); // 1338mS
  EEPROM.begin(sizeof(int32_t));
  meetingCount = max(0, EEPROM.readInt(0));
}

void loop()
{
  u8g2.clearBuffer();
  if (digitalRead(BUTTON_PIN) == 0)
  { //Button is down

    if (bleKeyboard.isConnected())
    {
      u8g2.drawStr(0, 0, "That's it! I'm going!");
      meetingCount++;
      EEPROM.writeInt(0, meetingCount);
      EEPROM.commit();
      sprintf(chBuffer, "Meetings left: %d", EEPROM.readInt(0));
      u8g2.drawStr(0, 20, chBuffer);
      u8g2.sendBuffer();
      bleKeyboard.press(KEY_LEFT_CTRL);
      delay(100);

      bleKeyboard.press('w');
      delay(500);
      bleKeyboard.releaseAll();
      delay(1000);
    }

    bleKeyboard.end();
    esp_sleep_enable_ext0_wakeup(BUTTON_PIN, 1);
    esp_deep_sleep_start();
  }
  bleKeyboard.setBatteryLevel(90);
  u8g2.drawStr(0, 0, "Panic Button");
  sprintf(chBuffer, "Meetings left : %d", meetingCount);
  u8g2.drawStr(0, 10, chBuffer);

  uint16_t c = analogRead(37) * XS * MUL;
  sprintf(chBuffer, "Battery : %d", (c / 100) * 100);
  u8g2.drawStr(0, 20, chBuffer);
  u8g2.sendBuffer();
  delay(100);
}