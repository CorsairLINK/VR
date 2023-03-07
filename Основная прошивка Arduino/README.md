<b>Основная Arduino прошивка</b><br/>
- Перед компиляцией и загрузки основной прошивки, установите <a href="https://github.com/CorsairLINK/VR/tree/main/%D0%91%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA%D0%B8%20Arduino">библиотеки</a><br/>
- Пины подключения кнопок и светодиода для трекинга выбираются по вашему желанию. Используйте для этого только цифровые пины (D2 - D12 / 2 - 12). Для подключения стика используються аналоговые выводы Arduino (A0 - A7 / 14 - 21). Имейте ввиду, что пины A4 и A5 уже используються под шину I2C для работы с датчиком mpu6050.<br/>
<img src="https://user-images.githubusercontent.com/75369161/223326437-584a8c7a-e108-4c6b-ab03-3757ba9facba.png" width=60% height=60%><br/>
- Оффсеты устанавливаються на основе <a href="https://github.com/CorsairLINK/VR/tree/main/%D0%9A%D0%B0%D0%BB%D0%B8%D0%B1%D1%80%D0%BE%D0%B2%D0%BA%D0%B0%20MPU6050">калибровочных данных</a><br/>
<img src="https://user-images.githubusercontent.com/75369161/223324195-cd5b0da5-542c-4d15-8177-07544704d9f5.png" width=60% height=60%><br/>
<br/>
- Прошивка Arduino, формирует пакет данных ctrl[12] и отправляет его по Serial port<br/>
<img src="https://user-images.githubusercontent.com/75369161/223334724-94165ea0-64ff-4416-9f79-c0e3c8f76f8b.png" width=60% height=60%><br/>
<b>Полезная информация:</b><br/>
1. <a href="https://alexgyver.ru/lessons/digital/">Цифровые пины</a><br/>
2. <a href="https://alexgyver.ru/lessons/analog-pins/">Аналоговые пины</a><br/>
