#define PRINT_NEXTION_COMMU 1

//##############################################################################
//                             DECLARATIONS
//##############################################################################
#include "NextionHardware.h";
#include "NextionText.h";

// ----------------------------------------------------------------------
// CPU tick
// ----------------------------------------------------------------------
#define INTERVAL         10 // ms เป็นการกำหนดค่าคงที่
unsigned long previousMillis; //การเก็บตัวเลขที่เป็นจำนวนเต็ม ที่ชื่อ previousMillis
boolean       tick_state;  //แสดงสถานะที่เป็นเท็จหรือจริง

// ----------------------------------------------------------------------
// TASK BLINK
// ----------------------------------------------------------------------
#define TIME_BLINK     1000 // ms = 100 * 10ms ตั้งเวลา
int MY_TIME_BLINK = 1000; //หน่วยความจำ
boolean Blink = false; // ใช้จำสถานะไฟกระพริบ
int taskBlink_CNT; // จำเวลา [1,20] / C++[0,19]

// ----------------------------------------------------------------------
// Serial communication variables
// ----------------------------------------------------------------------
char incomingChar;//หน่วยความจำ
int byteIdx;
boolean nextionStxCome, nextionEtxCome;
byte dataBuff[6];

// ----------------------------------------------------------------------
// Nextion variables
// ----------------------------------------------------------------------
char buffer[100] = {0};

//##############################################################################
//                             SETUP
//##############################################################################
void setup() {

  systemInit();

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
  taskIncBlinkPeriod(nextionEtxCome && dataBuff[0] == 0x01 && dataBuff[1] == 0x02 && dataBuff[2] == 0x00);
  taskDecBlinkPeriod(nextionEtxCome && dataBuff[0] == 0x02 && dataBuff[1] == 0x02 && dataBuff[2] == 0x00);

  checkScaling(nextionEtxCome && dataBuff[0] == 0x06 && dataBuff[1] == 0x05 && dataBuff[2] == 0x00); // 65 06 05 00 FF FF FF

  resetNextionEtxCome();

}

void checkScaling(boolean _flag)
{
  if (_flag)
  {
    Serial.println();
    Serial.println("Ask entry scale.");

    memset(buffer, 0, sizeof(buffer));
    getText("t61", buffer, sizeof(buffer));
		
		callPage("3");
		
		setText("t21","Hi");
		
		
    Serial.println("End ask.");
  }
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

//##############################################################################
//                             NEXTION PROCEDURES AND FUNCTIONS
//##############################################################################
// ----------------------------------------------------------------------
// Serial communication variables
// ----------------------------------------------------------------------
void listenNextion()
{
  if (Serial1.available())  //ได้รับข้อมูลจากสายarduino
  {
    incomingChar = Serial1.read(); //อ่านหน่วยความจำที่Serial1

#if PRINT_NEXTION_COMMU
    Serial.print("Incoming Char = "); //ปริ๊นข้อความใน"" (Char = ประกาศตัวแปรชนิดอักษร)
    Serial.println(incomingChar); //เว้นบรรทัด
    Serial.print("Incoming Byte = "); //ปริ๊นข้อความใน"" หน่วยByte
    Serial.println((byte)incomingChar, HEX); //เว้นบรรทัดแล้วปริ๊นออกมาเป็นค่าHex

#endif

    if (incomingChar == 0x65) //ถ้าคีย์ข้อมูลค่า65

    {

      nextionStxCome = true;     //nextionStxCome จะเป็นจริง (Stx=Start TexT)
      nextionEtxCome = false;    //nextionEtxCome จะเป็นเท็จ (Etx=End TexT)
      byteIdx = 0;

#if PRINT_NEXTION_COMMU
      Serial.println();  //ให้เว้นบรรทัด
      Serial.println("STX Come........................."); //จะปริ๊นค่าใน"" แล้วขึ้นบรรทัดใหม่
      Serial.println("Reset ETX Come.");  //จะปริ๊นค่าใน""
      Serial.println("Reset byte IDX to zero."); //จะปริ๊นค่าใน""
      Serial.println();  //ให้เว้นบรรทัด
#endif

      return;
    }

    if (nextionStxCome) //ถ้าnextionStxComeเป็นจริง
    {
      dataBuff[byteIdx] = (byte)incomingChar; //เก็บ


#if PRINT_NEXTION_COMMU
      Serial.print("Data stored at byte IDX = ");
      Serial.println(byteIdx, DEC);
      Serial.println();
#endif
    }

    if (byteIdx == 5) //เก็บแค่5
    {
      if (dataBuff[3] == 0xFF && dataBuff[4] == 0xFF && dataBuff[5] == 0xFF) //check FF 3ตัว
      {
        nextionEtxCome = true; //nextionEtxCome เป็นจริง

#if PRINT_NEXTION_COMMU
        Serial.println("ETX Come.........................");
        Serial.println();
#endif
      }
    }

    byteIdx++;
    if (5 < byteIdx) byteIdx = 5;

  }
}

// ----------------------------------------------------------------------
// Task resetNextionEtxCome
// ----------------------------------------------------------------------
void resetNextionEtxCome()
{
  if (nextionEtxCome)
  {
    nextionEtxCome = false;
    Serial.println("Reset ETX. Command expired."); //ปริ๊นข้อความใน""
    Serial.println();
  }
}

//##############################################################################
//                             PROCEDURES OR FUNCTIONS
//##############################################################################
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
  if (_flag)
  {
    MY_TIME_BLINK = MY_TIME_BLINK + 50; //อัพเดตหน่วยความจำ
    if (2000 < MY_TIME_BLINK) MY_TIME_BLINK = 2000; //ถ้าหน่วยความจำมากกว่า 2000
    Serial.print("Increase MY_TIME_BLINK to "); //ให้ปริ๊นข้อความใน""
    Serial.print(MY_TIME_BLINK, DEC);  //ให้ไฟกระพริบ
    Serial.println();
  }
}

// ----------------------------------------------------------------------
// Task ลดคาบเวลาในการ Blink
// ----------------------------------------------------------------------
void taskDecBlinkPeriod(boolean _flag)
{
  if (_flag)
  {
    MY_TIME_BLINK = MY_TIME_BLINK - 50; //อัพเดตหน่วยความจำ
    if (MY_TIME_BLINK < 50) MY_TIME_BLINK = 50; //ถ้าหน่วยความจำน้อยกว่า 50
    Serial.print("Decrease MY_TIME_BLINK to ");  //ให้ปริ๊นข้อความใน""
    Serial.print(MY_TIME_BLINK, DEC); //ให้ไฟกระพริบ
    Serial.println();
  }
}
