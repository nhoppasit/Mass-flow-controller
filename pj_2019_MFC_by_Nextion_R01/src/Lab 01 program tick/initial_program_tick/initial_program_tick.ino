// -----------------------------------
// CPU tick
// -----------------------------------
#define INTERVAL         50 // ms
unsigned long previousMillis;
boolean       tick_state;

// -----------------------------------
// Button Set
// -----------------------------------
#define IN_BUTTON 4 //เลือกขาของสวิตซ์
int val = 0;
int P;

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
   for(P=0;P<=255;P=P+5)
    {
     //analogWrite (13,255); //ให้ส่งสัญญาณพัลส์ที่มีความกว้างของสัญญาณพัลส์ 100% ซึ่งเป็นค่าสูงสุด ออกที่led ขา 13
     analogWrite (13,P);
     delay(50);
    }
  }
  else
  {
    analogWrite(13,0); //ให้ส่งสัญญาณพัลส์ที่มีความกว้างของสัญญาณพัลส์ 0% ออกที่led ขา 13
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
