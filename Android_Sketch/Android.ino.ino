#include "BluetoothSerial.h" // заголовочный файл для последовательного Bluetooth будет добавлен по умолчанию в Arduino
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
//Код для управления малой платформой (W1)по Bluetooth c Android устройства
int incoming, inc1, inc2;
int RFwd = 27; //вращение правого колеса назад 4(W2)
int RBwd = 14; //вращение правого колеса вперед 16(W2)
int LFwd = 13; //вращение левого колеса назад 2(W2)
int LBwd = 12; //вращение левого колеса вперед 15(W2)
int kick = 16; //соленоид 17(W2)
static int sO1 = -1, sO2 = -1;
int f1 = 0, f2 = 0;
int o1 = 0, o2 = 0;
int inc, i = 0;
byte arr[9];
int jump;
int checkbit(const int value, const int position) {
  int result;
  if ((value & (1 << position)) == 0) {
    result = 0;
  } else {
    result = 1;
  }
  return result;
}

int setbit(const int value, const int position) {
  return (value | (1 << position));
}
int unsetbit(const int value, const int position) {
  return (value & ~(1 << position));
}
void setup() {
  Serial.begin(115200); // Запускаем последовательный монитор со скоростью 9600 /
  SerialBT.begin("Robofootball_2"); // Задаем имя вашего устройства Bluetooth
  Serial.println("Bluetooth Device is Ready to Pair");  // По готовности сообщаем, что устройство готово к сопряжению

  pinMode (RFwd, OUTPUT);
  ledcSetup(0, 500, 8);
  ledcAttachPin(RFwd, 0);

  pinMode (LFwd, OUTPUT);
  ledcSetup(1, 500, 8);
  ledcAttachPin(LFwd, 1);

  pinMode (RBwd, OUTPUT);
  ledcSetup(2, 500, 8);
  ledcAttachPin(RBwd, 2);
  pinMode (LBwd, OUTPUT);
  ledcSetup(3, 500, 8);
  ledcAttachPin(LBwd, 3);
  //  pinMode (kick, OUTPUT);
}
void printbyte(int byt)
{
  Serial.print("byte = ");
  Serial.println(byt);
  for (int i = 7; i >= 0; i--)
  {
    if (checkbit(byt, i) == 1)
      Serial.print(1);
    else
      Serial.print(0);

  }

}
void loop()
{

  i = 0;
  if (SerialBT.available())
  {
    Serial.println("SerialBT.available()");
    while ((inc = SerialBT.read()) != -1)
    {
      arr[i] = inc;
      i++;

    }
    /*
    int ck = 0;
    for(int j = 0; j < 9;j++)
    {
      if(arr[j] == 0) ck++;
    }
    if(ck ==9)return;
    */Serial.print("i = ");
    Serial.println(i);
    SerialBT.write(100);
    Serial.println("SerialBT.write(100);");
    if (i == 2)
    {

      inc1 = arr[0];
      inc2 = arr[1];

      if (inc1 == -1 || inc2 == -1) return;
      f1 = 0;
      f2 = 0;

      if (checkbit(inc1, 7) == 1)
      {
        jump = 1;
      }
      else
      {
        jump = 0;
      }
      if (checkbit(inc1, 6) == 1)
      {
        o1 = 0;
        ledcWrite(2, 0);
      }
      else
      {
        o1 = 2;
        ledcWrite(0, 0);
      }
      if (checkbit(inc2, 6) == 1)
      {
        o2 = 1;
        ledcWrite(3, 0);
      }
      else
      {
        o2 = 3;
        ledcWrite(1, 0);
      }
      for (int i = 0; i < 6; i++)
      {
        if (checkbit(inc1, i) == 1)
        {
          f1 = setbit(f1, i);
        }
        else
        {
          f1 = unsetbit(f1, i);
        }
        if (checkbit(inc2, i) == 1)
        {
          f2 = setbit(f2, i);
        }
        else
        {
          f2 = unsetbit(f2, i);
        }
      }

      if (f1 == 0 & f2 == 0)
      {

      }
      else
      {
        f1 = f1 * 4;
        f2 = f2 * 4;
        ledcWrite(o1, f1);
        ledcWrite(o2, f2);
      }
    }
    else if (i == 3)
    {
      Serial.print((char)arr[0]);
      Serial.print((char)arr[1]);
      Serial.print((char)arr[2]);
      Serial.println(" ");
    }
    if (i == 9)
    {
      double pre, post1, post2;
      double f1 = 0;
      pre = arr[0];
      post1 = arr[1];
      post2 = arr[2];
      f1 = pre;
      f1 += post1 / 100;
      f1 += post2 / 10000;
      Serial.print("f1 = ");
      Serial.println(f1, 4);

      pre = arr[3];
      post1 = arr[4];
      post2 = arr[5];
      f1 = pre;
      f1 += post1 / 100;
      f1 += post2 / 10000;
      Serial.print("f2 = ");
      Serial.println(f1, 4);

      pre = arr[6];
      post1 = arr[7];
      post2 = arr[8];
      f1 = pre;
      f1 += post1 / 100;
      f1 += post2 / 10000;
      Serial.print("f3 = ");
      Serial.println(f1, 4);
    }
    else
    {
      if (f1 == 0 & f2 == 0)
      {
        //выключаем двигатели и соленоид
        ledcWrite(0, 0);
        ledcWrite(1, 0);
        ledcWrite(2, 0);
        ledcWrite(3, 0);
      }
      else
      if (f1 != 0 & f2 != 0)
      {
        f1 = f1;
        f2 = f2;
        ledcWrite(o1, f1);
        ledcWrite(o2, f2);
        Serial.print("f1 = ");
        Serial.println(f1);
        Serial.print("f2 = ");
        Serial.println(f2);
      }
    }
  }
}

