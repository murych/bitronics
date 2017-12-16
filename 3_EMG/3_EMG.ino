#include <TimerOne.h>

void sendData() {
  Serial.write("A0");
  Serial.write(map(analogRead(A0),0,1023,0,255));
}

void setup() {
  Timer1.initialize(3000);
  Timer1.attachInterrupt(sendData);

  Serial.begin(115200);
}

void loop() {

}
