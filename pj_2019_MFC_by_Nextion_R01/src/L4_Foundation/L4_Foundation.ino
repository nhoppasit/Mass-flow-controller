// -----------------------------------
// CPU tick
// -----------------------------------
#define INTERVAL         50 // ms
unsigned long previousMillis;
boolean       tick_state;

// -----------------------------------
// TASK BLINK
// -----------------------------------
#define TIME_BLINK     1000 // ms = 20 * 50ms ตั้งเวลา
int MY_TIME_BLINK = 1000;
boolean Blink = false; // ใช้จำสถานะไฟกระพริบ
int taskBlink_CNT; // จำเวลา [1,20] / C++[0,19]

// Serial command
char inBuff;






void setup() {
  Serial.begin(9600);
  delay(500);
  Serial1.begin(9600);
  delay(500);

  pinMode(13, OUTPUT);

  Serial.print("Hello");
  Serial1.print("Hello");

  digitalWrite(13, LOW);
}

void loop()
{
  ListenSerial1();
  tick();

  //Mission
  taskBlink(tick_state);
  //taskDAC(l.......);

}

void tick()
{
  tick_state = false;
  if (millis() - previousMillis > INTERVAL) //50ms  ___|^^^
  {
    previousMillis = millis();
    tick_state = true;
  }
}

// Serial command
void ListenSerial1()
{
  if (Serial1.available()) 
  {
    inBuff = Serial1.read();
    Serial.print(inBuff);

    //TODO
    if(inBuff=='1') MY_TIME_BLINK = 1000;
    if(inBuff=='2') MY_TIME_BLINK = 900;
    if(inBuff=='3') MY_TIME_BLINK = 800;
    if(inBuff=='4') MY_TIME_BLINK = 700;
    if(inBuff=='5') MY_TIME_BLINK = 600;
    if(inBuff=='6') MY_TIME_BLINK = 500;
    if(inBuff=='7') MY_TIME_BLINK = 400;
    if(inBuff=='8') MY_TIME_BLINK = 300;
    if(inBuff=='9') MY_TIME_BLINK = 200;
    if(inBuff=='0') MY_TIME_BLINK = 100;
      
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
    if (taskBlink_CNT >= MY_TIME_BLINK / INTERVAL) //1000ms/50ms = 20 counts ==> 1000 ms
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
