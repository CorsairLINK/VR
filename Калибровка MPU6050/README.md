<b>Прошивка, которая калибрует параметры <code>Offset();</code> mpu6050</b><br/>

<img src="https://user-images.githubusercontent.com/75369161/223324195-cd5b0da5-542c-4d15-8177-07544704d9f5.png" width=60% height=60%><br/>

<b>Порядок прошивки:</b>
1. Загрузить прошивку "Калибровка MPU6050.ino" в плату Arduino Nano через Arduino IDE
2. Подключить плату mpu6050:<br/>
  VCC -> +5 V<br/>
  GND -> GND<br/>
  SCL -> A5<br/>
  SDA -> A4<br/>
(<a href="https://github.com/CorsairLINK/VR/tree/main/%D0%A1%D1%85%D0%B5%D0%BC%D0%B0%20%D0%BF%D0%BE%D0%B4%D0%BA%D0%BB%D1%8E%D1%87%D0%B5%D0%BD%D0%B8%D1%8F">Общая схема подключения</a>)</br>
3. Открыть в Arduino IDE "Монитор порта" (Serial monitor, значек лупы в правом верхнем углу), настроить его скорость на 9600 baud (Выпадающий список, справа низу) </br>
<img src="https://user-images.githubusercontent.com/75369161/224603020-f0300285-eea6-46c5-b981-1c8ddb289b06.png" width=60% height=60%><br/>

4. Расположить неподвижно, горизонтально плату mpu6050. Исключить вибрации! </br>
5. Отправить любой символ в монитор порта. (Например цифру "1") <br/>        
6. По завершению, записать полученные оффсеты и внести изменения в <a href="https://github.com/CorsairLINK/VR/tree/main/%D0%9E%D1%81%D0%BD%D0%BE%D0%B2%D0%BD%D0%B0%D1%8F%20%D0%BF%D1%80%D0%BE%D1%88%D0%B8%D0%B2%D0%BA%D0%B0%20Arduino">основную прошивку</a> <br/>
<br/>
Прошивка для калибровки взята из https://alexgyver.ru/arduino-mpu6050/
