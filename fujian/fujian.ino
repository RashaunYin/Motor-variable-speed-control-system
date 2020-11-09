#define BLINKER_PRINT Serial
#define BLINKER_WIFI

#include <Blinker.h>

char auth[] = "ec94ee6b0197";
char ssid[] = "Blinker";
char pswd[] = "576893124";

BlinkerButton Button1("btn-tan");   //启动
BlinkerButton Stop("btn-ajc");      //关闭
BlinkerButton Plus("btn-46d");      //加速
BlinkerButton Reduce("btn-jic");    //减速
BlinkerSlider Slider1("ran-wlx");   //速度滑块调节
BlinkerNumber Speed("num-xaw");     //转速显示

int DIR = 2;
int PUL = 14;
int n =2000;

void Plus_callback(const String & state)
{
  BLINKER_LOG("get button state: ", state);
  n=n+1;
  Speed.print(n);

  Serial.print("电机转速：");
  Serial.print(n);
  Serial.print(",");
  Serial.println("r/min");

  Blinker.vibrate();
  
  }

void Reduce_callback(const String & state)
{
  BLINKER_LOG("get button state: ", state);

  n=n-1;
  if(n<0)
    {
      n=0;
      Serial.print("ERROR");
      }

   Speed.print(n);

   Serial.print("电机转速：");
   Serial.print(n);
   Serial.print(",");
   Serial.println("r/min");

   Blinker.vibrate();
  }

void Stop_callback(const String & state)
{
  BLINKER_LOG("get button state: ", state);
  tone(PUL,0);
  n=0;
  Serial.print("电机停止");
  Blinker.vibrate();
  
  }

void Slider1_callback(int32_t value)
{
  BLINKER_LOG("get slider data: ", value);

  n=value;

  Speed.print(n);

  Serial.print("电机转速:");
  Serial.print(n);
  Serial.println("r/min");
  
  }


void setup() {
  pinMode(DIR, OUTPUT);
  
  Serial.begin(115200);

  Blinker.begin(auth, ssid, pswd);
  Stop.attach(Stop_callback);
  Plus.attach(Plus_callback);
  Reduce.attach(Reduce_callback);
  Slider1.attach(Slider1_callback);
  Speed.print(0);
  tone(PUL,n);

}


void loop() {
  Blinker.run();

  tone(PUL,n);
}
