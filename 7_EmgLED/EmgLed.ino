#include <TimerOne.h>

#define arrSize 32
#define noise 800

const int adc_0 = A0;
byte adc_bytes;

double sData = 0;

int val[arrSize]; //массив для сравнения с порогом
int measure;

int i=0;

void setup() {
  Timer1.initialize(3000);
  Timer1.attachInterrupt(sendData);

  Serial.begin(115200);
  pinMode(7,OUTPUT);
  digitalWrite(7,LOW);
  
  for (int k=0; k<arrSize; k++) {
    val[k] = 0;
  }
}

void sendData() {
  val[i] =  map(analogRead(adc_0), 0, 1023, 0, 255); //конвертация из 10бит в байт

  Serial.write("A0");
  Serial.write(val[i]);

  val[i] = 19* val[i];
  // Serial.println(sData);
  
  i++;
  
  if (sData > noise)
    digitalWrite(7, HIGH);
  else
    digitalWrite(7, LOW);   
  
  if (i > arrSize - 1) {
    double maxV = val[0], minV = val[0];
    
    for (int k = 0; k < arrSize; k++) {
      if ( val[k] > maxV)
        maxV = val[k];
      if ( val[k] < minV)
        minV = val[k];
    }

    sData =  0.4 * sData + 0.6 * (maxV - minV);
    //не выходим индексом i 
    i = 0;
  }
  
  
}


void loop() {
  
}
