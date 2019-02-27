#include <cmath>
int sensor[] = {PA0, PA1, PA2, PA3};
float average = 0;
float sum = 0;
float prod = 0;
float val[4];
float pos;
float setpoint = 2.5;
int ki=0, kd=0, kp=0;
int lastkp;
int error;
int proportional=5, integral=0.1, derivative=12;
float position1;
//float round(float x);
void setup()
{
  Serial.begin(9600);// turn on serial monitor
}

void loop()
{
  PID1();
  //readSensor();
}
float readSensor()
{
  sum = 0;
  prod = 0;
  for (int i = 0; i < 4; i++)
  {
    val[i] = analogRead(sensor[i]);//reading value of sensors
    Serial.print(val[i]);
    Serial.print("\t");
  }

  for (int i = 1; i <= 4; i++) {
    sum += val[i - 1];
    prod += i * val[i - 1];
  }
 
  position1 = prod / sum;
  //return (position1);
  Serial.print(position1);
  Serial.print("\t");
}

void PID1()
{ 
  pos = readSensor();
  //Serial.print(pos);
  Serial.print("\t");
  kp = pos - setpoint;// finding value of propotional
  Serial.print(kp);
  Serial.print("\t");
  ki = ki - kp;// value of integral
  kd = kp - lastkp;// derivative value
  lastkp = kp;
  error = (proportional * kp + integral * ki + derivative * kd);//finding the error value
  Serial.println(error);
}
void turn()
{
  if (error < -256) //all values below -256 to be read as -256
  {
    error = -256;
  }
  if (error > 256) // all values above 256 to be read as 256
  {
    error = 256;
  }
}
