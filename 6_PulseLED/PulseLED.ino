#include <TimerOne.h>

#define LED_PIN 3

int data0 = 0;
int data1 = 0;

void sendData() {
  
  data1 = data0;
  data0 = analogRead(A0);

  if(data1 < data0 - 2)
    digitalWrite(LED_PIN, HIGH);
  else
    digitalWrite(LED_PIN, LOW);

  Serial.write ("A0");
  Serial.write(map(analogRead(A0), 0, 1023, 0, 255));
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);

  Timer1.initialize(3000); //30000
  Timer1.attachInterrupt(sendData);
}

void loop() {

}
