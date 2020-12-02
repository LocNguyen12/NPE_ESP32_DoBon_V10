#include <Arduino.h>
#include <SoftwareSerial.h>

int LED = 2;

SoftwareSerial lcdSerial(16, 17); // RX, TX'
SoftwareSerial sensorSerial(25, 26); // RX, TX'

void setup() {
  pinMode(LED, OUTPUT);
  lcdSerial.begin(9600);
  sensorSerial.begin(115200);
}

void loop() {
    lcdSerial.println("Hello lcd 2");
    sensorSerial.println("Hello sensor 6");
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
    digitalWrite(LED, HIGH);
}
