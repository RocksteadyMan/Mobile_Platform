
int TRIGGER_PIN1=15;   // Вывод1 Trig подключен к 15-у порту (перед)
int ECHO_PIN1=2;     // Вывод1 Echo подключен к 2-у порту (перед)
int TRIGGER_PIN2=25;   // Вывод1 Trig подключен к 25-у порту (левая сторона)
int ECHO_PIN2=26;      // Вывод1 Echo подключен к 26-у порту (левая сторона)
int TRIGGER_PIN3=4 ;  // Вывод1 Trig подключен к 4-у порту (правая сторона)
int ECHO_PIN3=5;      // Вывод1 Echo подключен к 5-у порту (правая сторона)

int RFwd=27; //вращение правого колеса назад
int RBwd=14; //вращение правого колеса вперед 
int LFwd=13; //вращение левого колеса назад 
int LBwd=12; //вращение левого колеса вперед 

int EncoderLeft=34;
int EncoderCount_L=0;
static byte pred_Cnt_L;
byte Cnt_L;

void setup() {
  Serial.begin(115200); 

  pinMode(TRIGGER_PIN1, OUTPUT); 
  pinMode(ECHO_PIN1, INPUT);
        
  pinMode(TRIGGER_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);       
        
  pinMode(TRIGGER_PIN3, OUTPUT);
  pinMode(ECHO_PIN3, INPUT);
  
  pinMode (RFwd, OUTPUT);
  ledcSetup(0,500,8);
  ledcAttachPin(RFwd, 0);
  
  pinMode (LFwd, OUTPUT);
  ledcSetup(1,500,8);
  ledcAttachPin(LFwd, 1);
  
  pinMode (RBwd, OUTPUT);
  ledcSetup(2,500,8);
  ledcAttachPin(RBwd, 2);
  pinMode (LBwd, OUTPUT);
  ledcSetup(3,500,8);
  ledcAttachPin(LBwd, 3);

  pinMode(EncoderLeft, INPUT);
  attachInterrupt(34, doEncoderL, CHANGE);
  delay(500);

}

void loop() {

long distance_front, distance_right, distance_left, duration_front, duration_right, duration_left, distance_front_old;

//distance_front_old = distance_front;

//start:
digitalWrite(TRIGGER_PIN1, LOW);
delayMicroseconds(2);
digitalWrite(TRIGGER_PIN1, HIGH);
delayMicroseconds(5);
digitalWrite(TRIGGER_PIN1, LOW);
duration_front = pulseIn(ECHO_PIN1, HIGH);
//delay((15000-duration_front)/1000); 
distance_front = duration_front/29/2;

//if (distance_front-distance_front_old>=40)
//{
  //goto start;
//}

digitalWrite(TRIGGER_PIN2, LOW);
delayMicroseconds(2);
digitalWrite(TRIGGER_PIN2, HIGH);
delayMicroseconds(5);
digitalWrite(TRIGGER_PIN2, LOW);
duration_right = pulseIn(ECHO_PIN2, HIGH);
//delay((15000-duration_right)/1000); 
distance_right = duration_right/29/2;

digitalWrite(TRIGGER_PIN3, LOW);
delayMicroseconds(2);
digitalWrite(TRIGGER_PIN3, HIGH);
delayMicroseconds(5);
digitalWrite(TRIGGER_PIN3, LOW);
duration_left = pulseIn(ECHO_PIN3, HIGH);
//delay((15000-duration_left)/1000); 
distance_left = duration_left/29/2;

Serial.print("Перед  ");
Serial.print(distance_front);
Serial.print(" Справа ");
Serial.print(distance_right);
Serial.print(" Слева ");
Serial.println(distance_left);

ledcWrite(0,0);
ledcWrite(1,0);
ledcWrite(2,0);
ledcWrite(3,0);



  //delay(100);
 /* Serial.print("Перед  ");
  Serial.println(sonar1.ping_cm());
  Serial.print("Справа ");
  Serial.println(sonar2.ping_cm());
  Serial.print("Слева ");
  Serial.println(sonar3.ping_cm());*/
  // 0 - левое назад
  // 1 - правое назад
  // 2 - левое вперед
  // 3 - правое вперед 
 if(distance_left==0 && distance_right==0 && distance_front==0)
{
  ledcWrite(0,0);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
  
}

 if (distance_front>13)
 {
  if (distance_right>4 && distance_right<8)
  { Serial.println("Вперед");
    ledcWrite(2,65); //72
    ledcWrite(3,65);
  }
  if (distance_right>=8)
  {
    Serial.println("Вперед и вправо");
    ledcWrite(2,80); //75
    ledcWrite(3,60);
  }
  if (distance_right<=4)
  {
    Serial.println("Вперед и влево");
    ledcWrite(2,60);
    ledcWrite(3,80); //80
  }
 }
//if (distance_right<=3 && distance_left>10 &&distance_front<=10) nazad1();
//if (distance_left<=3 && distance_right>16 &&distance_front<=10) nazad2();
if (distance_left<=21 && distance_left>3 && distance_right>16 && distance_front<=13) dir();
if (distance_left>16 && distance_right>16 && distance_front<=13) dir();
if (distance_right<16 && distance_right>3 && distance_left>16 && distance_front<=13) left();
if (distance_right<=16&& distance_right!=0 && distance_left<=16 && distance_front<=13) back();
}

void doEncoderL(void)
{
   pred_Cnt_L=0;
   Cnt_L= digitalRead(EncoderLeft);
  // Serial.println(Cnt);
   
   if (Cnt_L!= pred_Cnt_L)
   { 
     pred_Cnt_L=Cnt_L;
     EncoderCount_L++;
    
    // Serial.print("Cчетчик - ");
   // Serial.println(EncoderCount_L);
   }
} 

void dir()  // поворот на 90 вправо
{ ledcWrite(0,0);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
  //delay(1000);
  
  EncoderCount_L=0;
while (EncoderCount_L<140)   //155
{
  ledcWrite(2,65);
  ledcWrite(1,65);
}
  ledcWrite(2,0);
  ledcWrite(1,0);
 // delay(1000);
}

void left() // поворот на 90 влево
{
  ledcWrite(0,0);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
 // delay(1000);
  
  EncoderCount_L=0;
while (EncoderCount_L<200)  //155
{
  ledcWrite(3,65);
  ledcWrite(0,65);
}
  ledcWrite(3,0);
  ledcWrite(0,0);
  //delay(1000);
}

void back() // поворот на 180 (вправо)
{
  ledcWrite(0,0);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
 // delay(1000);
  
  EncoderCount_L=0;
while (EncoderCount_L<345) //310
{
  ledcWrite(2,65);
  ledcWrite(1,65);
}
  ledcWrite(2,0);
  ledcWrite(1,0);
  //delay(1000);
}


/*void nazad1()
{ ledcWrite(0,0);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
  delay(1000);
  ledcWrite(1,90);
  ledcWrite(0,60);
  delay(500);
  ledcWrite(1,60);
  ledcWrite(0,90);
  delay(300);
  ledcWrite(0,0);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
}*/


/*

void nazad2()
{ ledcWrite(0,0);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
  delay(1000);
  ledcWrite(0,90);
  ledcWrite(1,60);
  delay(500);
  ledcWrite(0,60);
  ledcWrite(1,90);
  delay(300);
  ledcWrite(0,0);
  ledcWrite(1,0);
  ledcWrite(2,0);
  ledcWrite(3,0);
}
*/
