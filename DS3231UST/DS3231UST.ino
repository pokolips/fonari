#include <microDS3231.h>
MicroDS3231 rtc;
void setup() {
  Serial.begin(9600);
}
void loop() {
  // получаем и выводим каждый элемент отдельно
  Serial.print(rtc.getHours());
  Serial.print(":");
  Serial.print(rtc.getMinutes());
  Serial.print(":");
  Serial.print(rtc.getSeconds());
  Serial.print(" ");
  Serial.print(rtc.getDay());
  Serial.print(" ");
  Serial.print(rtc.getDate());
  Serial.print("/");
  Serial.print(rtc.getMonth());
  Serial.print("/");
  Serial.println(rtc.getYear());
  
  // выводим температуру модуля
  Serial.println(rtc.getTemperatureFloat());  
  
  // выводим дату и время готовыми строками
  Serial.println(rtc.getTimeString());
  Serial.println(rtc.getDateString());
}
