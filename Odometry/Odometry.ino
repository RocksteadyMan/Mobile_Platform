
int RFwd=27; //вращение правого колеса назад 
int RBwd=14; //вращение правого колеса вперед 
int LFwd=13; //вращение левого колеса назад 
int LBwd=12; //вращение левого колеса вперед 
int PowerL;
int PowerR;
int EncoderLeft=34;
int EncoderRight=35;
int EncoderCount_L=0;
static byte pred_Cnt_L;
byte Cnt_L;

int EncoderCount_R=0;
static byte pred_Cnt_R;
byte Cnt_R;

float diameter=67;
float L=210.8;
float distance_cm;
float distance_cm_2; 
int Left=297;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
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
  pinMode(EncoderRight, INPUT);
  attachInterrupt(34, doEncoderL, CHANGE);
  attachInterrupt(35, doEncoderR, CHANGE);
}

void loop() { 
 /* ledcWrite(2,120);
  ledcWrite(3,120);*/
  if (PowerL==PowerR){
    distance_cm=(((float)EncoderCount_L/(float)297)*(float)210.8)/(float)10;
  Serial.println(distance_cm);
  delay(100);
  }
  if (PowerL!=PowerR){
    distance_cm+= ((float)210.8*((float)EncoderCount_L+(float)EncoderCount_R))/(float)297;  //при повороте создавать новый счетчик!!!!
  }
 /* delay(1000);
  ledcWrite(2,0);
  ledcWrite(3,0);*/
  
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
     //Serial.print("Cчетчик - ");
    // Serial.println(EncoderCount);
   } 
    
   void doEncoderR(void)
{
   pred_Cnt_R=0;
   Cnt_R= digitalRead(EncoderRight);
  // Serial.println(Cnt);
   if (Cnt_R!= pred_Cnt_R)
   {
     pred_Cnt_R=Cnt_R;
     EncoderCount_R++;
     //Serial.print("Cчетчик - ");
    // Serial.println(EncoderCount);
   }  
}






