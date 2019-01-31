#define PRINT_NEXTION_COMMU 0

//##############################################################################
//                             DECLARATIONS
//##############################################################################
// ----------------------------------------------------------------------
// CPU tick
// ----------------------------------------------------------------------
#define INTERVAL         10 // ms
unsigned long previousMillis;
boolean       tick_state;

// ----------------------------------------------------------------------
// TASK BLINK
// ----------------------------------------------------------------------
#define TIME_BLINK     1000 // ms = 100 * 10ms ตั้งเวลา
int MY_TIME_BLINK = 1000;
boolean Blink = false; // ใช้จำสถานะไฟกระพริบ
int taskBlink_CNT; // จำเวลา [1,20] / C++[0,19]

// ----------------------------------------------------------------------
// Serial communication variables
// ----------------------------------------------------------------------
char incomingChar;
int byteIdx;
boolean nextionStxCome, nextionEtxCome;
byte dataBuff[6];


//##############################################################################
//                             SETUP
//##############################################################################
void setup() {
  Serial.begin(115200);
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
	// ............................
	// LISTEN & TICK
	// ............................
	listenNextion();
	tick();

	// ............................
	// TIME-BASED MISSIONS
	// ............................
	taskBlink(tick_state);

	// ............................
	// NEXTION MISSIONS
	// ............................
	taskIncBlinkPeriod(nextionEtxCome && dataBuff[1]==0x06 && dataBuff[2]==0x01);	
	taskDecBlinkPeriod(nextionEtxCome && dataBuff[1]==0x07 && dataBuff[2]==0x01);
	resetNextionEtxCome();	

}

//##############################################################################
//                             PROCEDURES OR FUNCTIONS
//##############################################################################
// ----------------------------------------------------------------------
// Tick --> update tick_state
// ----------------------------------------------------------------------
void tick()
{
  tick_state = false;
  if (millis() - previousMillis > INTERVAL) //50ms  ___|^^|_____10ms____|^^|___
  {
    previousMillis = millis();
    tick_state = true;
  }
}

// ----------------------------------------------------------------------
// Serial communication variables
// ----------------------------------------------------------------------
void listenNextion() 
{
  if (Serial1.available()) 
  {
    incomingChar = Serial1.read();

#if PRINT_NEXTION_COMMU	
	Serial.print("Incoming Char = ");
    Serial.println(incomingChar);
	Serial.print("Incoming Byte = ");
    Serial.println((byte)incomingChar, HEX);
#endif

	if(incomingChar==0x65) 
	{
		
		nextionStxCome = true;
		nextionEtxCome = false;
		byteIdx = 0;

#if PRINT_NEXTION_COMMU	
		Serial.println();
		Serial.println("STX Come........................."); 
		Serial.println("Reset ETX Come."); 
		Serial.println("Reset byte IDX to zero."); 
		Serial.println();
#endif
		
		return;
	}
	
	if(nextionStxCome)
	{
		dataBuff[byteIdx] = (byte)incomingChar;		

#if PRINT_NEXTION_COMMU	
		Serial.print("Data stored at byte IDX = "); 
		Serial.println(byteIdx, DEC);				
		Serial.println();
#endif
	}
	
	if(byteIdx==5)
	{
		if(dataBuff[3]==0xFF && dataBuff[4]==0xFF && dataBuff[5]==0xFF)
		{
			nextionEtxCome = true;

#if PRINT_NEXTION_COMMU	
			Serial.println("ETX Come........................."); 
			Serial.println();
#endif
		}
	}
	
	byteIdx++;
	if(5<byteIdx) byteIdx=5;

  }
}

// ----------------------------------------------------------------------
// Task resetNextionEtxCome
// ----------------------------------------------------------------------
void resetNextionEtxCome()
{
	if(nextionEtxCome)
	{
		nextionEtxCome = false;
		Serial.println("Reset ETX. Command expired.");
		Serial.println();
	}	
}

// ----------------------------------------------------------------------
// Task Blink
// ----------------------------------------------------------------------
void taskBlink(boolean _flag)
{
  if (_flag)
  {
    taskBlink_CNT++;
    if ((MY_TIME_BLINK / INTERVAL) <= taskBlink_CNT) //1000ms/10ms = 100 counts ==> 1000 ms
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

// ----------------------------------------------------------------------
// Task เพิ่มคาบเวลาในการ Blink
// ----------------------------------------------------------------------
void taskIncBlinkPeriod(boolean _flag)
{
	if(_flag)
	{
		MY_TIME_BLINK = MY_TIME_BLINK + 50;
		if(2000<MY_TIME_BLINK) MY_TIME_BLINK = 2000;
		Serial.print("Increase MY_TIME_BLINK to ");
		Serial.print(MY_TIME_BLINK, DEC);
		Serial.println();
	}
}

// ----------------------------------------------------------------------
// Task ลดคาบเวลาในการ Blink
// ----------------------------------------------------------------------
void taskDecBlinkPeriod(boolean _flag)
{
	if(_flag)
	{
		MY_TIME_BLINK = MY_TIME_BLINK - 50;
		if(MY_TIME_BLINK<50) MY_TIME_BLINK = 50;
		Serial.print("Decrease MY_TIME_BLINK to ");
		Serial.print(MY_TIME_BLINK, DEC);
		Serial.println();
	}
}

