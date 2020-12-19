#include <Arduino.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("Panic Button");
void print_wakeup_reason()
{
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason)
  {
  case ESP_SLEEP_WAKEUP_EXT0:
    Serial.println("Wakeup caused by external signal using RTC_IO");
    break;
  case ESP_SLEEP_WAKEUP_EXT1:
    Serial.println("Wakeup caused by external signal using RTC_CNTL");
    break;
  case ESP_SLEEP_WAKEUP_TIMER:
    Serial.println("Wakeup caused by timer");
    break;
  case ESP_SLEEP_WAKEUP_TOUCHPAD:
    Serial.println("Wakeup caused by touchpad");
    break;
  case ESP_SLEEP_WAKEUP_ULP:
    Serial.println("Wakeup caused by ULP program");
    break;
  default:
    Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
    break;
  }
}

void setup()
{
  Serial.begin(115200);
  delay(1000);
  print_wakeup_reason();
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
  pinMode(GPIO_NUM_13, INPUT_PULLUP);
}

void loop()
{

  if (digitalRead(GPIO_NUM_13) == 0)
  { //Button is down

    if (bleKeyboard.isConnected())
    {
      Serial.printf("%d\n", bleKeyboard.press(KEY_LEFT_CTRL));
      delay(100);

      Serial.printf("%d\n", bleKeyboard.press('w'));
      delay(500);
      bleKeyboard.releaseAll();
      delay(1000);
    }

    Serial.println("Going to sleep");
    bleKeyboard.end();
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_13, 1);
    esp_deep_sleep_start();
    Serial.println("This will never be printed");
  }
  bleKeyboard.setBatteryLevel(90);

  Serial.printf("Pin is %d\n", digitalRead(GPIO_NUM_13));
  delay(100);
}