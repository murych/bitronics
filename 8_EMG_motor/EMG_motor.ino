#include <TimerOne.h>

#define arrSize 32  // Размер массива для анализа
#define noise 50  // Шумовой уровень

double sData = 0;  // Амплитуда размаха сигнала

int val[arrSize]; //массив для анализа ЭМГ сигнала

int i=0; // Глобальный счетчик 

void sendData() {
  // Отправляем имя порта, к которому подключен
  Serial.write("A0");

  // Конвертируем из 10 битного вида к 8 битному
  val[i] = map(analogRead(A0), 0, 1023, 0, 255);

  // Отправляем результат оцифровки
  Serial.write(val[i++]);
  
  if (i == arrSize) {
    // Если полностью заполнили массив
    // не выходим индексом i за размер массива
    i = 0;

    // Инициализируем максимальное и минимальное значение
    double maxV = val[0], minV = val[0];
  
    // Ищем максимальное и минимальное значение в массиве
    for (int k = 0; k < arrSize; k++) {
      if (val[k] > maxV)
        maxV = val[k];
      if (val[k] < minV)
        minV = val[k];
    }

    // Чтобы применить комплиментарный фильтр, раскомментируйте строку
    // sData =  0.4*sData + 0.6*(maxV - minV); 

    // Определяем максимальный размах сигнала
    sData = maxV - minV;
  }
  
  // Если размах сигнала больше уровня шума
  if (sData > noise)
    // Подаем логическую 1 на ногу 13
    digitalWrite(13,HIGH);
  else
    // Иначе подаем логический 0 на ногу 13
    digitalWrite(13,LOW);
}

void setup() {
  Serial.begin(115200);

  // Запускаем таймер с периодом 3 мс
  Timer1.initialize(3000);  

  // Выполняем функцию sendData каждую 3 мс
  Timer1.attachInterrupt(sendData);

  // Определим 13 ногу как вывод
  pinMode(13,OUTPUT);

  // Установим "низкое" состояние на ножке
  digitalWrite(13,LOW);

  // Заполняем массив для изучения нулями
  for (int k=0; k<arrSize;k++){
    val[k] = 0;
  }

}

void loop() {

}
