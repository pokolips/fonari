//https://robotchip.ru/obzor-datchika-davleniya-bmp180/?ysclid=lmimf1ivm7663737046
#include <SFE_BMP180.h>
#include <Wire.h>
 
SFE_BMP180 pressure;                          // Объявляем переменную для доступа к SFE_BMP180
 
void setup()
{
 Serial.begin(9600);                          // Задаем скорость передачи данных
 Serial.println("REBOOT");                    // Печать текста "Перезагрузка"
 
 if(pressure.begin())                         // Инициализация датчика
     Serial.println("BMP180 init success");   // Печать текста "BMP180 подключен"
   else{                                      // В противном случаи, датчик не подключен
     Serial.println("BMP180 init fail\n\n");  // Печать текста "BMP180 не подключен"
     while(1);                                // Пауза.
       }
}
 
void loop()
{
  char status;
  double T,P,p0,a;
 
/* Так как давление зависит от температуры, надо сначало узнать температуру 
 * Считывание температуры занимает какоето время. 
 * Если все хорошо, функция pressure.startTemperature вернет status с количеством милисикунд
 * которые нужно подождать. Ксли какае то проблема, то функция вернет 0.
*/
 
  status = pressure.startTemperature();       // Считывание показания
  if(status!=0){                              // Если значение status не 0, выполняем следующию команду.
     delay(status);                           // Ждем     
     status = pressure.getTemperature(T);     // Полученые показания, сохраняем в переменную T
      if(status!=0){                          // Если все хорошо, функция вернет 1, иначе вернет 0
         Serial.print("Temperature: ");       // Печать текста "Температура"
         Serial.print(T,2);                   // Печать показания переменной "Т"
         Serial.println(" C, ");              // Печать текста "С"
 
/* Определяем показания атмосферного давления
 * Параметр указывает расширение, от 0 до 3 (чем больше расширение, тем больше точность, тем долше ждать)
 * Если все хорошо, функция pressure.startTemperature вернет status с количеством милисикунд
 * которые нужно подождать. Ксли какае то проблема, то функция вернет 0.
*/
 
  status = pressure.startPressure(3);         // Считывание показания
  if(status!=0){                              // Если значение status не 0, выполняем следующию команду.
     delay(status);                           // Ждем
     status = pressure.getPressure(P,T);      // Полученные показания, сохраняем в переменную P
      if(status!=0){                          // Если все хорошо, функция вернет 1, иначе вернет 0 
         Serial.print("Absolute pressure: "); // Печать текста "Атмосферное давление"
          Serial.print(P,2);                  // Печать показания переменной mBar
          Serial.print(" mbar, ");            // Печать текста "mBar"
          Serial.print(P*0.7500637554192,2);  // Печать показания в mmHg
          Serial.println(" mmHg");}           // Печать текста "mmHg"
 
  else Serial.println("error retrieving pressure measurement\n");}    // Ошибка получения давления
  else Serial.println("error starting pressure measurement\n");}      // Ошибка запуска получения давления
  else Serial.println("error retrieving temperature measurement\n");} // Ошибка получения температуры
  else Serial.println("error starting temperature measurement\n");    // Ошибка запуска получения температуры
  delay(5000);                                                        // Пауза в 5с
}
