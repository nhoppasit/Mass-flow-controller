//##############################################################################
//                             DECLARATIONS
//##############################################################################
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

// -----------------------------------
// Serial communication variables
// -----------------------------------
char incomingChar;
int byteIdx;
boolean stxCome;
byte inBuff[4];


//##############################################################################
//                             SETUP
//##############################################################################
void setup() {
  Serial.begin(9600);
  delay(500);
  Serial1.begin(9600);
  delay(500);

  pinMode(13, OUTPUT);

  Serial.print("Software started. Hello PC.");
  
  Serial1.print("Hello for test if you are Docklight.");

  digitalWrite(13, LOW);
}

//##############################################################################
//                             LOOP
//##############################################################################
void loop()
{
  listenNextion();
  tick();

  //Mission
  taskBlink(tick_state);
  //taskDAC(l.......);

}

//##############################################################################
//                             PROCEDURES OR FUNCTIONS
//##############################################################################
// -----------------------------------
// Tick --> update tick_state
// -----------------------------------
void tick()
{
  tick_state = false;
  if (millis() - previousMillis > INTERVAL) //50ms  ___|^^|_50ms__|^^|___
  {
    previousMillis = millis();
    tick_state = true;
  }
}

// -----------------------------------
// Serial communication variables
// -----------------------------------
void listenNextion() 
{
  if (Serial1.available()) 
  {
    incomingChar = Serial1.read();
	
    Serial.print(incomingChar);

	if(incomingChar==0x65) 
	{
		Serial.println();
		
		stxCome = true;
		Serial.println("STX Come."); 
		
		byteIdx = 0;
		Serial.print("Byte IDX = "); 
		
	}
      
  }
}

// -----------------------------------
// Task Blink
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
