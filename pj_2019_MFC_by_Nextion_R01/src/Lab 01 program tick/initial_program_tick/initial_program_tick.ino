// -----------------------------------
// CPU tick
// -----------------------------------
#define INTERVAL         50 // ms
unsigned long previousMillis;
boolean       tick_state;

// -----------------------------------
// Button Set
// -----------------------------------
#define IN_BUTTON 4
int val = 0;

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
  pinMode(IN_BUTTON,INPUT);

}

void loop()
{
  tick();

  //Mission
  missionPrint(tick_state);
  taskBlink(tick_state);
  buttonSet(tick_state);

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
void buttonSet(boolean _flag)
{
  val = digitalRead (IN_BUTTON); //อ่านค่าvalueในinput
  if(val==HIGH) // เช็คinput เป็น High
  {
    analogWrite (13,255);  //analogWrite values from 0 to 255
  }
  else
  {
    analogWrite(13,64);
  }
}
// -----------------------------------
// TK01 = Blink
// -----------------------------------
void taskBlink(boolean _flag)
{
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
