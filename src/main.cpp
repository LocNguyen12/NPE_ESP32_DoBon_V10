#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <RTClib.h>

int LED = 2;
/* Địa chỉ của DS1307 */
const byte DS1307 = 0x68;
/* Số byte dữ liệu sẽ đọc từ DS1307 */
const byte NumberOfFields = 7;

/* khai báo các biến thời gian */
int second, minute, hour, day, wday, month, year;

SoftwareSerial lcdSerial(16, 17);    // RX, TX'
SoftwareSerial sensorSerial(25, 26); // RX, TX'

RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
void readDS1307();

// void setup() {
//   pinMode(LED, OUTPUT);
//   lcdSerial.begin(9600);
//   sensorSerial.begin(115200);
//   Serial.begin(115200);
//   /* cài đặt thời gian cho module */
//   setTime(11, 42, 06, 5, 3, 12, 20); // 12:30:45 CN 08-02-2015
//   Wire.begin();
//   Serial.println("Khoi tao xong DS1307");
//   Serial.println("Bat dau chuong trinh");
// }

void setup()
{
  Serial.begin(115200);
  if (!rtc.begin())
  {
    Serial.print("Couldn't find RTC");
    while (1)
      ;
  }

  if (!rtc.isrunning())
  {
    Serial.print("RTC is NOT running!");
    Serial.println();
  }
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  rtc.adjust(DateTime(2020, 12, 4, 12, 05, 0));
}
void loop()
{

  delay(1000);
}

// void loop() {
//     // lcdSerial.println("Hello lcd 2");
//     // sensorSerial.println("Hello sensor 6");
//     readDS1307();
//     digitalClockDisplay();
//     delay(1000);
//     // digitalWrite(LED, LOW);
//     // delay(500);
//     // digitalWrite(LED, HIGH);
//     // scanAddressI2c();
// }

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