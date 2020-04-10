int RFwd=27; //вращение правого колеса назад 4(W2)
int RBwd=14; //вращение правого колеса вперед 16(W2)
int LFwd=13; //вращение левого колеса назад 2(W2)
int LBwd=12; //вращение левого колеса вперед 15(W2)
int left_sensor_line = 15;
int right_sensor_line = 2;
int ls;
int rs;
int  powerL;
int powerR;
float kp;
float kd;
float ki;
float iMin=-0.08;
float iMax=0.08;
float iSum=0;

float err;
float err_old;
int min_power; 
void setup() {
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

  pinMode(left_sensor_line, INPUT);
  pinMode(right_sensor_line, INPUT);
}

void loop() {
  ls = analogRead(left_sensor_line);
  rs = analogRead(right_sensor_line);
  kp=0.0069;
kd=0.01;
ki=0.001;
min_power =55;

err=((float)ls-(float)rs); 

iSum=iSum+err;
if(iSum<iMin)
{
  iSum=iMin;
}
if(iSum>iMax)
{
  iSum=iMax;
}
powerL=int((float)min_power-(kp*err+kd*(err-err_old)+ki*iSum));
powerR=int((float)min_power+(kp*err+kd*(err-err_old)+ki*iSum));
err_old= err;


ledcWrite(0,powerR);
ledcWrite(1,powerL);

}
