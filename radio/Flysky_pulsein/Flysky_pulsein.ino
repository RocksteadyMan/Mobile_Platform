#define pinCanal1 13
#define pinCanal2 14
#define pinCanal3 27
#define pinCanal4 26

void setup() {
  Serial.begin(115200);
  pinMode(pinCanal1, INPUT);
  pinMode(pinCanal2, INPUT);
  pinMode(pinCanal3, INPUT);
  pinMode(pinCanal4, INPUT);
}
//============================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//============================================================================================================
void loop()
{
  long mic;
  mic = micros();
  long Canal1Time = pulseIn(pinCanal1, HIGH, 20000);
  long Canal2Time = pulseIn(pinCanal2, HIGH, 20000);
  long Canal3Time = pulseIn(pinCanal3, HIGH, 20000);
  long Canal4Time = pulseIn(pinCanal4, HIGH, 20000);
  mic = micros() - mic;
  Serial.print(mic); Serial.print(" = ");
  Serial.print(Canal1Time); Serial.print(" = ");
  Serial.print(Canal2Time); Serial.print(" = ");
  Serial.print(Canal3Time); Serial.print(" = ");
  Serial.print(Canal4Time); Serial.print(" || ");
  Serial.println("==========================================");
  delay(200);
}
