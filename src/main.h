#include <Arduino.h>
#include <SoftwareSerial.h>
#include <RTClib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//  UART =================================================================================================
SoftwareSerial lcdSerial(16, 17);    // RX, TX'
SoftwareSerial sensorSerial(25, 26); // RX, TX'
//  DS1307 RTC ===========================================================================================
RTC_DS1307 rtc;

void initSetup();
//  GPIO =================================================================================================
void statusGPIO(int GPIO, int Status);
//  DS1307 RTC ===========================================================================================
void initDS1307();
void writeDS1307(uint8_t hour, uint8_t min, uint8_t sec, uint8_t day, uint8_t date,uint8_t month, uint16_t year );
void readDS1307();
