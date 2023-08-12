#include <LiquidCrystal_I2C.h>
  // put your setup code here, to run once:
//#include <LiquidCrystal_I2C.h>      // подключаем библу
LiquidCrystal_I2C lcd(0x27, 16, 2); // адрес, столбцов, строк
// полученные адреса
uint8_t s1_addr[] = {0x28, 0xFF, 0x5E, 0xBB, 0x82, 0x16, 0x3, 0xF3};
uint8_t s2_addr[] = {0x28, 0xFF, 0xE, 0x6, 0x85, 0x16, 0x5, 0xCD};
uint8_t s3_addr[] = {0x28, 0xFF, 0x46, 0xF4, 0x82, 0x16, 0x3, 0xCB};
#include <microDS18B20.h>
MicroDS18B20<2, s1_addr> sensor1;  // Создаем термометр с адресацией
MicroDS18B20<2, s2_addr> sensor2;  // Создаем термометр с адресацией
MicroDS18B20<2, s3_addr> sensor3;  // Создаем термометр с адресацией
void setup() {
  lcd.init();           // инициализация
  lcd.backlight();      // включить подсветку
}
void loop() {
  // запрашиваем температуру
  sensor1.requestTemp();
  sensor2.requestTemp();
  sensor3.requestTemp();
  // ждём
  delay(1000);
  // получаем и записываем в переменные
  float t1 = sensor1.getTemp();
  float t2 = sensor2.getTemp();
  float t3 = sensor3.getTemp();

  lcd.home();
  lcd.print(t1, 1);     // температура 1
  lcd.write(223);       // градус
  lcd.print('H ');       // "минус"
  lcd.print(t2, 1);     // температура 2
  lcd.write(223);       // градус
  lcd.print('i ');       // "равно"
  lcd.print(t3, 1);  // ищем разность и выводим
  lcd.write(223);       // градус
}


