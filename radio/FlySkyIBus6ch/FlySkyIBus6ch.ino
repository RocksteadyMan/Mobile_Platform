#include "FlySkyIBus.h"
HardwareSerial FSkySerial(1);

int RFwd = 2; //вращение правого колеса назад 4(W2)17
  int RBwd = 15; //вращение правого колеса вперед 16(W2)5
  int LFwd = 4; //вращение левого колеса назад 2(W2)19
  int LBwd = 16; //вращение левого колеса вперед 15(W2)18
  int kick = 17; //соленоид 17(W2)16 //23              //16

/*int RFwd = 5; //вращение правого колеса назад 4(W2)17
int RBwd = 17; //вращение правого колеса вперед 16(W2)5
int LFwd = 18; //вращение левого колеса назад 2(W2)19
int LBwd = 19; //вращение левого колеса вперед 15(W2)18
int kick = 16; //соленоид 17(W2)16 //23              //16*/

int MoveF, MoveD, TurnLeft, TurnRight, MTL2, MTL1, MTR1, MTR2, MDTL1, MDTL2, MDTR1, MDTR2;


void setup()
{
  Serial.begin(115200);
  IBus.begin(FSkySerial);
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

  pinMode (kick, OUTPUT);

}

void loop()
{
  static uint16_t C0 = 0, C1 = 0, C2 = 0, C3 = 0, C4 = 0, C5 = 0;
  IBus.loop();
  uint16_t C0n, C1n, C2n, C3n, C4n, C5n;
  C0n = IBus.readChannel(0);
  C1n = IBus.readChannel(1);
  C2n = IBus.readChannel(2);
  C3n = IBus.readChannel(3);
  C4n = IBus.readChannel(4);
  C5n = IBus.readChannel(5);
  if (((C0 <= (C0n - 5)) || ((C0 >= (C0n + 5)))) ||
      ((C1 <= (C1n - 5)) || ((C1 >= (C1n + 5)))) ||
      ((C2 <= (C2n - 5)) || ((C2 >= (C2n + 5)))) ||
      ((C3 <= (C3n - 5)) || ((C3 >= (C3n + 5)))) ||
      ((C4 <= (C4n - 5)) || ((C4 >= (C4n + 5)))) ||
      ((C5 <= (C5n - 5)) || ((C5 >= (C5n + 5)))))
  {
    C0 = C0n; C1 = C1n; C2 = C2n; C3 = C3n; C4 = C4n; C5 = C5n;


if(C5>1800)
{
    if (C2 >= 1600)
    { Serial.print("вперед ");
      ledcWrite(1, 0);
      ledcWrite(0, 0);
      MoveF = map(C2, 1600, 2000, 60, 255);

      // v = ((C2 - 1600) * 0.4875) + 60;
      Serial.print(MoveF);
      ledcWrite(2, MoveF);
      ledcWrite(3, MoveF);

    }

    if (C2 <= 1400)
    { Serial.print("назад ");
      ledcWrite(2, 0);
      ledcWrite(3, 0);
      MoveD = map(C2, 1400, 1000, 60, 255);
      // z = ((1400 - C2) * 0.4875) + 60;
      Serial.println(MoveF);
      ledcWrite(1, MoveD);
      ledcWrite(0, MoveD);
    }

    //разворот налево
    if ((C0 <= 1450) && (C2 > 1400) && (C2 < 1600))
    {
      Serial.println("разворот налево");
      ledcWrite(2, 0);
      ledcWrite(3, 0);
      TurnLeft = map(C0, 1450, 1000, 60, 255);
      ledcWrite(0, TurnLeft);
      ledcWrite(3, TurnLeft);

    }


    //разворот направо
    if ((C0 >= 1550) && (C2 > 1400) && (C2 < 1600))
    {
      Serial.println("разворот направо");
      ledcWrite(0, 0);
      ledcWrite(3, 0);
      TurnRight = map(C0, 1550, 2000, 60, 255);
      ledcWrite(1, TurnRight);
      ledcWrite(2, TurnRight);

    }
      

    // прямо и направо
    if ((C2 > 1600) && (C0 > 1550))
    {
      Serial.println("прямо и направо");
      ledcWrite(2, 0);
      ledcWrite(3, 0);
      //MTL1 = map(C0,1450,1000,60,200);
      MTR2 = map(C2, 1600, 2000, 60, 255);
      MTR1 = (MTR2 / 2);
      ledcWrite(1, MTR2);
      ledcWrite(0, MTR1);

    }

    // назад и налево
    if ((C2 < 1400) && (C0 < 1450))
    {
      Serial.println("назад и налево");
      ledcWrite(0, 0);
      ledcWrite(1, 0);
      //MTL1 = map(C0,1450,1000,60,200);
      MDTL2 = map(C2, 1400, 1000, 60, 255);
      MDTL1 = (MDTL2 / 2);
      ledcWrite(2, MDTL2);
      ledcWrite(3, MDTL1);

    }

    // назад и направо
    if ((C2 < 1400) && (C0 > 1550))
    {
      Serial.println("назад и направо");
      ledcWrite(0, 0);
      ledcWrite(1, 0);
      //MTL1 = map(C0,1450,1000,60,200);
      MDTR2 = map(C2, 1400, 1000, 60, 255);
      MDTR1 = (MTR2 / 2);
      ledcWrite(2, MDTR1);
      ledcWrite(3, MDTR2);

    }

    digitalWrite(kick, LOW);
    if (C4 > 1800) {
      Serial.println("кик");
      digitalWrite(kick, HIGH);
      delay(200);
      digitalWrite(kick, LOW);
      delay(200);
    }

    if ((C2 > 1400) && (C2 < 1600) && (C0 > 1450) && (C0 < 1550))
    {
      Serial.println("Стоп");
      ledcWrite(2, 0);
      ledcWrite(3, 0);
      ledcWrite(0, 0);
      ledcWrite(1, 0);
      digitalWrite(kick, LOW);
    }

    Serial.print("Ch1  "); Serial.println(C0, DEC);
    Serial.print("Ch2  "); Serial.println(C1, DEC);
    Serial.print("Ch3  "); Serial.println(C2, DEC);
    Serial.print("Ch4  "); Serial.println(C3, DEC);
    Serial.print("Ch5  "); Serial.println(C4, DEC);
    Serial.print("Ch6  "); Serial.println(C5, DEC);
    Serial.println("==================================================");
    delay(10);
}
else
{
      Serial.println("Стоп");
      ledcWrite(2, 0);
      ledcWrite(3, 0);
      ledcWrite(0, 0);
      ledcWrite(1, 0);
      digitalWrite(kick, LOW);
    }


  }
}





 
   /* if ((C3 >= 1550) && (C3 < 1600) && (C3 > 1400))
    {
      Serial.println("направо");
      ledcWrite(1, 0);
      ledcWrite(0, 0);
      //n = map(C3, 1550, 2000, 60, 255);
      //nn = map(C3, 1550, 2000, 255, 60);
      n = (((C3 - 1550)*0.433) + 60);
      // n2 = 255 - n +60;
      //Serial.print("n"); Serial.println(n);
      //Serial.print("n2 ");Serial.println(n2);
      ledcWrite(2, nn); //n1   2 канал - правое колесо
      ledcWrite(3, n); //n2  3 канал  - левое
    }

    if (C3 <= 1450)
      { Serial.println("налево ");
        ledcWrite(0, 0);
        ledcWrite(1, 0);
        n2 = ((1450 - C3) * 0.433) + 60;
       // Serial.println(l1); Serial.println(l2);
        ledcWrite(2, n2);
        ledcWrite(3, 70);
      }


      if((C3<1450)&&(C3>1000)&&(C2>1600)&&(C2<2000))
      { 
        ledcWrite(0, 0);
        ledcWrite(1, 0);
        d = map(C3, 1450, 1000, 60, 200);
        dd = map(C2, 1600, 200, 60, 255);
        ledcWrite(2, dd);
        ledcWrite(3, d);
      }

    /*  if (C3<=1450 && C2>= 1600)
      {
        Serial.println("налево вверх");
        ledcWrite(1, 0);
        ledcWrite(0, 0);
        l1 = ((1450 - C3) * 0.433) + 60; //2 канал
        l2 = ((C2 - 1600) * 0.4875) + 60;
        Serial.println(l1); Serial.println(l2);

       // n = (((C3 - 1550)*0.433) + 60);
       // n2 = 255 - n +60;
       //Serial.print("n"); Serial.println(n);
       //Serial.print("n2 ");Serial.println(n2);
        ledcWrite(2, l1); //n1   2 канал - правое колесо
         ledcWrite(3, l2); //n2  3 канал  - левое
      }*/
