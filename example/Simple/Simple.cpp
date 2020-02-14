#include <Arduino.h>
#include <CircularBuffer.h>

void setup() {
  // put your setup code here, to run once:
  CircularBuffer<int> *buffer = new CircularBuffer<int>(5);
  Serial.begin(9600);
  Serial.println(String(buffer->size()));
}

void loop() {
  // put your main code here, to run repeatedly:
}