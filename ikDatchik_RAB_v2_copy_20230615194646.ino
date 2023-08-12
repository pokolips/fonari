#include "IRremote.h"
#define krut
//https://robotclass.ru/tutorials/arduino-ir-remote-control/
IRrecv irrecv(2);  // указываем вывод, к которому подключен приемник

decode_results results;
const int Relay = 6;
boolean stop = false;
boolean pusk = false;
int RelayState = LOW;     // этой переменной устанавливаем состояние светодиода
long previousMillis = 0;  // храним время последнего переключения светодиода
boolean milState = false;
long interval = 1000;  // интервал между включение/выключением светодиода (1 секунда)

void setup() {
  Serial.begin(9600);
  pinMode(Relay, OUTPUT);
  irrecv.enableIRIn();  // запускаем прием
}
void loop() {
    Serial.print ("pusk");
    Serial.print (pusk);
    Serial.println (stop);
    Serial.println (interval);
  if (irrecv.decode(&results)) {  // если данные пришли
    switch (results.value) {
      case 0x100C:
        stop = false;
        pusk = false;
        break;
      case 0x180C:
        stop=false;
        pusk = false;
        break;
      case 0x1810:
        pusk = true;
        break;
      case 0x1010:
        pusk = true;
        break;
      case 0x1811:
      interval=1000;
        stop = true;
        break;
      case 0x1011:
      interval=1000;
        stop = true;
        break;
         case 0x1820://---
        interval = 500;
        stop = true;
        break;
         case 0x1020:
        interval = 500;
        stop = true;
        break;
        case 0x1821:
        pusk = false;
        break;
      case 0x1021:
        pusk = false;
        break;
    }
    irrecv.resume();  // принимаем следующую команду
  }
  if (pusk == true){
    RelayState = HIGH;
    Serial.print ("stop");
    Serial.print (pusk);
    Serial.println (stop);
    digitalWrite(Relay, RelayState);
    }
 // }
    if (stop == true) {
    unsigned long currentMillis = millis();

    //проверяем не прошел ли нужный интервал, если прошел то
    if (currentMillis - previousMillis > interval) {
      // сохраняем время последнего переключения
      previousMillis = currentMillis;

      // если светодиод не горит, то зажигаем, и наоборот
      if (RelayState == LOW)
        RelayState = HIGH;
      else
        RelayState = LOW;

      // устанавливаем состояния выхода, чтобы включить или выключить светодиод
      digitalWrite(Relay, RelayState);
      milState = true;
    }
  }
  if (stop == false) {
    digitalWrite(Relay, LOW);
  }
}
void Blink() {
  if (digitalRead(Relay)== HIGH) {
    digitalWrite (Relay,LOW);
    delay(10000);
  }
 int strip = 0;
  while (strip <= 600000) {
       digitalWrite( Relay, HIGH );
delay(500);
digitalWrite( Relay, LOW );
delay(1000); 
//break;
}
//break;
    }

void pauseMil() {
  unsigned long currentMillis = millis();

  //проверяем не прошел ли нужный интервал, если прошел то
  if (currentMillis - previousMillis > interval) {
    // сохраняем время последнего переключения
    previousMillis = currentMillis;

    // если светодиод не горит, то зажигаем, и наоборот
    if (RelayState == LOW)
      RelayState = HIGH;
    else
      RelayState = LOW;

    // устанавливаем состояния выхода, чтобы включить или выключить светодиод
    digitalWrite(Relay, RelayState);
    milState = true;
  }
}
