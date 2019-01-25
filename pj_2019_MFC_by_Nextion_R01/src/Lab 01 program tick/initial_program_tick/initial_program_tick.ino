// -----------------------------------
// CPU tick
// -----------------------------------
#define INTERVAL         50 // ms
unsigned long previousMillis;
boolean       tick_state;
int button =12;

// -----------------------------------
// TASK BLINK
// -----------------------------------
#define TIME_BLINK     1000 // ms = 20 * 50ms ตั้งเวลา
boolean Blink = false; // ใช้จำสถานะไฟกระพริบ
int taskBlink_CNT; // จำเวลา [1,20] / C++[0,19]

// ---------------------------------
// Mission Print
// ---------------------------------
#define TIME_PRINT    2000
int missionPrint_CNT;

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT); // put your setup code here, to run once:
  pinMode(12,INPUT_PULLUP);

}

void loop()
{
  tick();

  //Mission
  missionPrint(tick_state);
  taskBlink(tick_state);


  delay(1);
}

// ================================= PROCEDURES =========================================
// -----------------------------------
// Program Tick
// -----------------------------------
void tick()
{
  tick_state = false;
  if (millis() - previousMillis > INTERVAL) //50ms  ___|^^^
  {
    previousMillis = millis();
    tick_state = true;
  }
}

// -----------------------------------
// TK01 = Blink
// -----------------------------------
void taskBlink(boolean _flag)
{
  if(digitalRead(button)==0){
  if (_flag)
  {
    taskBlink_CNT++;
    if (taskBlink_CNT >= TIME_BLINK / INTERVAL) //1000ms/50ms = 20 counts ==> 1000 ms
    {
      taskBlink_CNT = 0; // Reset counter <--

      // led Mission
      if (!Blink)
      {
        //LED ON
        digitalWrite(13, HIGH);
        Blink = true;
      }
      else
      {
        //LED OFF
        digitalWrite(13, LOW);
        Blink = false;
      }
    }
  }
}
}

void missionPrint(boolean _flag)
{
  if (_flag)
  {
    missionPrint_CNT++;

    if (TIME_PRINT/INTERVAL <= missionPrint_CNT)
    {
      missionPrint_CNT = 0;

      Serial.println("HI");
    }
  }
}
