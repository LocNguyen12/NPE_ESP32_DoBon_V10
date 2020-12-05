#include <main.h>

int LED = 2;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void toggleLED(void *parameter)
{
  for (;;)
  {
    statusGPIO(LED, TOGGLE);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void sensorWork(void *parameter)
{
  for (;;)
  {
    // if (lcdSerial.available())
    // {
    //   lcdSerial.print(char(lcdSerial.read()));
    // }
    vTaskDelay(1 / portTICK_PERIOD_MS );
  }
}

// void sensorWork(void *parameter)
// {
//   for (;;)
//   {
//     sensorSerial.println("Hello sensor");
//     vTaskDelay(1000 / portTICK_PERIOD_MS );
//   }
// }

//  void setup ===========================================================================================
void setup()
{
  initSetup();

  xTaskCreate(toggleLED, "Toggle LED", 1000, NULL, 2, NULL);
  xTaskCreate(sensorWork, "sensorWork", 1000, NULL, 1, NULL);
}

void loop()
{
    if (lcdSerial.available())
    {
      lcdSerial.print(char(lcdSerial.read()));
    }
    if (sensorSerial.available())
    {
      sensorSerial.print(char(sensorSerial.read()));
    }
}

//  Setup ==================================================
void initSetup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  lcdSerial.begin(9600);
  sensorSerial.begin(9600);
  initDS1307();
  writeDS1307(9, 51, 0, 7, 5, 12, 20);
}
//  GPIO ========================================================
void statusGPIO(int GPIO, int Status)
{
  switch (Status)
  {
  case LOW:
    digitalWrite(GPIO, LOW);
    break;
  case HIGH:
    digitalWrite(GPIO, HIGH);
    break;
  case TOGGLE:
    int stt = digitalRead(GPIO);
    digitalWrite(GPIO, !stt);
    break;
  }
}
//  DS1307 RTC ==================================================
void initDS1307()
{
  Serial.println("Begin RTC");
  if (!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
  }

  if (!rtc.isrunning())
  {
    Serial.println("RTC is NOT running!");
  }
}
void writeDS1307(uint8_t hour, uint8_t min, uint8_t sec, uint8_t day, uint8_t date, uint8_t month, uint16_t year)
{
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  year = year + 2000;
  rtc.adjust(DateTime(year, month, date, hour, min, sec));
}
void readDS1307()
{
  DateTime now = rtc.now();
  if (now.hour() <= 9)
  {
    Serial.print("0");
    Serial.print(now.hour());
  }
  else
  {
    Serial.print(now.hour());
  }
  Serial.print(':');
  if (now.minute() <= 9)
  {
    Serial.print("0");
    Serial.print(now.minute());
  }
  else
  {
    Serial.print(now.minute());
  }
  Serial.print(':');
  if (now.second() <= 9)
  {
    Serial.print("0");
    Serial.print(now.second());
  }
  else
  {
    Serial.print(now.second());
  }
  Serial.println();

  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(",");
  if (now.day() <= 9)
  {
    Serial.print("0");
    Serial.print(now.day());
  }
  else
  {
    Serial.print(now.day());
  }
  Serial.print('/');
  if (now.month() <= 9)
  {
    Serial.print("0");
    Serial.print(now.month());
  }
  else
  {
    Serial.print(now.month());
  }
  Serial.print('/');
  if (now.year() <= 9)
  {
    Serial.print("0");
    Serial.print(now.year());
  }
  else
  {
    Serial.print(now.year());
  }
  Serial.println();
}
// =============================================================