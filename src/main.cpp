#include <C:\Users\ivanb\Documents\mbed-os-master>
#include <Sht31.h>

Sht31 sht31(I2C_SDA, I2C_SCL);

Thread lightLoop, RFIDLoop;

void lightCycle()
{
  bool isLightEnable;
  while (1)
  {
    isLightEnable = true;
    // свет горит 3 часа с 7 до 10 утра или с 19 вечера по 22 вечера
    thread_sleep_for(10800000);
    isLightEnable = false;
    // свет не горит 9 часов  с 10 утра по 19 вечера или с 22 вечера по 7 утра
    thread_sleep_for(32400000);
  }
}

void RFIDCycle()
{
  while (1)
  {
   // Заготовка для RFID
  }
}

int main()
{
  int temp, humidity;
  bool isOpenWindow, isEnableHeating;
  // Цикл освещения в отдельном потоке
  lightLoop.start(lightCycle);
  // Цикл RFID в отдельном потоке
  RFIDLoop.start(RFIDCycle);

  while (1)
  {
    temp = sht31.readTemperature();
    humidity = sht31.readHumidity();
    if (humidity < 60)
    {
      // делаем какой-то код для включения увлажнителя
    }
    switch (temp)
    {
    case 11:
      // Если температура < 12 закрываем окно и включаем подогрев
      isOpenWindow = false;
      isEnableHeating = true;
      break;
    case 17:
      // Если температура > 16 открываем окно и выключаем подогрев
      isOpenWindow = true;
      isEnableHeating = false;
      break;
    default:
      // В случаем недостижения пограничных значений закрываем окно и выключаем подогрев
      isOpenWindow = false;
      isEnableHeating = false;
      break;
    }
    // Ставим задержку в 5 минут чтобы успело проветриться и подогреться
    thread_sleep_for(300000);
  }
}
