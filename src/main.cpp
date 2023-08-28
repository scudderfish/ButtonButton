#include <Arduino.h>
#include <BleKeyboard.h>
#include <U8g2lib.h>
#include <EEPROM.h>
#include "heltec.h"

#define BUTTON_PIN GPIO_NUM_14

float XS = (0.00225) * 3700 / 5450; //Empirical fudge
uint16_t MUL = 1000;
uint16_t MMUL = 100;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, 16, 15, 4);
char chBuffer[128];

BleKeyboard bleKeyboard("Panic Button");

int32_t meetingCount = 0;
int32_t totalDurationSeconds = 0;
int32_t startTime = millis();

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
  EEPROM.begin(2 * sizeof(int32_t));
  meetingCount = max(0, EEPROM.readInt(0));
  totalDurationSeconds = max(0, EEPROM.readInt(sizeof(int32_t)));
  Serial.printf("INIT meeting count: %d  TDS: %d\n", meetingCount, totalDurationSeconds);
}

void loop()
{
  int32_t currentDurationSeconds = ((millis() - startTime) / 1000);
  u8g2.clearBuffer();
  if (digitalRead(BUTTON_PIN) == 0)
  { //Button is down

    if (bleKeyboard.isConnected())
    {
      u8g2.drawStr(0, 0, "That's it! I'm going!");
      meetingCount++;
      Serial.printf("Meeting count is now %d\n", meetingCount);
      totalDurationSeconds = totalDurationSeconds + currentDurationSeconds;
      EEPROM.writeInt(0, meetingCount);
      EEPROM.writeInt(sizeof(int32_t), totalDurationSeconds);
      EEPROM.commit();
      sprintf(chBuffer, "Meetings left: %d", EEPROM.readInt(0));
      u8g2.drawStr(0, 20, chBuffer);
      u8g2.sendBuffer();
      bleKeyboard.press(KEY_RIGHT_GUI);
      bleKeyboard.press(KEY_RIGHT_SHIFT);
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

  u8g2.drawStr(0, 0, "Panic Button");
  sprintf(chBuffer, "Meetings quit : %d", meetingCount);
  u8g2.drawStr(0, 10, chBuffer);
  int currentTotal = totalDurationSeconds + currentDurationSeconds;
  int currentSeconds = (currentTotal % 60);
  int currentMinutes = (currentTotal / 60) % 60;
  int currentHours = (currentTotal / 3600) % 8;
  int currentDays = (currentTotal / 3600) / 8;
  sprintf(chBuffer, "Total   : %dd%dh%02dm%02ds", currentDays, currentHours, currentMinutes, currentSeconds);
  u8g2.drawStr(0, 20, chBuffer);
  sprintf(chBuffer, "Current : %ds", currentDurationSeconds);
  u8g2.drawStr(0, 30, chBuffer);

  uint16_t c = analogRead(37) * XS * MUL;
  sprintf(chBuffer, "Battery : %d", (c / 100) * 100);
  u8g2.drawStr(0, 40, chBuffer);
  if (!bleKeyboard.isConnected())
  {
    u8g2.drawStr(0, 50, "Not Connected");
  }
  u8g2.sendBuffer();
  uint16_t batLevel = (c / 390) * 10;
  // Serial.printf("Setting batLevel to %d %d\n", c, batLevel);
  bleKeyboard.setBatteryLevel(batLevel);

  delay(100);
}