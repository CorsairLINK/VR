#include "I2Cdev.h"
//#include "MPU6050.h"
#include "MPU6050_6Axis_MotionApps20.h"
MPU6050 mpu;
// Адреса кнопок
#define GRIP_BTN  0x0001
#define THUMB_BTN 0x0002
//#define A_BTN   0x0004 // Данные кнопки закоментированны, т.к. не используються (Пока что)
//#define B_BTN   0x0008
#define MENU_BTN  0x0010
#define SYS_BTN   0x0020
// Пины кнопок на Arduino
const byte TriggerBtnPin = 2;     // Тригер
const byte GripBtnPin = 3;        //
const byte MenuBtnPin = 4;        // Кнопка "Меню"
const byte SystemBtnPin = 5;      // Кнопка "Система"
// Стик
const int pinX = A0; // Подключение вывода outX к пину A0 (Ось стика X)
const int pinY = A1; // Подключение вывода outY к пину A1 (Ось стика Y)
const byte ThumbStickBtnPin = 6;  // Кнопка стика (outSw)
// Светодиод для трекинга, помещенный внутрь белого шарика
const byte LED_PIN = 7;      // Пин светодиода D7 => резистор 220 Ом => (+) Светодиод (-) => GND 

float ctrl[12];
uint8_t fifoBuffer[45]; // FIFO буфер
//----------- УСТАНОВКА ------------//
void setup() {
  Wire.begin();
  Serial.begin(115200); // Скорость Serial port: 115200 baud
  mpu.initialize(); // Инициализация mpu
  // Установка оффсетов (Ставятся после калибровки индивидуально)
  mpu.setXGyroOffset(-1967);
  mpu.setYGyroOffset(-1170);
  mpu.setZGyroOffset(1469);
  mpu.setXAccelOffset(75);
  mpu.setYAccelOffset(25); 
  mpu.setZAccelOffset(35);

  mpu.dmpInitialize(); // Инициализация DPM
  mpu.setDMPEnabled(true);  
  // Кнопки
  pinMode(TriggerBtnPin, INPUT_PULLUP);
  pinMode(GripBtnPin, INPUT_PULLUP);
  pinMode(SystemBtnPin, INPUT_PULLUP);
  pinMode(MenuBtnPin, INPUT_PULLUP);
  // Стик
  pinMode(pinX, INPUT); // Настраиваем пин А0 на чтение
  pinMode(pinY, INPUT); // Настраиваем пин А1 на чтение
  pinMode(ThumbStickBtnPin, INPUT_PULLUP); // Пин кнопки стика
  // Вывод светодиода для трекинга
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // Включаем светодиод
}
//----------- ОСНОВНОЙ ЦИКЛ ------------//
void loop() {
  static uint32_t tmr;
  if (millis() - tmr >= 11) {  // таймер на 11 мс (на всякий случай)
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
      // Переменные для расчёта
      Quaternion q;
      VectorFloat gravity;
      float ypr[3];  // [yaw, pitch, roll]   yaw/pitch/roll контейнер
      // Расчёты
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      // Установка позиций
      ctrl[0] = -0.05;  // X - Правее/Левее
      ctrl[1] = -0.05;  // Y - Выше/Ниже
      ctrl[2] = -0.30;  // Z - Ближе/Дальше
      // Позиция датчика в контроллере (Yaw, Pitch, Roll)      
      ctrl[3] = degrees(ypr[2]);       // Yaw - Рыскание
      ctrl[4] = degrees(ypr[0]) * -1;   // Pitch - Тангаж
      ctrl[5] = degrees(ypr[1]);        // Roll - Крен
      // Позиция датчика на плече (Yaw, Pitch)
      ctrl[6] = 0;
      ctrl[7] = 0;
      // Кнопки
      ctrl[8] = 0; // Кнопки
      ctrl[9] = 0; // Триггер
      ctrl[10] = 0; // Стик (Ось X)
      ctrl[11] = 0; // Стик (Ось Y)
      // Проверка нажатия кнопок
      int CtrlButtons = 0;
      if (digitalRead(GripBtnPin) == LOW)
        CtrlButtons |= GRIP_BTN;
      if (digitalRead(ThumbStickBtnPin) == LOW)
        CtrlButtons |= THUMB_BTN; 
      if (digitalRead(MenuBtnPin) == LOW)
        CtrlButtons |= MENU_BTN;
      if (digitalRead(SystemBtnPin) == LOW)
        CtrlButtons |= SYS_BTN;
      ctrl[8] = CtrlButtons;
      // Тригер
      if (digitalRead(TriggerBtnPin) == LOW)
        ctrl[9] = 1;
      // Стик (С поддержкой чувствительности)
      if (analogRead(pinX) > 520 || analogRead(pinX) < 500) {
        int pinX_0 = analogRead(pinX);
        float pinX_1;
        pinX_1 = 1023 - pinX_0;
        pinX_1 = 1 - (pinX_1 / 510);
        ctrl[10] = pinX_1; // Ось X (Передача числа от -1.00 до 1.00)
      }
      if (analogRead(pinY) > 520 || analogRead(pinY) < 500) {
        int pinY_0 = analogRead(pinY);
        float pinY_1;
        pinY_1 = 1023 - pinY_0;
        pinY_1 = 1 - (pinY_1 / 510);
        ctrl[11] = pinY_1; // Ось Y (Передача числа от -1.00 до 1.00)
      }
      // Отправка пакета данных (ctrl[]) в Seral port
      Serial.write((byte*)&ctrl, sizeof(ctrl));

      tmr = millis();  // сброс таймера
    }
  }
}
