#define PRINT_NEXTION_COMMU 1
#define PRINT_DEBUG 1

//##############################################################################
//                             DECLARATIONS
//##############################################################################

#include "NextionHardware.h";
#include "NextionText.h";

#include "MCP4922.h"
#include <SPI.h>

MCP4922 DAC_A(51, 52, 34, 2); // (MOSI/SDI,SCK,CS,LDAC) define Connections for MEGA_board
MCP4922 DAC_B(51, 52, 53, 2); // (MOSI/SDI,SCK,CS,LDAC) define Connections for MEGA_board

// ----------------------------------------------------------------------
// Set Timing
// ----------------------------------------------------------------------
int led = 12; // กำหนดขาled ที่pin 12
float timer; // ใช้ในการเก็บค่า ที่ชื่อ timer
int state;  // ใช้การเก็บค่าที่ชื่อ state
int stateValue1; // ใช้การเก็บค่าที่ชื่อ stateValue1
int stateValue2; // ใช้การเก็บค่าที่ชื่อ stateValue2
int stateValue3; // ใช้การเก็บค่าที่ชื่อ stateValue3
int stateValue4; // ใช้การเก็บค่าที่ชื่อ stateValue4
unsigned long T_LED = 0; //การเก็บค่าตัวเลขที่เป็นจำนวนเต็มที่ชื่อ T_LED
unsigned long Showvalue1 ; //การเก็บค่าตัวเลขที่เป็นจำนวนเต็มที่ชื่อ Showvalue1
unsigned long Showvalue2 ; //การเก็บค่าตัวเลขที่เป็นจำนวนเต็มที่ชื่อ Showvalue2
unsigned long Showvalue3 ; //การเก็บค่าตัวเลขที่เป็นจำนวนเต็มที่ชื่อ Showvalue3
unsigned long Showvalue4 ; //การเก็บค่าตัวเลขที่เป็นจำนวนเต็มที่ชื่อ Showvalue4
boolean BlinkLED1 = false; // ใช้จำสถานะBlinkLED1
boolean TimingLED1 = false; //ใช้จำสถานะTimingLED1
boolean ADC1 = false; //ใช้จำสถานะADC1

boolean BlinkLED2 = false; // ใช้จำสถานะBlinkLED2
boolean TimingLED2 = false; //ใช้จำสถานะTimingLED2
boolean ADC2 = false; //ใช้จำสถานะADC2

boolean BlinkLED3 = false; // ใช้จำสถานะBlinkLED3
boolean TimingLED3 = false; //ใช้จำสถานะTimingLED3
boolean ADC3 = false; //ใช้จำสถานะADC3

boolean BlinkLED4 = false; // ใช้จำสถานะBlinkLED4
boolean TimingLED4 = false; //ใช้จำสถานะTimingLED4
boolean ADC4 = false; //ใช้จำสถานะADC4

char hr[100] = {0}; //ให้ hr เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
float led_hr;  // ใช้การเก็บค่าตัวเลขที่ชื่อ led_hr
float len_hr; // ใช้การเก็บค่าตัวเลขที่ชื่อ len_hr
int ihr;  // ใช้การเก็บค่าตัวเลขที่ชื่อ ihr

char min[100] = {0}; //ให้ min เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
float led_min; // ใช้การเก็บค่าตัวเลขที่ชื่อ led_min
float len_min; // ใช้การเก็บค่าตัวเลขที่ชื่อ len_min
int imin;  // ใช้การเก็บค่าตัวเลขที่ชื่อ imin

char sec[100] = {0}; //ให้ sec เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
float led_sec; // ใช้การเก็บค่าตัวเลขที่ชื่อ led_sec
float len_sec; // ใช้การเก็บค่าตัวเลขที่ชื่อ len_sec
int isec;  //  ใช้การเก็บค่าตัวเลขที่ชื่อ isec

// ----------------------------------------------------------------------
// Channel 1
// ----------------------------------------------------------------------
float Vout_1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ Vout_1
float Vout_sccm_FS_1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ Vout_sccm_FS_1
float Vout_sccm_SP_1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ Vout_sccm_SP_1
float FSN1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ FSN1 (Full Scale New 1)
float SPN1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ SPN1 (Set Point New 1)
float Flowrate1, Flowout1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ Flowrate1 และ Flowout1
float FS1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ FS1 (Full Scale 1)
float SP1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ SP1 (Set Point 1)
float GF1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ GF1 (Type of gas 1)
float GM1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ GM1 (Gas of massflow 1)
float A; //  ใช้การเก็บค่าตัวเลขที่ชื่อ A
float B; //  ใช้การเก็บค่าตัวเลขที่ชื่อ B
int analogValue1 = 0; //  ใช้การเก็บค่าตัวเลขที่ชื่อ analogValue1
int analogValue11 = 0; //  ใช้การเก็บค่าตัวเลขที่ชื่อ analogValue11

// ----------------------------------------------------------------------
// Channel 2
// ----------------------------------------------------------------------
float Vout_2; //  ใช้การเก็บค่าตัวเลขที่ชื่อ Vout_2
float Vout_sccm_FS_2; //  ใช้การเก็บค่าตัวเลขที่ชื่อ Vout_sccm_FS_2
float Vout_sccm_SP_2; //  ใช้การเก็บค่าตัวเลขที่ชื่อ Vout_sccm_FS_2
float FSN2; //  ใช้การเก็บค่าตัวเลขที่ชื่อ FSN2 (Full Scale New 2)
float SPN2; //  ใช้การเก็บค่าตัวเลขที่ชื่อ SPN2 (Set Point New 2)
float Flowrate2, Flowout2; //  ใช้การเก็บค่าตัวเลขที่ชื่อ Flowrate2 และ Flowout2
float FS2; //  ใช้การเก็บค่าตัวเลขที่ชื่อ FS2 (Full Scale 2)
float SP2; //  ใช้การเก็บค่าตัวเลขที่ชื่อ  SP2 (Set Point 2)
float GF2; //  ใช้การเก็บค่าตัวเลขที่ชื่อ GF2 (Type of gas 2)
float GM2; //  ใช้การเก็บค่าตัวเลขที่ชื่อ  GM2 (Gas of massflow 2)
float C; //  ใช้การเก็บค่าตัวเลขที่ชื่อ C
float D; //  ใช้การเก็บค่าตัวเลขที่ชื่อ D
int analogValue2 = 0; //  ใช้การเก็บค่าตัวเลขที่ชื่อ analogValue2
int analogValue22 = 0; //  ใช้การเก็บค่าตัวเลขที่ชื่อ analogValue22

// ----------------------------------------------------------------------
// Channel 3
// ----------------------------------------------------------------------
float Vout_3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ Vout_3
float Vout_sccm_FS_3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ Vout_sccm_FS_3
float Vout_sccm_SP_3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ Vout_sccm_SP_3
float FSN3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ FSN3 (Full Scale New 3)
float SPN3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ SPN3 (Set Point New 3)
float Flowrate3, Flowout3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ Flowrate3 และ Flowout3
float FS3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ FS3 (Full Scale 3)
float SP3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ SP3 (Set Point 3)
float GF3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ GF3 (Type of gas 3)
float GM3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ GM3 (Gas of massflow 3)
float E; //  ใช้การเก็บค่าตัวเลขที่ชื่อ E
float F; //  ใช้การเก็บค่าตัวเลขที่ชื่อ F
int analogValue3 = 0; //  ใช้การเก็บค่าตัวเลขที่ชื่อ analogValue3
int analogValue33 = 0; //  ใช้การเก็บค่าตัวเลขที่ชื่อ analogValue33

// ----------------------------------------------------------------------
// Channel 4
// ----------------------------------------------------------------------
float Vout_4; //  ใช้การเก็บค่าตัวเลขที่ชื่อ Vout_4
float Vout_sccm_FS_4; //  ใช้การเก็บค่าตัวเลขที่ชื่อ Vout_sccm_FS_4
float Vout_sccm_SP_4; //  ใช้การเก็บค่าตัวเลขที่ชื่อ Vout_sccm_SP_4
float FSN4; //  ใช้การเก็บค่าตัวเลขที่ชื่อ FSN4 (Full Scale New 4)
float SPN4; //  ใช้การเก็บค่าตัวเลขที่ชื่อ SPN4 (Set Point New 4)
float Flowrate4, Flowout4; //  ใช้การเก็บค่าตัวเลขที่ชื่อ Flowrate4 และ Flowout4
float FS4; //  ใช้การเก็บค่าตัวเลขที่ชื่อ FS4 (Full Scale 4)
float SP4; //  ใช้การเก็บค่าตัวเลขที่ชื่อ SP4 (Set Point 4)
float GF4; //  ใช้การเก็บค่าตัวเลขที่ชื่อ GF4 (Type of gas 4)
float GM4; //  ใช้การเก็บค่าตัวเลขที่ชื่อ GM4 (Gas of massflow 4)
float G; //  ใช้การเก็บค่าตัวเลขที่ชื่อ G
float H; //  ใช้การเก็บค่าตัวเลขที่ชื่อ H
int analogValue4 = 0; //  ใช้การเก็บค่าตัวเลขที่ชื่อ analogValue4
int analogValue44 = 0; //  ใช้การเก็บค่าตัวเลขที่ชื่อ analogValue44

// ----------------------------------------------------------------------
// CPU tick
// ----------------------------------------------------------------------
#define INTERVAL         10 // ms เป็นการกำหนดค่าคงที่ define เป็นคำสั่งแทนข้อความเมื่อ INTERVAL ปรากฏในโปรแกรมส่วนจะเท่ากับ 10 ms
unsigned long previousMillis; //การเก็บตัวเลขที่เป็นจำนวนเต็ม ที่ชื่อ previousMillis
boolean       tick_state;  //แสดงสถานะที่เป็นเท็จหรือจริง

// ----------------------------------------------------------------------
// TASK BLINK
// ----------------------------------------------------------------------
#define TIME_BLINK     1000 // ms = 100 * 10ms ตั้งเวลา
//int MY_TIME_BLINK = 1000; //หน่วยความจำ
int MY_TIME_BLINK = 500; // เป็นหน่วยความจำที่กำหนดให้  MY_TIME_BLINK = 500
boolean Blink = false; // ใช้จำสถานะไฟกระพริบ
int taskBlink_CNT; // จำเวลา [1,20] / C++[0,19]

//int TIME_ADC1 = 500;
int taskADC1_CNT;
int taskADC2_CNT;
int taskADC3_CNT;
int taskADC4_CNT;
//boolean ADC1 = false;
// ----------------------------------------------------------------------
// Serial communication variables
// ----------------------------------------------------------------------
char incomingChar;//หน่วยความจำ
int byteIdx; //  ใช้การเก็บค่าตัวเลขที่ชื่อ byteIdx
boolean nextionStxCome, nextionEtxCome;
byte dataBuff[6];

// ----------------------------------------------------------------------
// Nextion variables ch1
// ----------------------------------------------------------------------
char buffer[100] = {0}; //ให้ buffer เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
int len_buff;  //  ใช้การเก็บค่าตัวเลขที่ชื่อ len_buff
int ibuff;  //  ใช้การเก็บค่าตัวเลขที่ชื่อ ibuff
char buffer1[100] = {0}; //ให้ buffer1 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
int len_buff1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ len_buff1
int ibuff1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ ibuff1

char number[100] ; //ให้ number เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
int len_num; //  ใช้การเก็บค่าตัวเลขที่ชื่อ len_num
int inum; //  ใช้การเก็บค่าตัวเลขที่ชื่อ inum
char number1[100] ; //ให้ number1 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
int len_num1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ len_num1
int inum1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ inum1

// ----------------------------------------------------------------------
// Nextion variables ch2
// ----------------------------------------------------------------------
char buffer2[100] = {0}; //ให้ buffer2 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
int len_buff2;  //  ใช้การเก็บค่าตัวเลขที่ชื่อ len_buff2
int ibuff2;  //  ใช้การเก็บค่าตัวเลขที่ชื่อ ibuff2
char buffer3[100] = {0}; //ให้ buffer3 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
int len_buff3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ len_buff3
int ibuff3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ ibuff3

char number2[100] ; //ให้ number2 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
int len_num2; //  ใช้การเก็บค่าตัวเลขที่ชื่อ len_num2
int inum2; //  ใช้การเก็บค่าตัวเลขที่ชื่อ inum2
char number3[100] ; //ให้ number3 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
int len_num3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ len_num3
int inum3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ inum3

// ----------------------------------------------------------------------
// Nextion variables ch3
// ----------------------------------------------------------------------
char buffer4[100] = {0}; //ให้ buffer4 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
int len_buff4;  //  ใช้การเก็บค่าตัวเลขที่ชื่อ len_buff4
int ibuff4;  //  ใช้การเก็บค่าตัวเลขที่ชื่อ ibuff4
char buffer5[100] = {0}; //ให้ buffer5 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
int len_buff5; //  ใช้การเก็บค่าตัวเลขที่ชื่อ len_buff5
int ibuff5; //  ใช้การเก็บค่าตัวเลขที่ชื่อ ibuff5

char number4[100] ; //ให้ number4 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
int len_num4; //  ใช้การเก็บค่าตัวเลขที่ชื่อ len_num4
int inum4; //  ใช้การเก็บค่าตัวเลขที่ชื่อ inum4
char number5[100] ; //ให้ number5 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
int len_num5; //  ใช้การเก็บค่าตัวเลขที่ชื่อ len_num5
int inum5; //  ใช้การเก็บค่าตัวเลขที่ชื่อ inum5

// ----------------------------------------------------------------------
// Nextion variables ch4
// ----------------------------------------------------------------------
char buffer6[100] = {0}; //ให้ buffer6 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
int len_buff6;  //  ใช้การเก็บค่าตัวเลขที่ชื่อ len_buff6
int ibuff6;  //  ใช้การเก็บค่าตัวเลขที่ชื่อ ibuff6
char buffer7[100] = {0}; //ให้ buffer7 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
int len_buff7; //  ใช้การเก็บค่าตัวเลขที่ชื่อ len_buff7
int ibuff7; //  ใช้การเก็บค่าตัวเลขที่ชื่อ ibuff7

char number6[100] ; //ให้ number6 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
int len_num6; //  ใช้การเก็บค่าตัวเลขที่ชื่อ len_num6
int inum6; //  ใช้การเก็บค่าตัวเลขที่ชื่อ inum6
char number7[100] ; //ให้ number7 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[100]ตัว
int len_num7; //  ใช้การเก็บค่าตัวเลขที่ชื่อ len_num7
int inum7; //  ใช้การเก็บค่าตัวเลขที่ชื่อ inum7

// ----------------------------------------------------------------------
// Show Text After Massflow Process
// ----------------------------------------------------------------------
float V_ch1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ V_ch1
float VtoSccm_1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ VtoSccm_1
char sbuff1[8]; //ให้ sbuff1 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[8]ตัว
double MassflowtoNextion1 ; //  ใช้การเก็บค่าตัวเลขที่ชื่อ MassflowtoNextion1
String value1; //  ใช้การเก็บค่าตัวเลขที่ชื่อ value1

float V_ch2; //  ใช้การเก็บค่าตัวเลขที่ชื่อ V_ch2
float VtoSccm_2; //  ใช้การเก็บค่าตัวเลขที่ชื่อ VtoSccm_2
char sbuff2[8];//ให้ sbuff2 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[8]ตัว
double MassflowtoNextion2 ; //  ใช้การเก็บค่าตัวเลขที่ชื่อ MassflowtoNextion2
String value2; //  ใช้การเก็บค่าตัวเลขที่ชื่อ value2

float V_ch3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ V_ch3
float VtoSccm_3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ VtoSccm_3
char sbuff3[8];//ให้ sbuff3 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[8]ตัว
double MassflowtoNextion3 = 20; //  ใช้การเก็บค่าตัวเลขที่ชื่อ MassflowtoNextion3
String value3; //  ใช้การเก็บค่าตัวเลขที่ชื่อ value3

float V_ch4; //  ใช้การเก็บค่าตัวเลขที่ชื่อ V_ch4
float VtoSccm_4; //  ใช้การเก็บค่าตัวเลขที่ชื่อ VtoSccm_4
char sbuff4[8];//ให้ sbuff4 เก็บข้อมูลเป็นbyteในcharเก็บตัวเลข[8]ตัว
double MassflowtoNextion4 = 20; //  ใช้การเก็บค่าตัวเลขที่ชื่อ MassflowtoNextion4
String value4; //  ใช้การเก็บค่าตัวเลขที่ชื่อ value4

// ----------------------------------------------------------------------
// Select Voltage
// ----------------------------------------------------------------------
int pin1_24v = 4; // กำหนดrelayที่ชื่อ pin1_24v ที่ขา 4
int pin2_24v = 5; // กำหนดrelayที่ชื่อ pin2_24v ที่ขา 5
int pin3_24v = 6; // กำหนดrelayที่ชื่อ pin3_24v ที่ขา 6
int pin4_24v = 7; // กำหนดrelayที่ชื่อ pin4_24v ที่ขา 7


//##############################################################################
//                             SETUP
//##############################################################################
void setup() {

  systemInit();

  Serial.print("Software started. Hello PC.");

  pinMode(13, OUTPUT); //ส่งสํญญาณ ให้ออกที่ขา13
  digitalWrite(13, LOW);  //ให้เอาต์พุตขา13 เป็นลอจิก 0

  Serial.begin(115200); //กำหนดอัตราบอดของการรับส่งข้อมูล 115200บิตต่อวินาที่  set baud rate to 115200
  pinMode(led, OUTPUT); //ส่งสํญญาณให้ออกที่ขาของled
  SPI.begin();

  pinMode(A1, INPUT); //รับข้อมูลให้ส่งมายังขาของA1
  pinMode(A2, INPUT); //รับข้อมูลให้ส่งมายังขาของA2
  pinMode(A3, INPUT); //รับข้อมูลให้ส่งมายังขาของA3
  pinMode(A4, INPUT); //รับข้อมูลให้ส่งมายังขาของA4

  pinMode(pin1_24v, OUTPUT); //ส่งสํญญาณให้ออกที่ขาของpin1_24v
  pinMode(pin2_24v, OUTPUT); //ส่งสํญญาณให้ออกที่ขาของpin2_24v
  pinMode(pin3_24v, OUTPUT); //ส่งสํญญาณให้ออกที่ขาของpin3_24v
  pinMode(pin4_24v, OUTPUT); //ส่งสํญญาณให้ออกที่ขาของpin4_24v

}
void voltage1(unsigned int A)
{
  DAC_A.Set(A, C); //เซ็ตค่าdacของchannel1
}
void voltage2(unsigned int C)
{
  DAC_A.Set(A, C); //เซ็ตค่าdacของchannel2
}
void voltage3(unsigned int E)
{
  DAC_B.Set(E, G); //เซ็ตค่าdacของchannel3
}
void voltage4(unsigned int G)
{
  DAC_B.Set(E, G); //เซ็ตค่าdacของchannel4
}
//##############################################################################
//                             LOOP
//##############################################################################
void loop()
{
  // ............................
  // LISTEN & TICK
  // ............................
  listenNextion(); //ฟังก์ชันlistenNextion
  tick(); //ฟังก์ชัน tick

  // ............................
  // NEXTION MISSIONS
  // ............................  
  Check12Voltch1(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x1F && dataBuff[1] == 0x02 && dataBuff[2] == 0x01); // 65 1F 02 01 FF FF FF set relay 12v ch1
  Check12Voltch2(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x20 && dataBuff[1] == 0x02 && dataBuff[2] == 0x01); // 65 20 02 01 FF FF FF set relay 12v ch2
  Check12Voltch3(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x21 && dataBuff[1] == 0x02 && dataBuff[2] == 0x01); // 65 21 02 01 FF FF FF set relay 12v ch3
  Check12Voltch4(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x22 && dataBuff[1] == 0x02 && dataBuff[2] == 0x01); // 65 22 02 01 FF FF FF set relay 12v ch4

  Check24Voltch1(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x1F && dataBuff[1] == 0x03 && dataBuff[2] == 0x01); // 65 1F 03 01 FF FF FF set relay 24v ch1
  Check24Voltch2(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x20 && dataBuff[1] == 0x03 && dataBuff[2] == 0x01); // 65 20 03 01 FF FF FF set relay 24v ch2
  Check24Voltch3(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x21 && dataBuff[1] == 0x03 && dataBuff[2] == 0x01); // 65 21 03 01 FF FF FF set relay 24v ch3
  Check24Voltch4(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x22 && dataBuff[1] == 0x03 && dataBuff[2] == 0x01); // 65 22 03 01 FF FF FF set relay 24v ch4

  // ............................
  // CHECK STRAT
  // ............................
  checkChannel1(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x16 && dataBuff[1] == 0x0C && dataBuff[2] == 0x00); // 65 16 0C 00 FF FF FF ปุ่ม start ตรวจสอบค่า FullScale and SetPoint ch1
  checkChannel2(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x16 && dataBuff[1] == 0x0F && dataBuff[2] == 0x00); // 65 16 0F 00 FF FF FF ปุ่ม start ตรวจสอบค่า FullScale and SetPoint ch2
  checkChannel3(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x16 && dataBuff[1] == 0x12 && dataBuff[2] == 0x00); // 65 16 12 00 FF FF FF ปุ่ม start ตรวจสอบค่า FullScale and SetPoint ch3
  checkChannel4(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x16 && dataBuff[1] == 0x15 && dataBuff[2] == 0x00); // 65 16 15 00 FF FF FF ปุ่ม start ตรวจสอบค่า FullScale and SetPoint ch4

  // ............................
  // CHECK STOP
  // ............................
  checkSTOP1(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x16 && dataBuff[1] == 0x0D && dataBuff[2] == 0x00); // 65 16 0D 00 FF FF FF ปุ่ม stop ch1
  checkSTOP2(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x16 && dataBuff[1] == 0x10 && dataBuff[2] == 0x00); // 65 16 10 00 FF FF FF ปุ่ม stop ch2
  checkSTOP3(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x16 && dataBuff[1] == 0x13 && dataBuff[2] == 0x00); // 65 16 13 00 FF FF FF ปุ่ม stop ch3
  checkSTOP4(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x16 && dataBuff[1] == 0x16 && dataBuff[2] == 0x00); // 65 16 16 00 FF FF FF ปุ่ม stop ch4

  // ............................
  // TIME-BASED MISSIONS
  // ............................
  taskBlink(tick_state); //ฟังก์ชันtaskBlink

  taskStart1(tick_state && TimingLED1); //ฟังก์ชันtaskStart1
  taskStart2(tick_state && TimingLED2); //ฟังก์ชันtaskStart2
  taskStart3(tick_state && TimingLED3); //ฟังก์ชันtaskStart3
  taskStart4(tick_state && TimingLED4); //ฟังก์ชันtaskStart4

  taskOnOff1(tick_state && BlinkLED1); //ฟังก์ชันtaskOnOff1
  taskOnOff2(tick_state && BlinkLED2); //ฟังก์ชันtaskOnOff2
  taskOnOff3(tick_state && BlinkLED3); //ฟังก์ชันtaskOnOff3
  taskOnOff4(tick_state && BlinkLED4); //ฟังก์ชันtaskOnOff4

  taskMeasureFlow1(tick_state && ADC1); //ฟังก์ชันtaskMeasureFlow1
  taskMeasureFlow2(tick_state && ADC2); //ฟังก์ชันtaskMeasureFlow2
  taskMeasureFlow3(tick_state && ADC3); //ฟังก์ชันtaskMeasureFlow3
  taskMeasureFlow4(tick_state && ADC4); //ฟังก์ชันtaskMeasureFlow4

  // ............................
  // TIMING MISSIONS
  // ............................
  TimingStart1(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x23 && dataBuff[1] == 0x05 && dataBuff[2] == 0x00); // 65 23 05 00 FF FF FF ปุ่ม start ch1
  TimingStart2(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x24 && dataBuff[1] == 0x05 && dataBuff[2] == 0x00); // 65 24 05 00 FF FF FF ปุ่ม start ch2
  TimingStart3(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x25 && dataBuff[1] == 0x05 && dataBuff[2] == 0x00); // 65 25 05 00 FF FF FF ปุ่ม start ch3
  TimingStart4(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x26 && dataBuff[1] == 0x05 && dataBuff[2] == 0x00); // 65 26 05 00 FF FF FF ปุ่ม start ch4

  TimingStartONOFF1(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x23 && dataBuff[1] == 0x08 && dataBuff[2] == 0x00); // 65 23 08 00 FF FF FF ปุ่ม start On/Off ch1
  TimingStartONOFF2(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x24 && dataBuff[1] == 0x08 && dataBuff[2] == 0x00); // 65 24 08 00 FF FF FF ปุ่ม start On/Off ch2
  TimingStartONOFF3(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x25 && dataBuff[1] == 0x08 && dataBuff[2] == 0x00); // 65 25 08 00 FF FF FF ปุ่ม start On/Off ch3
  TimingStartONOFF4(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x26 && dataBuff[1] == 0x08 && dataBuff[2] == 0x00); // 65 26 08 00 FF FF FF ปุ่ม start On/Off ch4

  TimingStop1(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x23 && dataBuff[1] == 0x06 && dataBuff[2] == 0x00); // 65 23 06 00 FF FF FF ปุ่ม stop ch1
  TimingStop2(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x24 && dataBuff[1] == 0x06 && dataBuff[2] == 0x00); // 65 24 06 00 FF FF FF ปุ่ม stop ch2
  TimingStop3(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x25 && dataBuff[1] == 0x06 && dataBuff[2] == 0x00); // 65 25 06 00 FF FF FF ปุ่ม stop ch3
  TimingStop4(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x26 && dataBuff[1] == 0x06 && dataBuff[2] == 0x00); // 65 26 06 00 FF FF FF ปุ่ม stop ch4

  resetNextionEtxCome(); //ฟังก์ชัน resetNextionEtxCome
}
// ----------------------------------------------------------------------
//  Check 12 Voltage
// ----------------------------------------------------------------------
void Check12Voltch1 (boolean _flag) //ฟังก์ชันcheck12Voltch1
{
  if (_flag)
  {
    digitalWrite(pin1_24v, LOW); //ให้เอาต์พุตขาของpin1_24v เป็นลอจิก 0 หรือมีสัญญาณไฟ 12 โวลต์
  }
}
void Check12Voltch2 (boolean _flag) //ฟังก์ชันcheck12Voltch2
{
  if (_flag)
  {
    digitalWrite(pin2_24v, LOW); //ให้เอาต์พุตขาของpin2_24v เป็นลอจิก 0 หรือมีสัญญาณไฟ 12 โวลต์
  }
}
void Check12Voltch3 (boolean _flag) //ฟังก์ชันcheck12Voltch3
{
  if (_flag)
  {
    digitalWrite(pin3_24v, LOW); //ให้เอาต์พุตขาของpin3_24v เป็นลอจิก 0 หรือมีสัญญาณไฟ 12 โวลต์
  }
}
void Check12Voltch4 (boolean _flag) //ฟังก์ชันcheck12Voltch4
{
  if (_flag)
  {
    digitalWrite(pin4_24v, LOW); //ให้เอาต์พุตขาของpin4_24v เป็นลอจิก 0 หรือมีสัญญาณไฟ 12 โวลต์
  }
}
// ----------------------------------------------------------------------
// Check 24 Voltage
// ----------------------------------------------------------------------
void Check24Voltch1 (boolean _flag) //ฟังก์ชันCheck24Voltch1
{
  if (_flag)
  {
    digitalWrite(pin1_24v, HIGH); //ให้เอาต์พุตขาของpin1_24v เป็นลอจิก 1 หรือมีสัญญาณไฟ 24 โวลต์
  }
}
void Check24Voltch2 (boolean _flag) //ฟังก์ชันCheck24Voltch2
{
  if (_flag)
  {
    digitalWrite(pin2_24v, HIGH); //ให้เอาต์พุตขาของpin2_24v เป็นลอจิก 1 หรือมีสัญญาณไฟ 24 โวลต์
  }
}
void Check24Voltch3 (boolean _flag) //ฟังก์ชันCheck24Voltch3
{
  if (_flag)
  {
    digitalWrite(pin3_24v, HIGH); //ให้เอาต์พุตขาของpin3_24v เป็นลอจิก 1 หรือมีสัญญาณไฟ 24 โวลต์
  }
}
void Check24Voltch4 (boolean _flag) //ฟังก์ชันCheck24Voltch4
{
  if (_flag)
  {
    digitalWrite(pin4_24v, HIGH); //ให้เอาต์พุตขาของpin4_24v เป็นลอจิก 1 หรือมีสัญญาณไฟ 24 โวลต์
  }
}
// ----------------------------------------------------------------------
//  Timing
// ----------------------------------------------------------------------
void taskStart1 (boolean _flag)
{
  if (_flag)
  {
    if (millis() > T_LED) //ถ้าmills()มีค่ามากกว่าT_LED
    {
      T_LED = timer + millis(); //โดยทุกๆtimer(เวลาที่กำหนด)  โปรแกรมจะส่งสัญญาณHIGH เกิดเป็นไฟLEDติดที่ขา12 ตามเวลาที่กำหนด และดับลดเมื่อส่งสัญญาณLOWตอนที่หมดเวลา 
      //Serial.println(T_LED);
      //Serial.print("T_LED: ");
      state = !state ;
      if (state == 1)
      {
        A = ( 4095 * SPN1 ) / FSN1 ;
        voltage1(A); //Set DAC voltage
        digitalWrite(led, HIGH);
        Serial.println("LED : ON");
      }
      else
      {
        ADC1 = false;
        A = 0;
        voltage1(A); //Set DAC voltage
        T_LED = 0;
        state = 0;
        TimingLED1 = false; 
        setText("t350", "0"); //โชว์ข้อความ"0" ในTextboxที่t350 
        setText("t351", "0"); //โชว์ข้อความ"0" ในTextboxที่t351
        setText("t352", "0"); //โชว์ข้อความ"0" ในTextboxที่t352
        setText("t353", "0"); //โชว์ข้อความ"0" ในTextboxที่t353
        digitalWrite(led, LOW);
        Serial.println("LED : OFF");
      }
    }
  }
}
void taskStart2 (boolean _flag)
{
  if (_flag)
  {
    if (millis() > T_LED) //ถ้าmills()มีค่ามากกว่าT_LED
    {
      T_LED = timer + millis(); //โดยทุกๆtimer(เวลาที่กำหนด)  โปรแกรมจะส่งสัญญาณHIGH เกิดเป็นไฟLEDติดที่ขา12 ตามเวลาที่กำหนด และดับลดเมื่อส่งสัญญาณLOWตอนที่หมดเวลา 
      Serial.println(T_LED);
      Serial.print("T_LED: ");
      state = !state ;
      if (state == 1)
      {
        C = ( 4095 * SPN2 ) / FSN2 ;
        voltage2(C); //Set DAC voltage
        digitalWrite(led, HIGH);
        Serial.println("LED : ON");
      }
      else
      {
        ADC2 = false;
        C = 0 ;
        voltage2(C); //Set DAC voltage
        T_LED = 0;
        state = 0;
        TimingLED2 = false;
        setText("t360", "0"); //โชว์ข้อความ"0" ในTextboxที่t360
        setText("t361", "0"); //โชว์ข้อความ"0" ในTextboxที่t361
        setText("t362", "0"); //โชว์ข้อความ"0" ในTextboxที่t362
        setText("t363", "0"); //โชว์ข้อความ"0" ในTextboxที่t363
        digitalWrite(led, LOW);
        Serial.println("LED : OFF");
      }
    }
  }
}
void taskStart3 (boolean _flag)
{
  if (_flag)
  {
    if (millis() > T_LED) //ถ้าmills()มีค่ามากกว่าT_LED
    {
      T_LED = timer + millis(); //โดยทุกๆtimer(เวลาที่กำหนด)  โปรแกรมจะส่งสัญญาณHIGH เกิดเป็นไฟLEDติดที่ขา12 ตามเวลาที่กำหนด และดับลดเมื่อส่งสัญญาณLOWตอนที่หมดเวลา 
	  Serial.println(T_LED);
      Serial.print("T_LED: ");
      state = !state ;
      if (state == 1)
      {
        E = ( 4095 * SPN3 ) / FSN3 ;
        voltage3(E);//Set DAC voltage
        digitalWrite(led, HIGH);
        Serial.println("LED : ON");
      }
      else
      {
        ADC3 = false;
        E = 0;
        voltage3(E); //Set DAC voltage
        T_LED = 0;
        state = 0;
        TimingLED3 = false;
        setText("t370", "0"); //โชว์ข้อความ"0" ในTextboxที่t370
        setText("t371", "0"); //โชว์ข้อความ"0" ในTextboxที่t371
        setText("t372", "0"); //โชว์ข้อความ"0" ในTextboxที่t372
        setText("t373", "0"); //โชว์ข้อความ"0" ในTextboxที่t373
        digitalWrite(led, LOW);
        Serial.println("LED : OFF");
      }
    }
  }
}
void taskStart4 (boolean _flag)
{
  if (_flag)
  {
    if (millis() > T_LED) //ถ้าmills()มีค่ามากกว่าT_LED
    {
      T_LED = timer + millis(); //โดยทุกๆtimer(เวลาที่กำหนด)  โปรแกรมจะส่งสัญญาณHIGH เกิดเป็นไฟLEDติดที่ขา12 ตามเวลาที่กำหนด และดับลดเมื่อส่งสัญญาณLOWตอนที่หมดเวลา 
      Serial.println(T_LED);
      Serial.print("T_LED: ");
      state = !state ;
      if (state == 1)
      {
        G = ( 4095 * SPN4 ) / FSN4 ;
        voltage4(G); //Set DAC voltage
        digitalWrite(led, HIGH);
        Serial.println("LED : ON");
      }
      else
      {
        ADC4 = false;
        G = 0;
        voltage4(G); //Set DAC voltage
        T_LED = 0;
        state = 0;
        TimingLED4 = false;
        setText("t380", "0"); //โชว์ข้อความ"0" ในTextboxที่t380
        setText("t381", "0"); //โชว์ข้อความ"0" ในTextboxที่t381
        setText("t382", "0"); //โชว์ข้อความ"0" ในTextboxที่t382
        setText("t383", "0"); //โชว์ข้อความ"0" ในTextboxที่t383
        digitalWrite(led, LOW);
        Serial.println("LED : OFF");
      }
    }
  }
}
void taskOnOff1 (boolean _flag)
{
  if (_flag)
  {
    if (millis() > T_LED) //ถ้าmills()มีค่ามากกว่าT_LED     
    {      
      T_LED = timer + millis(); //โดยทุกๆtimer(เวลาที่กำหนด)  โปรแกรมจะส่งสัญญาณHIGH และสัญญาณLOWสลับกัน เกิดเป็นไฟกระพริบที่ขา12 โดยค่าของ millis() จะเพิ่มค่าอัตโนมัติตามการรันโปรแกรม
      Serial.println(T_LED); 
      Serial.print("T_LED: ");
      state = !state ;
      if (state == 1)
      {
        A = ( 4095 * SPN1 ) / FSN1 ;
        voltage1(A); //Set DAC voltage
        digitalWrite(led, HIGH);
        Serial.println("LED : ON");
      }
      else
      {
        A = 0;
        voltage1(A); //Set DAC voltage
        digitalWrite(led, LOW);
        Serial.println("LED : OFF");
      }
    }
  }
}
void taskOnOff2 (boolean _flag)
{
  if (_flag)
  {
    if (millis() > T_LED) //ถ้าmills()มีค่ามากกว่าT_LED
    {
      T_LED = timer + millis(); //โดยทุกๆtimer(เวลาที่กำหนด)  โปรแกรมจะส่งสัญญาณHIGH และสัญญาณLOWสลับกัน เกิดเป็นไฟกระพริบที่ขา12 โดยค่าของ millis() จะเพิ่มค่าอัตโนมัติตามการรันโปรแกรม
      Serial.println(T_LED);
      Serial.print("T_LED: ");
      state = !state ;
      if (state == 1)
      {
        C = ( 4095 * SPN2 ) / FSN2 ;
        voltage2(C); //Set DAC voltage
        digitalWrite(led, HIGH);
        Serial.println("LED : ON");
      }
      else
      {
        C = 0;
        voltage2(C);
        digitalWrite(led, LOW);
        Serial.println("LED : OFF");
      }
    }
  }
}
void taskOnOff3 (boolean _flag)
{
  if (_flag)
  {
    if (millis() > T_LED) //ถ้าmills()มีค่ามากกว่าT_LED
    {
      T_LED = timer + millis(); //โดยทุกๆtimer(เวลาที่กำหนด)  โปรแกรมจะส่งสัญญาณHIGH และสัญญาณLOWสลับกัน เกิดเป็นไฟกระพริบที่ขา12 โดยค่าของ millis() จะเพิ่มค่าอัตโนมัติตามการรันโปรแกรม
      Serial.println(T_LED);
      Serial.print("T_LED: ");
      state = !state ;
      if (state == 1)
      {
        E = ( 4095 * SPN3 ) / FSN3 ;
        voltage3(E);//Set DAC voltage
        digitalWrite(led, HIGH);
        Serial.println("LED : ON");
      }
      else
      {
        E = 0;
        voltage3(E); //Set DAC voltage
        digitalWrite(led, LOW);
        Serial.println("LED : OFF");
      }
    }
  }
}
void taskOnOff4 (boolean _flag)
{
  if (_flag)
  {
    if (millis() > T_LED) //ถ้าmills()มีค่ามากกว่าT_LED
    {
      T_LED = timer + millis(); //โดยทุกๆtimer(เวลาที่กำหนด)  โปรแกรมจะส่งสัญญาณHIGH และสัญญาณLOWสลับกัน เกิดเป็นไฟกระพริบที่ขา12 โดยค่าของ millis() จะเพิ่มค่าอัตโนมัติตามการรันโปรแกรม
      Serial.println(T_LED);
      Serial.print("T_LED: ");
      state = !state ;
      if (state == 1)
      {
        G = ( 4095 * SPN4 ) / FSN4 ;
        voltage4(G); //Set DAC voltage
        digitalWrite(led, HIGH);
        Serial.println("LED : ON");
      }
      else
      {
        G = 0;
        voltage4(G); //Set DAC voltage
        digitalWrite(led, LOW);
        Serial.println("LED : OFF");
      }
    }
  }
}
void TimingStart1 (boolean _flag)
{
  if (_flag)
  {
    TimingLED1 = true; 
    memset(hr, 0, sizeof(hr));
    len_hr = getText("t350", hr, sizeof(hr)); //รับค่าจากTextbox"t350"มาโชว์ที่len_hr
    memset(min, 0, sizeof(min));
    len_min = getText("t351", min, sizeof(min)); //รับค่าจากTextbox"t351"มาโชว์ที่len_min
    memset(sec, 0, sizeof(sec));
    len_sec = getText("t352", sec, sizeof(sec)); //รับค่าจากTextbox"t352"มาโชว์ที่len_sec
    callPage("35"); 

#if PRINT_DEBUG
    Serial.print("Hr.[] = ");
    for (ihr = 0; ihr < len_hr; ihr++)
    {
      Serial.print(hr[ihr]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Min[] = ");
    for (imin = 0; imin < len_min; imin++)
    {
      Serial.print(min[imin]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Sec[] = ");
    for (isec = 0; isec < len_sec; isec++)
    {
      Serial.print(sec[isec]);
    }
    Serial.println();
#endif

    led_sec = atof(sec); //รับค่าsec มาเก็บไว้ที่led_sec
    Serial.print("led_sec = ");
    Serial.println(led_sec);

    led_min = atof(min); //รับค่าmin มาเก็บไว้ที่led_min
    Serial.print("led_min = ");
    Serial.println(led_min);

    led_hr = atof(hr); //รับค่าhr มาเก็บไว้ที่led_hr
    Serial.print("led_hr = ");
    Serial.println(led_hr);

    float timerhr = ( led_hr * 60000 ) * 60 ; //รับค่าled_hrมาคำนวณ แล้วเก็บค่าไว้ที่ timerhr
    Serial.print("timerhr = ");
    Serial.println(timerhr);

    float timermin =  led_min * 60000 ; //รับค่าled_minมาคำนวณ แล้วเก็บค่าไว้ที่ timermin
    Serial.print("timermin = ");
    Serial.println(timermin);

    float timersec = led_sec * 1000; //รับค่าled_secมาคำนวณ แล้วเก็บค่าไว้ที่ timersec
    Serial.print("timersec = ");
    Serial.println(timersec);

    timer = timerhr + timermin + timersec; //รับค่าtimerhr,timerminและ timersec มาคำนวณแล้วเก็บค่าไว้ที่timer
    Serial.print("timer = ");
    Serial.println(timer);

    // ----------------------------------------------------------------------
    // Receive data 
    // ----------------------------------------------------------------------
    callPage("2");
    memset(buffer, 0, sizeof(buffer));
    memset(buffer1, 0, sizeof(buffer1)); 
    len_buff = getText("t21", buffer, sizeof(buffer)); //รับค่าจากTextbox"t21"มาโชว์ที่len_buff
    len_buff1 = getText("t22", buffer1, sizeof(buffer1)); //รับค่าจากTextbox"t22"มาโชว์ที่len_buff1
    callPage("11");
    memset(number, 0, sizeof(number));
    memset(number1, 0, sizeof(number1));
    len_num = getText("t111", number, sizeof(number)); //รับค่าจากTextbox"t111"มาโชว์ที่len_num
    len_num1 = getText("t112", number1, sizeof(number1)); //รับค่าจากTextbox"t112"มาโชว์ที่len_num1

#if PRINT_DEBUG
    Serial.print("Buffer[] = ");
    for (ibuff = 0; ibuff < len_buff; ibuff++)
    {
      Serial.print(buffer[ibuff]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Buffer1[] = ");
    for (ibuff1 = 0; ibuff1 < len_buff1; ibuff1++)
    {
      Serial.print(buffer1[ibuff1]);
    }
    Serial.println();
#endif

#if PRINT_DEBUG
    Serial.print("Number[] = ");
    for (inum = 0; inum < len_num; inum++)
    {
      Serial.print(number[inum]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Number1[] = ");
    for (inum1 = 0; inum1 < len_num1; inum1++)
    {
      Serial.print(number1[inum1]);
    }
    Serial.println();
#endif

    // ----------------------------------------------------------------------
    //  Set Value
    // ----------------------------------------------------------------------
    String S = String(buffer);
    Serial.print("S = ");
    Serial.println(S);

    if (S == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GM1 = 0.993;
      Serial.print("GM1 = ");
      Serial.println(GM1, 3);
    }
    else if (S == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GM1 = 1.39;
      Serial.print("GM1 = ");
      Serial.println(GM1);
    }
    else if (S == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GM1 = 1.00;
      Serial.print("GM1 = ");
      Serial.println(GM1);
    }
    else if (S == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GM1 = 1.01;
      Serial.print("GM1 = ");
      Serial.println(GM1);
    }
    else
    {
      GM1 = atof(buffer); //รับค่าbuffer มาเก็บไว้ที่GM1
      Serial.print("GM1 = ");
      Serial.println(GM1, 3);
    }

    String T = String(buffer1);
    Serial.print("T = ");
    Serial.println(T);

    if (T == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GF1 = 0.993;
      Serial.print("GF1 = ");
      Serial.println(GF1, 3);
    }
    else if (T == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GF1 = 1.39;
      Serial.print("GF1 = ");
      Serial.println(GF1);
    }
    else if (T == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GF1 = 1.00;
      Serial.print("GF1 = ");
      Serial.println(GF1);
    }
    else if (T == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GF1 = 1.01;
      Serial.print("GF1 = ");
      Serial.println(GF1);
    }
    else
    {
      GF1 = atof(buffer1); //รับค่าbuffer1 มาเก็บไว้ที่GF1
      Serial.print("GF1 = ");
      Serial.println(GF1, 3);
    }

    FS1 = atof(number); //รับค่าnumber มาเก็บไว้ทีFS1
    Serial.print("FS1 = ");
    Serial.println(FS1);

   // SP1 = 0;
    SP1 = atof(number1); //รับค่าnumber1 มาเก็บไว้ทีSP1
    Serial.print("SP1 = ");
    Serial.println(SP1);

    if (SP1 > FS1) //ถ้าSP1 มีค่ามากกว่า FS1 ให้โชว์หน้าที่27
    {
      callPage("27"); 
      A = 0;
      voltage1(A); //Set DAC voltage
      Serial.print("A = ");
      Serial.println(A);
    }
    else
    {
      callPage("35");

      // ----------------------------------------------------------------------
      // Part Calculate Channel 1
      // ----------------------------------------------------------------------
      FSN1 = ( GF1 / GM1 ) * FS1; //รับค่าGF1,GM1และFS1มาคำนวณ แล้วเก็บค่าไว้ที่FSN1
      Serial.print("FSN1(sccm) = ");
      Serial.println(FSN1);

      SPN1 = ( FSN1 / FS1 ) * SP1 ; //รับค่าFSN1,FS1และSP1มาคำนวณ แล้วเก็บค่าไว้ที่SPN1
      if (SPN1 > FSN1) //ถ้าSPN1 มีค่ามากกว่า FSN1 ให้ SPN1 = FSN1
      {
        SPN1 = FSN1;
      }
      Serial.print("SPN1 = ");
      Serial.println(SPN1);      
      A = ( 4095 * SPN1 ) / FSN1 ; //แปลงค่าSPN1ให้อยู่ในช่วง 0-4095 byte       
      voltage1(A); //เซ็ตค่าDAC Voltage1
      Serial.print("A = ");
      Serial.println(A, BIN);
      Serial.println(A);
      
      B = ( FSN1 * A ) / 4095 ; //แปลงช่วง 0-4095 ให้อยู่ในค่าFSN1
      Serial.print("B(sccm) = ");
      Serial.println(B);      
      Serial.println("_______________________________ END CHANNEL 1 _______________________________");
      Serial.println("End ask.");

      ADC1 = true;

    }
  }
}
void TimingStart2 (boolean _flag)
{
  if (_flag)
  {
    TimingLED2 = true;
    memset(hr, 0, sizeof(hr));
    len_hr = getText("t360", hr, sizeof(hr)); //รับค่าจากTextbox"t360"มาโชว์ที่len_hr
    memset(min, 0, sizeof(min));
    len_min = getText("t361", min, sizeof(min)); //รับค่าจากTextbox"t361"มาโชว์ที่len_min
    memset(sec, 0, sizeof(sec));
    len_sec = getText("t362", sec, sizeof(sec)); //รับค่าจากTextbox"t362"มาโชว์ที่len_sec
    callPage("36");

#if PRINT_DEBUG
    Serial.print("Hr.[] = ");
    for (ihr = 0; ihr < len_hr; ihr++)
    {
      Serial.print(hr[ihr]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Min[] = ");
    for (imin = 0; imin < len_min; imin++)
    {
      Serial.print(min[imin]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Sec[] = ");
    for (isec = 0; isec < len_sec; isec++)
    {
      Serial.print(sec[isec]);
    }
    Serial.println();
#endif

    led_sec = atof(sec); //รับค่าsec มาเก็บไว้ที่led_sec
    Serial.print("led_sec = ");
    Serial.println(led_sec);

    led_min = atof(min); //รับค่าmin มาเก็บไว้ที่led_min
    Serial.print("led_min = ");
    Serial.println(led_min);

    led_hr = atof(hr); //รับค่าhr มาเก็บไว้ที่led_hr
    Serial.print("led_hr = ");
    Serial.println(led_hr);

    float timerhr = ( led_hr * 60000 ) * 60 ; //รับค่าled_hrมาคำนวณ แล้วเก็บค่าไว้ที่ timerhr
    Serial.print("timerhr = ");
    Serial.println(timerhr);

    float timermin =  led_min * 60000 ; //รับค่าled_minมาคำนวณ แล้วเก็บค่าไว้ที่ timermin
    Serial.print("timermin = ");
    Serial.println(timermin);

    float timersec = led_sec * 1000; //รับค่าled_secมาคำนวณ แล้วเก็บค่าไว้ที่ timersec
    Serial.print("timersec = ");
    Serial.println(timersec);

    timer = timerhr + timermin + timersec;  //รับค่าtimerhr,timerminและ timersec มาคำนวณแล้วเก็บค่าไว้ที่timer
    Serial.print("timer = ");
    Serial.println(timer);

    // ----------------------------------------------------------------------
    // Channel 2
    // ----------------------------------------------------------------------
    callPage("3");
    memset(buffer2, 0, sizeof(buffer2));
    memset(buffer3, 0, sizeof(buffer3));
    len_buff2 = getText("t31", buffer2, sizeof(buffer2)); //รับค่าจากTextbox"t31"มาโชว์ที่len_buff2
    len_buff3 = getText("t32", buffer3, sizeof(buffer3)); //รับค่าจากTextbox"t32"มาโชว์ที่len_buff3
    callPage("12");
    memset(number2, 0, sizeof(number2));
    memset(number3, 0, sizeof(number3));
    len_num2 = getText("t121", number2, sizeof(number2)); //รับค่าจากTextbox"t121"มาโชว์ที่len_num2
    len_num3 = getText("t122", number3, sizeof(number3)); //รับค่าจากTextbox"t122"มาโชว์ที่len_num3

    // ----------------------------------------------------------------------
    // Channel 2
    // ----------------------------------------------------------------------

#if PRINT_DEBUG
    Serial.print("Buffer2[] = ");
    for (ibuff2 = 0; ibuff2 < len_buff2; ibuff2++)
    {
      Serial.print(buffer2[ibuff2]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Buffer3[] = ");
    for (ibuff3 = 0; ibuff3 < len_buff3; ibuff3++)
    {
      Serial.print(buffer3[ibuff3]);
    }
    Serial.println();
#endif

#if PRINT_DEBUG
    Serial.print("Number2[] = ");
    for (inum2 = 0; inum2 < len_num2; inum2++)
    {
      Serial.print(number2[inum2]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Number3[] = ");
    for (inum3 = 0; inum3 < len_num3; inum3++)
    {
      Serial.print(number3[inum3]);
    }
    Serial.println();
#endif

    // ----------------------------------------------------------------------
    // Channel 2
    // ----------------------------------------------------------------------

    String U = String(buffer2);
    Serial.print("U = ");
    Serial.println(U);

    if (U == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GM2 = 0.993;
      Serial.print("GM2 = ");
      Serial.println(GM2, 3);
    }
    else if (U == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GM2 = 1.39;
      Serial.print("GM2 = ");
      Serial.println(GM2);
    }
    else if (U == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GM2 = 1.00;
      Serial.print("GM2 = ");
      Serial.println(GM2);
    }
    else if (U == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GM2 = 1.01;
      Serial.print("GM2 = ");
      Serial.println(GM2);
    }
    else
    {
      GM2 = atof(buffer2); //รับค่าbuffer2 มาเก็บไว้ที่GM2
      Serial.print("GM2 = ");
      Serial.println(GM2, 3);
    }

    String V = String(buffer3);
    Serial.print("V = ");
    Serial.println(V);

    if (V == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GF2 = 0.993;
      Serial.print("GF2 = ");
      Serial.println(GF2, 3);
    }
    else if (V == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GF2 = 1.39;
      Serial.print("GF2 = ");
      Serial.println(GF2);
    }
    else if (V == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GF2 = 1.00;
      Serial.print("GF2 = ");
      Serial.println(GF2);
    }
    else if (V == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GF2 = 1.01;
      Serial.print("GF2 = ");
      Serial.println(GF2);
    }
    else
    {
      GF2 = atof(buffer3); //รับค่าbuffer3 มาเก็บไว้ที่GF2
      Serial.print("GF2 = ");
      Serial.println(GF2, 3);
    }

    FS2 = atof(number2);  //รับค่าnumber2 มาเก็บไว้ทีFS2
    Serial.print("FS2 = ");
    Serial.println(FS2, 4);

    SP2 = atof(number3); //รับค่าnumber3 มาเก็บไว้ทีSP2
    Serial.print("SP2 = ");
    Serial.println(SP2, 4);

    if (SP2 > FS2) //ถ้าSP1 มีค่ามากกว่า FS1 ให้โชว์หน้าที่28
    {
      callPage("28");
      C = 0;
      voltage2(C);   //Set DAC voltage
      Serial.print("C = ");
      Serial.println(C);
    }
    else
    {
      callPage("36");

      // ----------------------------------------------------------------------
      // Part Calculate Channel 2
      // ----------------------------------------------------------------------

      FSN2 = ( GF2 / GM2 ) * FS2  ;  //รับค่าGF2,GM2และFS2มาคำนวณ แล้วเก็บค่าไว้ที่FSN2
      Serial.print("FSN2(sccm) = ");
      Serial.println(FSN2);

      SPN2 = ( FSN2 / FS2 ) * SP2 ; //รับค่าFSN2,FS2และSP2มาคำนวณ แล้วเก็บค่าไว้ที่SPN2
      if (SPN2 > FSN2) //ถ้าSPN2 มีค่ามากกว่า FSN2 ให้ SPN2 = FSN2
      {
        SPN2 = FSN2;
      }
      Serial.print("SPN2 = ");
      Serial.println(SPN2);
      
      C = ( 4095 * SPN2 ) / FSN2 ; //แปลงค่าSPN2ให้อยู่ในช่วง 0-4095 byte 
      voltage2(C); //Set DAC voltage
      Serial.print("C = ");
      Serial.println(C, BIN);
      Serial.println(C);
      
      D = ( FSN2 * C ) / 4095 ; //แปลงช่วง 0-4095 ให้อยู่ในค่าFSN2
      Serial.print("D(sccm) = ");
      Serial.println(D);      
      Serial.println("_______________________________ END CHANNEL 2 _______________________________");
      Serial.println("End ask.");

      ADC2 = true;
    }
  }
}
void TimingStart3 (boolean _flag)
{
  if (_flag)
  {
    TimingLED3 = true;
    memset(hr, 0, sizeof(hr));
    len_hr = getText("t370", hr, sizeof(hr)); //รับค่าจากTextbox"t370"มาโชว์ที่len_hr
    memset(min, 0, sizeof(min));
    len_min = getText("t371", min, sizeof(min)); //รับค่าจากTextbox"t371"มาโชว์ที่len_min
    memset(sec, 0, sizeof(sec));
    len_sec = getText("t372", sec, sizeof(sec)); //รับค่าจากTextbox"t372"มาโชว์ที่len_sec
    callPage("37");

#if PRINT_DEBUG
    Serial.print("Hr.[] = ");
    for (ihr = 0; ihr < len_hr; ihr++)
    {
      Serial.print(hr[ihr]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Min[] = ");
    for (imin = 0; imin < len_min; imin++)
    {
      Serial.print(min[imin]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Sec[] = ");
    for (isec = 0; isec < len_sec; isec++)
    {
      Serial.print(sec[isec]);
    }
    Serial.println();
#endif

    led_sec = atof(sec); //รับค่าsec มาเก็บไว้ที่led_sec
    Serial.print("led_sec = ");
    Serial.println(led_sec);

    led_min = atof(min); //รับค่าmin มาเก็บไว้ที่led_min
    Serial.print("led_min = ");
    Serial.println(led_min);

    led_hr = atof(hr); //รับค่าhr มาเก็บไว้ที่led_hr
    Serial.print("led_hr = ");
    Serial.println(led_hr);

    float timerhr = ( led_hr * 60000 ) * 60 ; //รับค่าled_hrมาคำนวณ แล้วเก็บค่าไว้ที่ timerhr
    Serial.print("timerhr = ");
    Serial.println(timerhr);

    float timermin =  led_min * 60000 ; //รับค่าled_minมาคำนวณ แล้วเก็บค่าไว้ที่ timermin
    Serial.print("timermin = ");
    Serial.println(timermin);

    float timersec = led_sec * 1000; //รับค่าled_secมาคำนวณ แล้วเก็บค่าไว้ที่ timersec
    Serial.print("timersec = ");
    Serial.println(timersec);

    timer = timerhr + timermin + timersec;  //รับค่าtimerhr,timerminและ timersec มาคำนวณแล้วเก็บค่าไว้ที่timer
    Serial.print("timer = ");
    Serial.println(timer);

    // ----------------------------------------------------------------------
    // Channel 3
    // ----------------------------------------------------------------------
    callPage("4");
    memset(buffer4, 0, sizeof(buffer4));
    memset(buffer5, 0, sizeof(buffer5));
    len_buff4 = getText("t41", buffer4, sizeof(buffer4)); //รับค่าจากTextbox"t41"มาโชว์ที่len_buff4
    len_buff5 = getText("t42", buffer5, sizeof(buffer5)); //รับค่าจากTextbox"t42"มาโชว์ที่len_buff5
    callPage("13");
    memset(number4, 0, sizeof(number4));
    memset(number5, 0, sizeof(number5));
    len_num4 = getText("t131", number4, sizeof(number4)); //รับค่าจากTextbox"t131"มาโชว์ที่len_num4
    len_num5 = getText("t132", number5, sizeof(number5)); //รับค่าจากTextbox"t132"มาโชว์ที่len_num5

    // ----------------------------------------------------------------------
    // Channe3
    // ----------------------------------------------------------------------
#if PRINT_DEBUG
    Serial.print("Buffer4[] = ");
    for (ibuff4 = 0; ibuff4 < len_buff4; ibuff4++)
    {
      Serial.print(buffer4[ibuff4]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Buffer5[] = ");
    for (ibuff5 = 0; ibuff5 < len_buff5; ibuff5++)
    {
      Serial.print(buffer5[ibuff5]);
    }
    Serial.println();
#endif

#if PRINT_DEBUG
    Serial.print("Number4[] = ");
    for (inum4 = 0; inum4 < len_num4; inum4++)
    {
      Serial.print(number4[inum4]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Number5[] = ");
    for (inum5 = 0; inum5 < len_num5; inum5++)
    {
      Serial.print(number5[inum5]);
    }
    Serial.println();
#endif

    // ----------------------------------------------------------------------
    // Channel 3
    // ----------------------------------------------------------------------
    String W = String(buffer4);
    Serial.print("W = ");
    Serial.println(W);

    if (W == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GM3 = 0.993;
      Serial.print("GM3 = ");
      Serial.println(GM3, 3);
    }
    else if (W == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GM3 = 1.39;
      Serial.print("GM3 = ");
      Serial.println(GM3);
    }
    else if (W == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GM3 = 1.00;
      Serial.print("GM3 = ");
      Serial.println(GM3);
    }
    else if (W == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GM3 = 1.01;
      Serial.print("GM3 = ");
      Serial.println(GM3);
    }
    else
    {
      GM3 = atof(buffer4);  //รับค่าbuffer4 มาเก็บไว้ที่GM3
      Serial.print("GM3 = ");
      Serial.println(GM3, 3);
    }

    String X = String(buffer5);
    Serial.print("X = ");
    Serial.println(X);

    if (X == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GF3 = 0.993;
      Serial.print("GF3 = ");
      Serial.println(GF3, 3);
    }
    else if (X == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GF3 = 1.39;
      Serial.print("GF3 = ");
      Serial.println(GF3);
    }
    else if (X == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GF3 = 1.00;
      Serial.print("GF3 = ");
      Serial.println(GF3);
    }
    else if (X == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GF3 = 1.01;
      Serial.print("GF3 = ");
      Serial.println(GF3);
    }
    else
    {
      GF3 = atof(buffer5); //รับค่าbuffer5 มาเก็บไว้ที่GF3
      Serial.print("GF3 = ");
      Serial.println(GF3, 3);
    }

    FS3 = atof(number4); //รับค่าnumber4 มาเก็บไว้ทีFS3
    Serial.print("FS3 = ");
    Serial.println(FS3);

    SP3 = atof(number5); //รับค่าnumber5 มาเก็บไว้ทีSP3
    Serial.print("SP3 = ");
    Serial.println(SP3);

    if (SP3 > FS3) //ถ้าSP3 มีค่ามากกว่า FS3 ให้โชว์หน้าที่29
    {
      callPage("29");
      E = 0;
      voltage3(E); //Set DAC voltage
      Serial.print("E = ");
      Serial.println(E);
    }
    else
    {
      callPage("37");
      // ----------------------------------------------------------------------
      // Part Calculate Channel 3
      // ----------------------------------------------------------------------

      FSN3 = ( GF3 / GM3 ) * FS3  ; //รับค่าGF3,GM3และFS3มาคำนวณ แล้วเก็บค่าไว้ที่FSN3
      Serial.print("FSN3(sccm) = ");
      Serial.println(FSN3);

      SPN3 = ( FSN3 / FS3 ) * SP3 ; //รับค่าFSN3,FS3และSP3มาคำนวณ แล้วเก็บค่าไว้ที่SPN3
      if (SPN3 > FSN3) //รับค่าFSN3,FS3และSP3มาคำนวณ แล้วเก็บค่าไว้ที่SPN3
      {
        SPN3 = FSN3;
      }
      Serial.print("SPN3 = ");
      Serial.println(SPN3);
     
      E = ( 4095 * SPN3 ) / FSN3 ; //แปลงค่าSPN3ให้อยู่ในช่วง 0-4095 byte 
      voltage3(E);//Set DAC voltage
      Serial.print("E = ");
      Serial.println(E, BIN);
      Serial.println(E);
       
      F = ( FSN3 * E ) / 4095 ; //แปลงช่วง 0-4095 ให้อยู่ในค่าFSN3
      Serial.print("F(sccm) = ");
      Serial.println(F);
      Serial.println("_______________________________ END CHANNEL 3 _______________________________");
      Serial.println("End ask.");

      ADC3 = true;
    }
  }
}
void TimingStart4 (boolean _flag)
{
  if (_flag)
  {
    TimingLED4 = true;
    memset(hr, 0, sizeof(hr));
    len_hr = getText("t380", hr, sizeof(hr)); //รับค่าจากTextbox"t350"มาโชว์ที่len_hr
    memset(min, 0, sizeof(min));
    len_min = getText("t381", min, sizeof(min)); //รับค่าจากTextbox"t351"มาโชว์ที่len_min
    memset(sec, 0, sizeof(sec));
    len_sec = getText("t382", sec, sizeof(sec)); //รับค่าจากTextbox"t352"มาโชว์ที่len_sec
    callPage("38");

#if PRINT_DEBUG
    Serial.print("Hr.[] = ");
    for (ihr = 0; ihr < len_hr; ihr++)
    {
      Serial.print(hr[ihr]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Min[] = ");
    for (imin = 0; imin < len_min; imin++)
    {
      Serial.print(min[imin]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Sec[] = ");
    for (isec = 0; isec < len_sec; isec++)
    {
      Serial.print(sec[isec]);
    }
    Serial.println();
#endif

    led_sec = atof(sec); //รับค่าsec มาเก็บไว้ที่led_sec
    Serial.print("led_sec = ");
    Serial.println(led_sec);

    led_min = atof(min); //รับค่าmin มาเก็บไว้ที่led_min
    Serial.print("led_min = ");
    Serial.println(led_min);

    led_hr = atof(hr); //รับค่าhr มาเก็บไว้ที่led_hr
    Serial.print("led_hr = ");
    Serial.println(led_hr);

    float timerhr = ( led_hr * 60000 ) * 60 ; //รับค่าled_hrมาคำนวณ แล้วเก็บค่าไว้ที่ timerhr
    Serial.print("timerhr = ");
    Serial.println(timerhr);

    float timermin =  led_min * 60000 ; //รับค่าled_minมาคำนวณ แล้วเก็บค่าไว้ที่ timermin
    Serial.print("timermin = ");
    Serial.println(timermin);

    float timersec = led_sec * 1000; //รับค่าled_secมาคำนวณ แล้วเก็บค่าไว้ที่ timersec
    Serial.print("timersec = ");
    Serial.println(timersec);

    timer = timerhr + timermin + timersec; //รับค่าtimerhr,timerminและ timersec มาคำนวณแล้วเก็บค่าไว้ที่timer
    Serial.print("timer = ");
    Serial.println(timer);

    // ----------------------------------------------------------------------
    // Channel 4
    // ----------------------------------------------------------------------
    callPage("5");
    memset(buffer6, 0, sizeof(buffer6));
    memset(buffer7, 0, sizeof(buffer7));
    len_buff6 = getText("t51", buffer6, sizeof(buffer6)); //รับค่าจากTextbox"t51"มาโชว์ที่len_buff6
    len_buff7 = getText("t52", buffer7, sizeof(buffer7)); //รับค่าจากTextbox"t52"มาโชว์ที่len_buff7
    callPage("14");
    memset(number6, 0, sizeof(number6));
    memset(number7, 0, sizeof(number7));
    len_num6 = getText("t141", number6, sizeof(number6)); //รับค่าจากTextbox"t141"มาโชว์ที่len_num6
    len_num7 = getText("t142", number7, sizeof(number7)); //รับค่าจากTextbox"t142"มาโชว์ที่len_num7

    // ----------------------------------------------------------------------
    // Channel 4
    // ----------------------------------------------------------------------
#if PRINT_DEBUG
    Serial.print("Buffer6[] = ");
    for (ibuff6 = 0; ibuff6 < len_buff6; ibuff6++)
    {
      Serial.print(buffer6[ibuff6]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Buffer7[] = ");
    for (ibuff7 = 0; ibuff7 < len_buff7; ibuff7++)
    {
      Serial.print(buffer7[ibuff7]);
    }
    Serial.println();
#endif

#if PRINT_DEBUG
    Serial.print("Number6[] = ");
    for (inum6 = 0; inum6 < len_num6; inum6++)
    {
      Serial.print(number6[inum6]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Number7[] = ");
    for (inum7 = 0; inum7 < len_num7; inum7++)
    {
      Serial.print(number7[inum7]);
    }
    Serial.println();
#endif

    // ----------------------------------------------------------------------
    // Channel 4
    // ----------------------------------------------------------------------
    String Y = String(buffer6);
    Serial.print("Y = ");
    Serial.println(Y);

    if (Y == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GM4 = 0.993;
      Serial.print("GM4 = ");
      Serial.println(GM4, 3);
    }
    else if (Y == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GM4 = 1.39;
      Serial.print("GM4 = ");
      Serial.println(GM4);
    }
    else if (Y == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GM4 = 1.00;
      Serial.print("GM4 = ");
      Serial.println(GM4);
    }
    else if (Y == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GM4 = 1.01;
      Serial.print("GM4 = ");
      Serial.println(GM4);
    }
    else
    {
      GM4 = atof(buffer6); //รับค่าbuffer6 มาเก็บไว้ที่GM4
      Serial.print("GM4 = ");
      Serial.println(GM4, 3);
    }
    String Z = String(buffer7);
    Serial.print("Z = ");
    Serial.println(Z);

    if (Z == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GF4 = 0.993;
      Serial.print("GF4 = ");
      Serial.println(GF4, 3);
    }
    else if (Z == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GF4 = 1.39;
      Serial.print("GF4 = ");
      Serial.println(GF4);
    }
    else if (Z == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GF4 = 1.00;
      Serial.print("GF4 = ");
      Serial.println(GF4);
    }
    else if (Z == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GF4 = 1.01;
      Serial.print("GF4 = ");
      Serial.println(GF4);
    }
    else
    {
      GF4 = atof(buffer7); //รับค่าbuffer7 มาเก็บไว้ที่GF4
      Serial.print("GF4 = ");
      Serial.println(GF4, 3);
    }

    FS4 = atof(number6); //รับค่าnumber6 มาเก็บไว้ทีFS4
    Serial.print("FS4 = ");
    Serial.println(FS4, 4);

    SP4 = atof(number7);  //รับค่าnumber7 มาเก็บไว้ทีSP4
    Serial.print("SP4 = ");
    Serial.println(SP4, 4);

    if (SP4 > FS4) //ถ้าSP4 มีค่ามากกว่า FS4 ให้โชว์หน้าที่30
    {
      callPage("30");
      G = 0;
      voltage4(G); //Set DAC voltage
      Serial.print("G = ");
      Serial.println(G);
    }
    else
    {
      callPage("38");

      // ----------------------------------------------------------------------
      // Part Calculate Channel 4
      // ----------------------------------------------------------------------
      FSN4 = ( GF4 / GM4 ) * FS4  ; //รับค่าGF4,GM4และFS4มาคำนวณ แล้วเก็บค่าไว้ที่FSN4
      Serial.print("FSN4(sccm) = ");
      Serial.println(FSN4);

      SPN4 = ( FSN4 / FS4 ) * SP4 ; //รับค่าFSN4,FS4และSP4มาคำนวณ แล้วเก็บค่าไว้ที่SPN4
      if (SPN4 > FSN4) //ถ้าSPN4 มีค่ามากกว่า FSN4 ให้ SPN4 = FSN4
      {
        SPN4 = FSN4;
      }
      Serial.print("SPN4 = ");
      Serial.println(SPN4);
      Serial.println(SPN4, BIN);
      
      G = ( 4095 * SPN4 ) / FSN4 ; //แปลงค่าSPN4ให้อยู่ในช่วง 0-4095 byte 
      voltage4(G); //Set DAC voltage
      Serial.print("G = ");
      Serial.println(G, BIN);
      Serial.println(G);
       
      F = ( FSN4 * G ) / 4095 ; //แปลงช่วง 0-4095 ให้อยู่ในค่าFSN4
      Serial.print("F(sccm) = ");
      Serial.println(F);
      Serial.println("_______________________________ END CHANNEL 4 _______________________________");
      Serial.println("End ask.");

      ADC4 = true;
    }
  }
}
void TimingStartONOFF1(boolean _flag)
{
  if (_flag)
  {
    BlinkLED1 = true;
    memset(hr, 0, sizeof(hr));
    len_hr = getText("t350", hr, sizeof(hr)); //รับค่าจากTextbox"t350"มาโชว์ที่len_hr
    memset(min, 0, sizeof(min));
    len_min = getText("t351", min, sizeof(min));//รับค่าจากTextbox"t351"มาโชว์ที่len_min
    memset(sec, 0, sizeof(sec));
    len_sec = getText("t352", sec, sizeof(sec)); //รับค่าจากTextbox"t352"มาโชว์ที่len_sec
    callPage("35");

#if PRINT_DEBUG
    Serial.print("Hr.[] = ");
    for (ihr = 0; ihr < len_hr; ihr++)
    {
      Serial.print(hr[ihr]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Min[] = ");
    for (imin = 0; imin < len_min; imin++)
    {
      Serial.print(min[imin]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Sec[] = ");
    for (isec = 0; isec < len_sec; isec++)
    {
      Serial.print(sec[isec]);
    }
    Serial.println();
#endif

    led_sec = atof(sec); //รับค่าsec มาเก็บไว้ที่led_sec
    Serial.print("led_sec = ");
    Serial.println(led_sec);

    led_min = atof(min); //รับค่าmin มาเก็บไว้ที่led_min
    Serial.print("led_min = ");
    Serial.println(led_min);

    led_hr = atof(hr); //รับค่าhr มาเก็บไว้ที่led_hr
    Serial.print("led_hr = ");
    Serial.println(led_hr);

    float timerhr = ( led_hr * 60000 ) * 60 ; //รับค่าled_hrมาคำนวณ แล้วเก็บค่าไว้ที่ timerhr
    Serial.print("timerhr = ");
    Serial.println(timerhr);

    float timermin =  led_min * 60000 ; //รับค่าled_minมาคำนวณ แล้วเก็บค่าไว้ที่ timermin
    Serial.print("timermin = ");
    Serial.println(timermin);

    float timersec = led_sec * 1000; //รับค่าled_secมาคำนวณ แล้วเก็บค่าไว้ที่ timersec
    Serial.print("timersec = ");
    Serial.println(timersec);

    timer = timerhr + timermin + timersec; //รับค่าtimerhr,timerminและ timersec มาคำนวณแล้วเก็บค่าไว้ที่timer
    Serial.print("timer = ");
    Serial.println(timer);

    // ----------------------------------------------------------------------
    // Channel 1
    // ----------------------------------------------------------------------
    callPage("2");
    memset(buffer, 0, sizeof(buffer));
    memset(buffer1, 0, sizeof(buffer1));
    len_buff = getText("t21", buffer, sizeof(buffer)); //รับค่าจากTextbox"t21"มาโชว์ที่len_buff
    len_buff1 = getText("t22", buffer1, sizeof(buffer1)); //รับค่าจากTextbox"t22"มาโชว์ที่len_buff1
    callPage("11");
    memset(number, 0, sizeof(number));
    memset(number1, 0, sizeof(number1));
    len_num = getText("t111", number, sizeof(number)); //รับค่าจากTextbox"t111"มาโชว์ที่len_num
    len_num1 = getText("t112", number1, sizeof(number1)); //รับค่าจากTextbox"t112"มาโชว์ที่len_num1


    // ----------------------------------------------------------------------
    // Channel 1
    // ----------------------------------------------------------------------
#if PRINT_DEBUG
    Serial.print("Buffer[] = ");
    for (ibuff = 0; ibuff < len_buff; ibuff++)
    {
      Serial.print(buffer[ibuff]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Buffer1[] = ");
    for (ibuff1 = 0; ibuff1 < len_buff1; ibuff1++)
    {
      Serial.print(buffer1[ibuff1]);
    }
    Serial.println();
#endif

#if PRINT_DEBUG
    Serial.print("Number[] = ");
    for (inum = 0; inum < len_num; inum++)
    {
      Serial.print(number[inum]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Number1[] = ");
    for (inum1 = 0; inum1 < len_num1; inum1++)
    {
      Serial.print(number1[inum1]);
    }
    Serial.println();
#endif

    // ----------------------------------------------------------------------
    // Channel 1
    // ----------------------------------------------------------------------
    String S = String(buffer);
    Serial.print("S = ");
    Serial.println(S);

    if (S == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GM1 = 0.993;
      Serial.print("GM1 = ");
      Serial.println(GM1, 3);
    }
    else if (S == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GM1 = 1.39;
      Serial.print("GM1 = ");
      Serial.println(GM1);
    }
    else if (S == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GM1 = 1.00;
      Serial.print("GM1 = ");
      Serial.println(GM1);
    }
    else if (S == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GM1 = 1.01;
      Serial.print("GM1 = ");
      Serial.println(GM1);
    }
    else
    {
      GM1 = atof(buffer); //รับค่าbuffer มาเก็บไว้ที่GM1
      Serial.print("GM1 = ");
      Serial.println(GM1, 3);
    }

    String T = String(buffer1);
    Serial.print("T = ");
    Serial.println(T);

    if (T == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GF1 = 0.993;
      Serial.print("GF1 = ");
      Serial.println(GF1, 3);
    }
    else if (T == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GF1 = 1.39;
      Serial.print("GF1 = ");
      Serial.println(GF1);
    }
    else if (T == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GF1 = 1.00;
      Serial.print("GF1 = ");
      Serial.println(GF1);
    }
    else if (T == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GF1 = 1.01;
      Serial.print("GF1 = ");
      Serial.println(GF1);
    }
    else
    {
      GF1 = atof(buffer1); //รับค่าbuffer1 มาเก็บไว้ที่GF1
      Serial.print("GF1 = ");
      Serial.println(GF1, 3);
    }

    FS1 = atof(number); //รับค่าnumber มาเก็บไว้ทีFS1
    Serial.print("FS1 = ");
    Serial.println(FS1);

    SP1 = atof(number1); //รับค่าnumber1 มาเก็บไว้ทีSP1
    Serial.print("SP1 = ");
    Serial.println(SP1);

    if (SP1 > FS1) //ถ้าSP1 มีค่ามากกว่า FS1 ให้โชว์หน้าที่27
    {
      callPage("27");
      A = 0;
      voltage1(A); //Set DAC voltage
      Serial.print("A = ");
      Serial.println(A);
    }
    else
    {
      callPage("35");

      // ----------------------------------------------------------------------
      // Part Calculate Channel 1
      // ----------------------------------------------------------------------
      FSN1 = ( GF1 / GM1 ) * FS1; //รับค่าGF1,GM1และFS1มาคำนวณ แล้วเก็บค่าไว้ที่FSN1
      Serial.print("FSN1(sccm) = ");
      Serial.println(FSN1);

      SPN1 = ( FSN1 / FS1 ) * SP1 ; //รับค่าFSN1,FS1และSP1มาคำนวณ แล้วเก็บค่าไว้ที่SPN1
      if (SPN1 > FSN1) //ถ้าSPN1 มีค่ามากกว่า FSN1 ให้ SPN1 = FSN1
      {
        SPN1 = FSN1;
      }
      Serial.print("SPN1 = ");
      Serial.println(SPN1);
      
      A = ( 4095 * SPN1 ) / FSN1 ; //แปลงค่าSPN1ให้อยู่ในช่วง 0-4095 byte 
      voltage1(A); //Set DAC voltage
      Serial.print("A = ");
      Serial.println(A, BIN);
      Serial.println(A);
       
      B = ( FSN1 * A ) / 4095 ; //แปลงช่วง 0-4095 ให้อยู่ในค่าFSN1
      Serial.print("B(sccm) = ");
      Serial.println(B);
      Serial.println("_______________________________ END CHANNEL 1 _______________________________");
      Serial.println("End ask.");

      ADC1 = true;
    }
  }
}
void TimingStartONOFF2 (boolean _flag)
{
  if (_flag)
  {
    BlinkLED2 = true;
    memset(hr, 0, sizeof(hr));
    len_hr = getText("t360", hr, sizeof(hr)); //รับค่าจากTextbox"t360"มาโชว์ที่len_hr
    memset(min, 0, sizeof(min));
    len_min = getText("t361", min, sizeof(min)); //รับค่าจากTextbox"t361"มาโชว์ที่len_min
    memset(sec, 0, sizeof(sec));
    len_sec = getText("t362", sec, sizeof(sec)); //รับค่าจากTextbox"t362"มาโชว์ที่len_sec
    callPage("36");

#if PRINT_DEBUG
    Serial.print("Hr.[] = ");
    for (ihr = 0; ihr < len_hr; ihr++)
    {
      Serial.print(hr[ihr]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Min[] = ");
    for (imin = 0; imin < len_min; imin++)
    {
      Serial.print(min[imin]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Sec[] = ");
    for (isec = 0; isec < len_sec; isec++)
    {
      Serial.print(sec[isec]);
    }
    Serial.println();
#endif

    led_sec = atof(sec); //รับค่าsec มาเก็บไว้ที่led_sec
    Serial.print("led_sec = ");
    Serial.println(led_sec);

    led_min = atof(min); //รับค่าmin มาเก็บไว้ที่led_min
    Serial.print("led_min = ");
    Serial.println(led_min);

    led_hr = atof(hr); //รับค่าhr มาเก็บไว้ที่led_hr
    Serial.print("led_hr = ");
    Serial.println(led_hr);

    float timerhr = ( led_hr * 60000 ) * 60 ; //รับค่าled_hrมาคำนวณ แล้วเก็บค่าไว้ที่ timerhr
    Serial.print("timerhr = ");
    Serial.println(timerhr);

    float timermin =  led_min * 60000 ; //รับค่าled_minมาคำนวณ แล้วเก็บค่าไว้ที่ timermin
    Serial.print("timermin = ");
    Serial.println(timermin);

    float timersec = led_sec * 1000; //รับค่าled_secมาคำนวณ แล้วเก็บค่าไว้ที่ timersec
    Serial.print("timersec = ");
    Serial.println(timersec);

    timer = timerhr + timermin + timersec;  //รับค่าtimerhr,timerminและ timersec มาคำนวณแล้วเก็บค่าไว้ที่timer
    Serial.print("timer = ");
    Serial.println(timer);

    // ----------------------------------------------------------------------
    // Channel 2
    // ----------------------------------------------------------------------
    callPage("3");
    memset(buffer2, 0, sizeof(buffer2));
    memset(buffer3, 0, sizeof(buffer3));
    len_buff2 = getText("t31", buffer2, sizeof(buffer2)); //รับค่าจากTextbox"t31"มาโชว์ที่len_buff2
    len_buff3 = getText("t32", buffer3, sizeof(buffer3)); //รับค่าจากTextbox"t32"มาโชว์ที่len_buff3
    callPage("12");
    memset(number2, 0, sizeof(number2));
    memset(number3, 0, sizeof(number3));
    len_num2 = getText("t121", number2, sizeof(number2)); //รับค่าจากTextbox"t121"มาโชว์ที่len_num2
    len_num3 = getText("t122", number3, sizeof(number3)); //รับค่าจากTextbox"t122"มาโชว์ที่len_num3

    // ----------------------------------------------------------------------
    // Channel 2
    // ----------------------------------------------------------------------

#if PRINT_DEBUG
    Serial.print("Buffer2[] = ");
    for (ibuff2 = 0; ibuff2 < len_buff2; ibuff2++)
    {
      Serial.print(buffer2[ibuff2]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Buffer3[] = ");
    for (ibuff3 = 0; ibuff3 < len_buff3; ibuff3++)
    {
      Serial.print(buffer3[ibuff3]);
    }
    Serial.println();
#endif

#if PRINT_DEBUG
    Serial.print("Number2[] = ");
    for (inum2 = 0; inum2 < len_num2; inum2++)
    {
      Serial.print(number2[inum2]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Number3[] = ");
    for (inum3 = 0; inum3 < len_num3; inum3++)
    {
      Serial.print(number3[inum3]);
    }
    Serial.println();
#endif

    // ----------------------------------------------------------------------
    // Channel 2
    // ----------------------------------------------------------------------

    String U = String(buffer2);
    Serial.print("U = ");
    Serial.println(U);

    if (U == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GM2 = 0.993;
      Serial.print("GM2 = ");
      Serial.println(GM2, 3);
    }
    else if (U == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GM2 = 1.39;
      Serial.print("GM2 = ");
      Serial.println(GM2);
    }
    else if (U == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GM2 = 1.00;
      Serial.print("GM2 = ");
      Serial.println(GM2);
    }
    else if (U == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GM2 = 1.01;
      Serial.print("GM2 = ");
      Serial.println(GM2);
    }
    else
    {
      GM2 = atof(buffer2); //รับค่าbuffer2 มาเก็บไว้ที่GM2
      Serial.print("GM2 = ");
      Serial.println(GM2, 3);
    }

    String V = String(buffer3);
    Serial.print("V = ");
    Serial.println(V);

    if (V == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GF2 = 0.993;
      Serial.print("GF2 = ");
      Serial.println(GF2, 3);
    }
    else if (V == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GF2 = 1.39;
      Serial.print("GF2 = ");
      Serial.println(GF2);
    }
    else if (V == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GF2 = 1.00;
      Serial.print("GF2 = ");
      Serial.println(GF2);
    }
    else if (V == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GF2 = 1.01;
      Serial.print("GF2 = ");
      Serial.println(GF2);
    }
    else
    {
      GF2 = atof(buffer3); //รับค่าbuffer3 มาเก็บไว้ที่GF2
      Serial.print("GF2 = ");
      Serial.println(GF2, 3);
    }

    FS2 = atof(number2);  //รับค่าnumber2 มาเก็บไว้ทีFS2
    Serial.print("FS2 = ");
    Serial.println(FS2, 4);

    SP2 = atof(number3); //รับค่าnumber3 มาเก็บไว้ทีSP2
    Serial.print("SP2 = ");
    Serial.println(SP2, 4);

    if (SP2 > FS2) //ถ้าSP1 มีค่ามากกว่า FS1 ให้โชว์หน้าที่28
    {
      callPage("28");
      C = 0;
      voltage2(C);   //Set DAC voltage
      Serial.print("C = ");
      Serial.println(C);
    }
    else
    {
      callPage("36");

      // ----------------------------------------------------------------------
      // Part Calculate Channel 2
      // ----------------------------------------------------------------------

      FSN2 = ( GF2 / GM2 ) * FS2  ;  //รับค่าGF2,GM2และFS2มาคำนวณ แล้วเก็บค่าไว้ที่FSN2 
      Serial.print("FSN2(sccm) = ");
      Serial.println(FSN2);

      SPN2 = ( FSN2 / FS2 ) * SP2 ; //รับค่าFSN2,FS2และSP2มาคำนวณ แล้วเก็บค่าไว้ที่SPN2
      if (SPN2 > FSN2) //ถ้าSPN2 มีค่ามากกว่า FSN2 ให้ SPN2 = FSN2
      {
        SPN2 = FSN2;
      }
      Serial.print("SPN2 = ");
      Serial.println(SPN2);

      C = ( 4095 * SPN2 ) / FSN2 ; //แปลงค่าSPN2ให้อยู่ในช่วง 0-4095 byte 
      voltage2(C); //Set DAC voltage
      Serial.print("C = ");
      Serial.println(C, BIN);
      Serial.println(C);

      D = ( FSN2 * C ) / 4095 ; //แปลงช่วง 0-4095 ให้อยู่ในค่าFSN2
      Serial.print("D(sccm) = ");
      Serial.println(D);
      Serial.println("_______________________________ END CHANNEL 2 _______________________________");
      Serial.println("End ask.");
	  
      ADC2 = true;
    }
  }
}
void TimingStartONOFF3 (boolean _flag)
{
  if (_flag)
  {
    BlinkLED3 = true;
    memset(hr, 0, sizeof(hr));
    len_hr = getText("t370", hr, sizeof(hr));  //รับค่าจากTextbox"t370"มาโชว์ที่len_hr
    memset(min, 0, sizeof(min));
    len_min = getText("t371", min, sizeof(min));  //รับค่าจากTextbox"t371"มาโชว์ที่len_min
    memset(sec, 0, sizeof(sec));
    len_sec = getText("t372", sec, sizeof(sec));  //รับค่าจากTextbox"t372"มาโชว์ที่len_sec
    callPage("37");

#if PRINT_DEBUG
    Serial.print("Hr.[] = ");
    for (ihr = 0; ihr < len_hr; ihr++)
    {
      Serial.print(hr[ihr]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Min[] = ");
    for (imin = 0; imin < len_min; imin++)
    {
      Serial.print(min[imin]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Sec[] = ");
    for (isec = 0; isec < len_sec; isec++)
    {
      Serial.print(sec[isec]);
    }
    Serial.println();
#endif

    led_sec = atof(sec); //รับค่าจากTextbox"t372"มาโชว์ที่len_sec
    Serial.print("led_sec = ");
    Serial.println(led_sec);

    led_min = atof(min); //รับค่าmin มาเก็บไว้ที่led_min
    Serial.print("led_min = ");
    Serial.println(led_min);

    led_hr = atof(hr);  //รับค่าhr มาเก็บไว้ที่led_hr
    Serial.print("led_hr = ");
    Serial.println(led_hr);

    float timerhr = ( led_hr * 60000 ) * 60 ; //รับค่าled_hrมาคำนวณ แล้วเก็บค่าไว้ที่ timerhr
    Serial.print("timerhr = ");
    Serial.println(timerhr);

    float timermin =  led_min * 60000 ; //รับค่าled_minมาคำนวณ แล้วเก็บค่าไว้ที่ timermin
    Serial.print("timermin = ");
    Serial.println(timermin);

    float timersec = led_sec * 1000; //รับค่าled_secมาคำนวณ แล้วเก็บค่าไว้ที่ timersec
    Serial.print("timersec = ");
    Serial.println(timersec);

    timer = timerhr + timermin + timersec; //รับค่าtimerhr,timerminและ timersec มาคำนวณแล้วเก็บค่าไว้ที่timer
    Serial.print("timer = ");
    Serial.println(timer);

    // ----------------------------------------------------------------------
    // Channel 3
    // ----------------------------------------------------------------------
    callPage("4");
    memset(buffer4, 0, sizeof(buffer4));
    memset(buffer5, 0, sizeof(buffer5));
    len_buff4 = getText("t41", buffer4, sizeof(buffer4)); //รับค่าจากTextbox"t41"มาโชว์ที่len_buff4
    len_buff5 = getText("t42", buffer5, sizeof(buffer5)); //รับค่าจากTextbox"t42"มาโชว์ที่len_buff5
    callPage("13");
    memset(number4, 0, sizeof(number4));
    memset(number5, 0, sizeof(number5));
    len_num4 = getText("t131", number4, sizeof(number4)); //รับค่าจากTextbox"t131"มาโชว์ที่len_num4
    len_num5 = getText("t132", number5, sizeof(number5)); //รับค่าจากTextbox"t132"มาโชว์ที่len_num5

    // ----------------------------------------------------------------------
    // Channe3
    // ----------------------------------------------------------------------
#if PRINT_DEBUG
    Serial.print("Buffer4[] = ");
    for (ibuff4 = 0; ibuff4 < len_buff4; ibuff4++)
    {
      Serial.print(buffer4[ibuff4]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Buffer5[] = ");
    for (ibuff5 = 0; ibuff5 < len_buff5; ibuff5++)
    {
      Serial.print(buffer5[ibuff5]);
    }
    Serial.println();
#endif

#if PRINT_DEBUG
    Serial.print("Number4[] = ");
    for (inum4 = 0; inum4 < len_num4; inum4++)
    {
      Serial.print(number4[inum4]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Number5[] = ");
    for (inum5 = 0; inum5 < len_num5; inum5++)
    {
      Serial.print(number5[inum5]);
    }
    Serial.println();
#endif

    // ----------------------------------------------------------------------
    // Channel 3
    // ----------------------------------------------------------------------
    String W = String(buffer4);
    Serial.print("W = ");
    Serial.println(W);

    if (W == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GM3 = 0.993;
      Serial.print("GM3 = ");
      Serial.println(GM3, 3);
    }
    else if (W == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GM3 = 1.39;
      Serial.print("GM3 = ");
      Serial.println(GM3);
    }
    else if (W == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GM3 = 1.00;
      Serial.print("GM3 = ");
      Serial.println(GM3);
    }
    else if (W == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GM3 = 1.01;
      Serial.print("GM3 = ");
      Serial.println(GM3);
    }
    else
    {
      GM3 = atof(buffer4); //รับค่าbuffer4 มาเก็บไว้ที่GM3
      Serial.print("GM3 = ");
      Serial.println(GM3, 3);
    }

    String X = String(buffer5);
    Serial.print("X = ");
    Serial.println(X);

    if (X == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GF3 = 0.993;
      Serial.print("GF3 = ");
      Serial.println(GF3, 3);
    }
    else if (X == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GF3 = 1.39;
      Serial.print("GF3 = ");
      Serial.println(GF3);
    }
    else if (X == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GF3 = 1.00;
      Serial.print("GF3 = ");
      Serial.println(GF3);
    }
    else if (X == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GF3 = 1.01;
      Serial.print("GF3 = ");
      Serial.println(GF3);
    }
    else
    {
      GF3 = atof(buffer5); //รับค่าbuffer5 มาเก็บไว้ที่GF3
      Serial.print("GF3 = ");
      Serial.println(GF3, 3);
    }

    FS3 = atof(number4); //รับค่าnumber4 มาเก็บไว้ทีFS3
    Serial.print("FS3 = ");
    Serial.println(FS3);

    SP3 = atof(number5); //รับค่าnumber5 มาเก็บไว้ทีSP3
    Serial.print("SP3 = ");
    Serial.println(SP3);

    if (SP3 > FS3) //ถ้าSP3 มีค่ามากกว่า FS3 ให้โชว์หน้าที่29
    {
      callPage("29");
      E = 0;
      voltage3(E); //Set DAC voltage
      Serial.print("E = ");
      Serial.println(E);
    }
    else
    {
      callPage("37");
      // ----------------------------------------------------------------------
      // Part Calculate Channel 3
      // ----------------------------------------------------------------------

      FSN3 = ( GF3 / GM3 ) * FS3  ; //รับค่าGF3,GM3และFS3มาคำนวณ แล้วเก็บค่าไว้ที่FSN3
      Serial.print("FSN3(sccm) = ");
      Serial.println(FSN3);

      SPN3 = ( FSN3 / FS3 ) * SP3 ; //รับค่าFSN3,FS3และSP3มาคำนวณ แล้วเก็บค่าไว้ที่SPN3
      if (SPN3 > FSN3) //รับค่าFSN3,FS3และSP1มาคำนวณ แล้วเก็บค่าไว้ที่SPN3
      {
        SPN3 = FSN3;
      }
      Serial.print("SPN3 = ");
      Serial.println(SPN3);
       
      E = ( 4095 * SPN3 ) / FSN3 ; //แปลงค่าSPN3ให้อยู่ในช่วง 0-4095 byte 
      voltage3(E);//Set DAC voltage
      Serial.print("E = ");
      Serial.println(E, BIN);
      Serial.println(E);
       
      F = ( FSN3 * E ) / 4095 ; //แปลงช่วง 0-4095 ให้อยู่ในค่าFSN3
      Serial.print("F(sccm) = ");
      Serial.println(F);      
      Serial.println("_______________________________ END CHANNEL 3 _______________________________");
      Serial.println("End ask.");

      ADC3 = true;
    }
  }
}
void TimingStartONOFF4 (boolean _flag)
{
  if (_flag)
  {
    BlinkLED4 = true;
    memset(hr, 0, sizeof(hr));
    len_hr = getText("t380", hr, sizeof(hr)); //รับค่าจากTextbox"t350"มาโชว์ที่len_hr
    memset(min, 0, sizeof(min));
    len_min = getText("t381", min, sizeof(min)); //รับค่าจากTextbox"t351"มาโชว์ที่len_min
    memset(sec, 0, sizeof(sec));
    len_sec = getText("t382", sec, sizeof(sec)); //รับค่าจากTextbox"t352"มาโชว์ที่len_sec
    callPage("38");

#if PRINT_DEBUG
    Serial.print("Hr.[] = ");
    for (ihr = 0; ihr < len_hr; ihr++)
    {
      Serial.print(hr[ihr]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Min[] = ");
    for (imin = 0; imin < len_min; imin++)
    {
      Serial.print(min[imin]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Sec[] = ");
    for (isec = 0; isec < len_sec; isec++)
    {
      Serial.print(sec[isec]);
    }
    Serial.println();
#endif

    led_sec = atof(sec); //รับค่าsec มาเก็บไว้ที่led_sec
    Serial.print("led_sec = ");
    Serial.println(led_sec);

    led_min = atof(min); //รับค่าmin มาเก็บไว้ที่led_min
    Serial.print("led_min = ");
    Serial.println(led_min);

    led_hr = atof(hr); //รับค่าhr มาเก็บไว้ที่led_hr
    Serial.print("led_hr = ");
    Serial.println(led_hr);

    float timerhr = ( led_hr * 60000 ) * 60 ; //รับค่าled_hrมาคำนวณ แล้วเก็บค่าไว้ที่ timerhr
    Serial.print("timerhr = ");
    Serial.println(timerhr);

    float timermin =  led_min * 60000 ; //รับค่าled_minมาคำนวณ แล้วเก็บค่าไว้ที่ timermin
    Serial.print("timermin = ");
    Serial.println(timermin);

    float timersec = led_sec * 1000; //รับค่าled_secมาคำนวณ แล้วเก็บค่าไว้ที่ timersec
    Serial.print("timersec = ");
    Serial.println(timersec);

    timer = timerhr + timermin + timersec; //รับค่าtimerhr,timerminและ timersec มาคำนวณแล้วเก็บค่าไว้ที่timer
    Serial.print("timer = ");
    Serial.println(timer);

    // ----------------------------------------------------------------------
    // Channel 4
    // ----------------------------------------------------------------------
    callPage("5");
    memset(buffer6, 0, sizeof(buffer6));
    memset(buffer7, 0, sizeof(buffer7));
    len_buff6 = getText("t51", buffer6, sizeof(buffer6)); //รับค่าจากTextbox"t51"มาโชว์ที่len_buff6
    len_buff7 = getText("t52", buffer7, sizeof(buffer7)); //รับค่าจากTextbox"t52"มาโชว์ที่len_buff7
    callPage("14");
    memset(number6, 0, sizeof(number6));
    memset(number7, 0, sizeof(number7));
    len_num6 = getText("t141", number6, sizeof(number6)); //รับค่าจากTextbox"t141"มาโชว์ที่len_num6
    len_num7 = getText("t142", number7, sizeof(number7)); //รับค่าจากTextbox"t142"มาโชว์ที่len_num7

    // ----------------------------------------------------------------------
    // Channel 4
    // ----------------------------------------------------------------------
#if PRINT_DEBUG
    Serial.print("Buffer6[] = ");
    for (ibuff6 = 0; ibuff6 < len_buff6; ibuff6++)
    {
      Serial.print(buffer6[ibuff6]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Buffer7[] = ");
    for (ibuff7 = 0; ibuff7 < len_buff7; ibuff7++)
    {
      Serial.print(buffer7[ibuff7]);
    }
    Serial.println();
#endif

#if PRINT_DEBUG
    Serial.print("Number6[] = ");
    for (inum6 = 0; inum6 < len_num6; inum6++)
    {
      Serial.print(number6[inum6]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Number7[] = ");
    for (inum7 = 0; inum7 < len_num7; inum7++)
    {
      Serial.print(number7[inum7]);
    }
    Serial.println();
#endif

    // ----------------------------------------------------------------------
    // Channel 4
    // ----------------------------------------------------------------------
    String Y = String(buffer6);
    Serial.print("Y = ");
    Serial.println(Y);

    if (Y == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GM4 = 0.993;
      Serial.print("GM4 = ");
      Serial.println(GM4, 3);
    }
    else if (Y == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GM4 = 1.39;
      Serial.print("GM4 = ");
      Serial.println(GM4);
    }
    else if (Y == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GM4 = 1.00;
      Serial.print("GM4 = ");
      Serial.println(GM4);
    }
    else if (Y == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GM4 = 1.01;
      Serial.print("GM4 = ");
      Serial.println(GM4);
    }
    else
    {
      GM4 = atof(buffer6); //รับค่าbuffer6 มาเก็บไว้ที่GM4
      Serial.print("GM4 = ");
      Serial.println(GM4, 3);
    }

    String Z = String(buffer7);
    Serial.print("Z = ");
    Serial.println(Z);

    if (Z == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GF4 = 0.993;
      Serial.print("GF4 = ");
      Serial.println(GF4, 3);
    }
    else if (Z == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GF4 = 1.39;
      Serial.print("GF4 = ");
      Serial.println(GF4);
    }
    else if (Z == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GF4 = 1.00;
      Serial.print("GF4 = ");
      Serial.println(GF4);
    }
    else if (Z == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GF4 = 1.01;
      Serial.print("GF4 = ");
      Serial.println(GF4);
    }
    else
    {
      GF4 = atof(buffer7); //รับค่าbuffer7 มาเก็บไว้ที่GF4
      Serial.print("GF4 = ");
      Serial.println(GF4, 3);
    }

    FS4 = atof(number6); //รับค่าnumber6 มาเก็บไว้ทีFS4
    Serial.print("FS4 = ");
    Serial.println(FS4, 4);

    SP4 = atof(number7);  //รับค่าnumber7 มาเก็บไว้ทีSP4
    Serial.print("SP4 = ");
    Serial.println(SP4, 4);

    if (SP4 > FS4) //ถ้าSP4 มีค่ามากกว่า FS4 ให้โชว์หน้าที่30
    {
      callPage("30");
      G = 0;
      voltage4(G); //Set DAC voltage
      Serial.print("G = ");
      Serial.println(G);
    }
    else
    {
      callPage("38");

      // ----------------------------------------------------------------------
      // Part Calculate Channel 4
      // ----------------------------------------------------------------------
      FSN4 = ( GF4 / GM4 ) * FS4  ; //รับค่าGF4,GM4และFS4มาคำนวณ แล้วเก็บค่าไว้ที่FSN4
      Serial.print("FSN4(sccm) = ");
      Serial.println(FSN4);

      SPN4 = ( FSN4 / FS4 ) * SP4 ; //รับค่าFSN4,FS4และSP4มาคำนวณ แล้วเก็บค่าไว้ที่SPN4
      if (SPN4 > FSN4) //ถ้าSPN4 มีค่ามากกว่า FSN4 ให้ SPN4 = FSN4
      {
        SPN4 = FSN4;
      }
      Serial.print("SPN4 = ");
      Serial.println(SPN4);
      Serial.println(SPN4, BIN);
      
      G = ( 4095 * SPN4 ) / FSN4 ; //แปลงค่าSPN4ให้อยู่ในช่วง 0-4095 byte 
      voltage4(G); //Set DAC voltage
      Serial.print("G = ");
      Serial.println(G, BIN);
      Serial.println(G);
       
      F = ( FSN4 * G ) / 4095 ; //แปลงช่วง 0-4095 ให้อยู่ในค่าFSN4
      Serial.print("F(sccm) = ");
      Serial.println(F);
      Serial.println("_______________________________ END CHANNEL 4 _______________________________");
      Serial.println("End ask.");

      ADC4 = true;
    }
  }
}
void TimingStop1 (boolean _flag)
{
  if (_flag)
  {
    ADC1 = false;
    BlinkLED1 = false;
    TimingLED1 = false;
    T_LED = 0;
    state = 0;
    A = 0;
    voltage1(A); //Set DAC voltage
    setText("t353", "0"); //โชว์ข้อความ"0" ในTextboxที่t353
    setText("t350", "0"); //โชว์ข้อความ"0" ในTextboxที่t350
    setText("t351", "0"); //โชว์ข้อความ"0" ในTextboxที่t351
    setText("t352", "0"); //โชว์ข้อความ"0" ในTextboxที่t352
    digitalWrite(led, LOW);
    Serial.println("LED : OFF");
  }
}
void TimingStop2 (boolean _flag)
{
  if (_flag)
  {
    ADC2 = false;
    BlinkLED2 = false;
    TimingLED2 = false;
    T_LED = 0;
    state = 0;
    C = 0;
    voltage2(C); //Set DAC voltage
    setText("t363", "0"); //โชว์ข้อความ"0" ในTextboxที่t363
    setText("t360", "0"); //โชว์ข้อความ"0" ในTextboxที่t360
    setText("t361", "0"); //โชว์ข้อความ"0" ในTextboxที่t361
    setText("t362", "0"); //โชว์ข้อความ"0" ในTextboxที่t362
    digitalWrite(led, LOW);
    Serial.println("LED : OFF");
  }
}
void TimingStop3 (boolean _flag)
{
  if (_flag)
  {
    ADC3 = false;
    BlinkLED3 = false;
    TimingLED3 = false;
    T_LED = 0;
    state = 0;
    E = 0;
    voltage3(E); //Set DAC voltage
    setText("t373", "0"); //โชว์ข้อความ"0" ในTextboxที่t373
    setText("t370", "0"); //โชว์ข้อความ"0" ในTextboxที่t370
    setText("t371", "0"); //โชว์ข้อความ"0" ในTextboxที่t371
    setText("t372", "0"); //โชว์ข้อความ"0" ในTextboxที่t372
    digitalWrite(led, LOW);
    Serial.println("LED : OFF");
  }
}
void TimingStop4 (boolean _flag)
{
  if (_flag)
  {
    ADC4 = false;
    BlinkLED4 = false;
    TimingLED4 = false;
    T_LED = 0;
    state = 0;
    G = 0;
    voltage4(G); //Set DAC voltage
    setText("t383", "0"); //โชว์ข้อความ"0" ในTextboxที่t383
    setText("t380", "0"); //โชว์ข้อความ"0" ในTextboxที่t380
    setText("t381", "0"); //โชว์ข้อความ"0" ในTextboxที่t381
    setText("t382", "0"); //โชว์ข้อความ"0" ในTextboxที่t382
    digitalWrite(led, LOW);
    Serial.println("LED : OFF");
  }
}
void checkChannel1(boolean _flag)
{
  if (_flag)
  {
    Serial.println();
    Serial.println("Ask entry scale.");

    // ----------------------------------------------------------------------
    // Channel 1
    // ----------------------------------------------------------------------
    callPage("2");
    memset(buffer, 0, sizeof(buffer)); 
    memset(buffer1, 0, sizeof(buffer1));
    len_buff = getText("t21", buffer, sizeof(buffer)); //รับค่าจากTextbox"t21"มาโชว์ที่len_buff
    len_buff1 = getText("t22", buffer1, sizeof(buffer1)); //รับค่าจากTextbox"t22"มาโชว์ที่len_buff1
    callPage("11");
    memset(number, 0, sizeof(number));
    memset(number1, 0, sizeof(number1));
    len_num = getText("t111", number, sizeof(number)); //รับค่าจากTextbox"t111"มาโชว์ที่len_num
    len_num1 = getText("t112", number1, sizeof(number1)); //รับค่าจากTextbox"t112"มาโชว์ที่len_num1

    // ----------------------------------------------------------------------
    // Channel 1
    // ----------------------------------------------------------------------
#if PRINT_DEBUG
    Serial.print("Buffer[] = ");
    for (ibuff = 0; ibuff < len_buff; ibuff++)
    {
      Serial.print(buffer[ibuff]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Buffer1[] = ");
    for (ibuff1 = 0; ibuff1 < len_buff1; ibuff1++)
    {
      Serial.print(buffer1[ibuff1]);
    }
    Serial.println();
#endif

#if PRINT_DEBUG
    Serial.print("Number[] = ");
    for (inum = 0; inum < len_num; inum++)
    {
      Serial.print(number[inum]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Number1[] = ");
    for (inum1 = 0; inum1 < len_num1; inum1++)
    {
      Serial.print(number1[inum1]);
    }
    Serial.println();
#endif

    // ----------------------------------------------------------------------
    // Channel 1
    // ----------------------------------------------------------------------
    String S = String(buffer);
    Serial.print("S = ");
    Serial.println(S);

    if (S == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GM1 = 0.993;
      Serial.print("GM1 = ");
      Serial.println(GM1, 3);
    }
    else if (S == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GM1 = 1.39;
      Serial.print("GM1 = ");
      Serial.println(GM1);
    }
    else if (S == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GM1 = 1.00;
      Serial.print("GM1 = ");
      Serial.println(GM1);
    }
    else if (S == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GM1 = 1.01;
      Serial.print("GM1 = ");
      Serial.println(GM1);
    }
    else
    {
      GM1 = atof(buffer);
      Serial.print("GM1 = ");
      Serial.println(GM1, 3);
    }

    String T = String(buffer1);
    Serial.print("T = ");
    Serial.println(T);

    if (T == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GF1 = 0.993;
      Serial.print("GF1 = ");
      Serial.println(GF1, 3);
    }
    else if (T == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GF1 = 1.39;
      Serial.print("GF1 = ");
      Serial.println(GF1);
    }
    else if (T == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GF1 = 1.00;
      Serial.print("GF1 = ");
      Serial.println(GF1);
    }
    else if (T == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GF1 = 1.01;
      Serial.print("GF1 = ");
      Serial.println(GF1);
    }
    else
    {
      GF1 = atof(buffer1); //รับค่าbuffer1 มาเก็บไว้ที่GF1
      Serial.print("GF1 = ");
      Serial.println(GF1, 3);
    }

    FS1 = atof(number); //รับค่าnumber มาเก็บไว้ทีFS1
    Serial.print("FS1 = ");
    Serial.println(FS1);
    
    SP1 = atof(number1); //รับค่าnumber1 มาเก็บไว้ทีSP1
    Serial.print("SP1 = ");
    Serial.println(SP1);

    if (SP1 > FS1) //ถ้าSP1 มีค่ามากกว่า FS1 ให้โชว์หน้าที่27
    {
      callPage("27");
      A = 0;
      voltage1(A); //Set DAC voltage
      Serial.print("A = ");
      Serial.println(A);
    }
    else
    {
      callPage("22");

      // ----------------------------------------------------------------------
      // Part Calculate Channel 1
      // ----------------------------------------------------------------------
      FSN1 = ( GF1 / GM1 ) * FS1; //รับค่าGF1,GM1และFS1มาคำนวณ แล้วเก็บค่าไว้ที่FSN1
      Serial.print("FSN1(sccm) = ");
      Serial.println(FSN1);

      SPN1 = ( FSN1 / FS1 ) * SP1 ; //รับค่าFSN1,FS1และSP1มาคำนวณ แล้วเก็บค่าไว้ที่SPN1
      if (SPN1 > FSN1) //ถ้าSPN1 มีค่ามากกว่า FSN1 ให้ SPN1 = FSN1
      {
        SPN1 = FSN1;
      }
      Serial.print("SPN1 = ");
      Serial.println(SPN1);
 
      A = ( 4095 * SPN1 ) / FSN1 ; //แปลงค่าSPN1ให้อยู่ในช่วง 0-4095 byte   
      voltage1(A); //Set DAC voltage
      Serial.print("A = ");
      Serial.println(A, BIN);
      Serial.println(A);
      digitalWrite(led, HIGH);

      B = ( FSN1 * A ) / 4095 ; //แปลงช่วง 0-4095 ให้อยู่ในค่าFSN1
      Serial.print("B(sccm) = ");
      Serial.println(B);
      Serial.println("_______________________________ END CHANNEL 1 _______________________________");
      Serial.println("End ask.");

      ADC1 = true ;
      callPage("22");

    }
  }
}
void checkSTOP1(boolean _flag)
{
  if (_flag)
  {
    ADC1 = false;
    ADC1 = false;
    ADC1 = false;
    A = 0;
    voltage1(A); //Set DAC voltage
    Serial.print("A = ");
    Serial.println(A);
    setText("t4", "STOP1");

    MassflowtoNextion1 = 0;
    dtostrf(MassflowtoNextion1, 4, 2, sbuff1);
    Serial.print("sbuff1 = ");
    Serial.println(sbuff1);
    setText("t0", sbuff1); //โชว์ข้อความของค่าsubff1ที่เก็บไว้ ในTextboxที่t0
    digitalWrite(led, LOW);
  }
}
void checkChannel2(boolean _flag)
{
  if (_flag)
  {
    Serial.println();
    Serial.println("Ask entry scale.");

    // ----------------------------------------------------------------------
    // Channel 2
    // ----------------------------------------------------------------------
    callPage("3");
    memset(buffer2, 0, sizeof(buffer2));
    memset(buffer3, 0, sizeof(buffer3));
    len_buff2 = getText("t31", buffer2, sizeof(buffer2)); //รับค่าจากTextbox"t31"มาโชว์ที่len_buff2
    len_buff3 = getText("t32", buffer3, sizeof(buffer3)); //รับค่าจากTextbox"t32"มาโชว์ที่len_buff3
    callPage("12");
    memset(number2, 0, sizeof(number2));
    memset(number3, 0, sizeof(number3));
    len_num2 = getText("t121", number2, sizeof(number2)); //รับค่าจากTextbox"t121"มาโชว์ที่len_num2
    len_num3 = getText("t122", number3, sizeof(number3)); //รับค่าจากTextbox"t122"มาโชว์ที่len_num3

    // ----------------------------------------------------------------------
    // Channel 2
    // ----------------------------------------------------------------------

#if PRINT_DEBUG
    Serial.print("Buffer2[] = ");
    for (ibuff2 = 0; ibuff2 < len_buff2; ibuff2++)
    {
      Serial.print(buffer2[ibuff2]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Buffer3[] = ");
    for (ibuff3 = 0; ibuff3 < len_buff3; ibuff3++)
    {
      Serial.print(buffer3[ibuff3]);
    }
    Serial.println();
#endif

#if PRINT_DEBUG
    Serial.print("Number2[] = ");
    for (inum2 = 0; inum2 < len_num2; inum2++)
    {
      Serial.print(number2[inum2]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Number3[] = ");
    for (inum3 = 0; inum3 < len_num3; inum3++)
    {
      Serial.print(number3[inum3]);
    }
    Serial.println();
#endif

    // ----------------------------------------------------------------------
    // Channel 2
    // ----------------------------------------------------------------------

    String U = String(buffer2);
    Serial.print("U = ");
    Serial.println(U);

    if (U == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GM2 = 0.993;
      Serial.print("GM2 = ");
      Serial.println(GM2, 3);
    }
    else if (U == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GM2 = 1.39;
      Serial.print("GM2 = ");
      Serial.println(GM2);
    }
    else if (U == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GM2 = 1.00;
      Serial.print("GM2 = ");
      Serial.println(GM2);
    }
    else if (U == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GM2 = 1.01;
      Serial.print("GM2 = ");
      Serial.println(GM2);
    }
    else
    {
      GM2 = atof(buffer2); //รับค่าbuffer2 มาเก็บไว้ที่GM2
      Serial.print("GM2 = ");
      Serial.println(GM2, 3);
    }

    String V = String(buffer3);
    Serial.print("V = ");
    Serial.println(V);

    if (V == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GF2 = 0.993;
      Serial.print("GF2 = ");
      Serial.println(GF2, 3);
    }
    else if (V == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GF2 = 1.39;
      Serial.print("GF2 = ");
      Serial.println(GF2);
    }
    else if (V == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GF2 = 1.00;
      Serial.print("GF2 = ");
      Serial.println(GF2);
    }
    else if (V == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GF2 = 1.01;
      Serial.print("GF2 = ");
      Serial.println(GF2);
    }
    else
    {
      GF2 = atof(buffer3); //รับค่าbuffer3 มาเก็บไว้ที่GF2
      Serial.print("GF2 = ");
      Serial.println(GF2, 3);
    }

    FS2 = atof(number2); //รับค่าbuffer3 มาเก็บไว้ที่GF2
    Serial.print("FS2 = ");
    Serial.println(FS2, 4);

    SP2 = atof(number3); //รับค่าnumber3 มาเก็บไว้ทีSP2
    Serial.print("SP2 = ");
    Serial.println(SP2, 4);

    if (SP2 > FS2) //ถ้าSP1 มีค่ามากกว่า FS1 ให้โชว์หน้าที่28
    {
      callPage("28");
      C = 0;
      voltage2(C);   //Set DAC voltage
      Serial.print("C = ");
      Serial.println(C);
    }
    else
    {
      callPage("22");

      // ----------------------------------------------------------------------
      // Part Calculate Channel 2
      // ----------------------------------------------------------------------

      FSN2 = ( GF2 / GM2 ) * FS2  ;  //รับค่าGF2,GM2และFS2มาคำนวณ แล้วเก็บค่าไว้ที่FSN2
      Serial.print("FSN2(sccm) = ");
      Serial.println(FSN2);

      SPN2 = ( FSN2 / FS2 ) * SP2 ; //รับค่าFSN2,FS2และSP2มาคำนวณ แล้วเก็บค่าไว้ที่SPN2
      if (SPN2 > FSN2) //ถ้าSPN2 มีค่ามากกว่า FSN2 ให้ SPN2 = FSN2
      {
        SPN2 = FSN2;
      }
      Serial.print("SPN2 = ");
      Serial.println(SPN2);
     
      C = ( 4095 * SPN2 ) / FSN2 ; //แปลงค่าSPN2ให้อยู่ในช่วง 0-4095 byte 
      voltage2(C); //Set DAC voltage
      Serial.print("C = ");
      Serial.println(C, BIN);
      Serial.println(C);
     
      D = ( FSN2 * C ) / 4095 ; //แปลงช่วง 0-4095 ให้อยู่ในค่าFSN2
      Serial.print("D(sccm) = ");
      Serial.println(D);
      Serial.println("_______________________________ END CHANNEL 2 _______________________________");
      Serial.println("End ask.");

      ADC2 = true;
      callPage("22");
    }
  }
}
void checkSTOP2(boolean _flag)
{
  if (_flag)
  {
    ADC2 = false ;
    ADC2 = false ;
    ADC2 = false ;
    C = 0;
    voltage2(C);   //Set DAC voltage
    Serial.print("C = ");
    Serial.println(C);
    setText("t5", "STOP2");

    MassflowtoNextion2 = 0;
    dtostrf(MassflowtoNextion2, 4, 2, sbuff2);
    Serial.print("sbuff2 = ");
    Serial.println(sbuff2);
    setText("t1", sbuff2); //โชว์ข้อความของค่าsubff2ที่เก็บไว้ ในTextboxที่t1
  }
}
void checkChannel3(boolean _flag)
{
  if (_flag)
  {
    Serial.println();
    Serial.println("Ask entry scale.");

    // ----------------------------------------------------------------------
    // Channel 3
    // ----------------------------------------------------------------------
    callPage("4");
    memset(buffer4, 0, sizeof(buffer4));
    memset(buffer5, 0, sizeof(buffer5));
    len_buff4 = getText("t41", buffer4, sizeof(buffer4)); //รับค่าจากTextbox"t41"มาโชว์ที่len_buff4
    len_buff5 = getText("t42", buffer5, sizeof(buffer5)); //รับค่าจากTextbox"t42"มาโชว์ที่len_buff5
    callPage("13");
    memset(number4, 0, sizeof(number4));
    memset(number5, 0, sizeof(number5));
    len_num4 = getText("t131", number4, sizeof(number4)); //รับค่าจากTextbox"t131"มาโชว์ที่len_num4
    len_num5 = getText("t132", number5, sizeof(number5)); //รับค่าจากTextbox"t132"มาโชว์ที่len_num5

    // ----------------------------------------------------------------------
    // Channe3
    // ----------------------------------------------------------------------
#if PRINT_DEBUG
    Serial.print("Buffer4[] = ");
    for (ibuff4 = 0; ibuff4 < len_buff4; ibuff4++)
    {
      Serial.print(buffer4[ibuff4]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Buffer5[] = ");
    for (ibuff5 = 0; ibuff5 < len_buff5; ibuff5++)
    {
      Serial.print(buffer5[ibuff5]);
    }
    Serial.println();
#endif

#if PRINT_DEBUG
    Serial.print("Number4[] = ");
    for (inum4 = 0; inum4 < len_num4; inum4++)
    {
      Serial.print(number4[inum4]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Number5[] = ");
    for (inum5 = 0; inum5 < len_num5; inum5++)
    {
      Serial.print(number5[inum5]);
    }
    Serial.println();
#endif

    // ----------------------------------------------------------------------
    // Channel 3
    // ----------------------------------------------------------------------
    String W = String(buffer4);
    Serial.print("W = ");
    Serial.println(W);

    if (W == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GM3 = 0.993;
      Serial.print("GM3 = ");
      Serial.println(GM3, 3);
    }
    else if (W == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GM3 = 1.39;
      Serial.print("GM3 = ");
      Serial.println(GM3);
    }
    else if (W == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GM3 = 1.00;
      Serial.print("GM3 = ");
      Serial.println(GM3);
    }
    else if (W == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GM3 = 1.01;
      Serial.print("GM3 = ");
      Serial.println(GM3);
    }
    else
    {
      GM3 = atof(buffer4);  //รับค่าbuffer4 มาเก็บไว้ที่GM3
      Serial.print("GM3 = ");
      Serial.println(GM3, 3);
    }

    String X = String(buffer5);
    Serial.print("X = ");
    Serial.println(X);

    if (X == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GF3 = 0.993;
      Serial.print("GF3 = ");
      Serial.println(GF3, 3);
    }
    else if (X == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GF3 = 1.39;
      Serial.print("GF3 = ");
      Serial.println(GF3);
    }
    else if (X == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GF3 = 1.00;
      Serial.print("GF3 = ");
      Serial.println(GF3);
    }
    else if (X == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GF3 = 1.01;
      Serial.print("GF3 = ");
      Serial.println(GF3);
    }
    else
    {
      GF3 = atof(buffer5); //รับค่าbuffer5 มาเก็บไว้ที่GF3
      Serial.print("GF3 = ");
      Serial.println(GF3, 3);
    }

    FS3 = atof(number4); //รับค่าnumber4 มาเก็บไว้ทีFS3
    Serial.print("FS3 = ");
    Serial.println(FS3);

    SP3 = atof(number5); //รับค่าnumber5 มาเก็บไว้ทีSP3
    Serial.print("SP3 = ");
    Serial.println(SP3);

    if (SP3 > FS3) //ถ้าSP3 มีค่ามากกว่า FS3 ให้โชว์หน้าที่29
    {
      callPage("29");
      E = 0;
      voltage3(E); //Set DAC voltage
      Serial.print("E = ");
      Serial.println(E);
    }
    else
    {
      callPage("22");
      // ----------------------------------------------------------------------
      // Part Calculate Channel 3
      // ----------------------------------------------------------------------

      FSN3 = ( GF3 / GM3 ) * FS3  ; //รับค่าGF3,GM3และFS3มาคำนวณ แล้วเก็บค่าไว้ที่FSN3
      Serial.print("FSN3(sccm) = ");
      Serial.println(FSN3);

      SPN3 = ( FSN3 / FS3 ) * SP3 ; //รับค่าFSN3,FS3และSP3มาคำนวณ แล้วเก็บค่าไว้ที่SPN3
      if (SPN3 > FSN3) //รับค่าFSN3,FS3และSP3มาคำนวณ แล้วเก็บค่าไว้ที่SPN3
      {
        SPN3 = FSN3;
      }
      Serial.print("SPN3 = ");
      Serial.println(SPN3);
      
      E = ( 4095 * SPN3 ) / FSN3 ; //แปลงค่าSPN3ให้อยู่ในช่วง 0-4095 byte 
      voltage3(E);//Set DAC voltage
      Serial.print("E = ");
      Serial.println(E, BIN);
      Serial.println(E);
       
      F = ( FSN3 * E ) / 4095 ; //แปลงช่วง 0-4095 ให้อยู่ในค่าFSN3
      Serial.print("F(sccm) = ");
      Serial.println(F);
      Serial.println("_______________________________ END CHANNEL 3 _______________________________");
      Serial.println("End ask.");

      ADC3 = true ;
      callPage("22");
    }
  }
}
void checkSTOP3(boolean _flag)
{
  if (_flag)
  {
    ADC3 = false ;
    ADC3 = false ;
    ADC3 = false ;
    E = 0;
    voltage3(E); //Set DAC voltage
    Serial.print("E = ");
    Serial.println(E);
    setText("t6", "STOP3");

    MassflowtoNextion3 = 0;
    dtostrf(MassflowtoNextion3, 4, 2, sbuff3);
    Serial.print("sbuff3 = ");
    Serial.println(sbuff3);
    setText("t2", sbuff3); //โชว์ข้อความของค่าsubff3ที่เก็บไว้ ในTextboxที่t2
  }
}
void checkChannel4(boolean _flag)
{
  if (_flag)
  {
    Serial.println();
    Serial.println("Ask entry scale.");

    // ----------------------------------------------------------------------
    // Channel 4
    // ----------------------------------------------------------------------
    callPage("5");
    memset(buffer6, 0, sizeof(buffer6));
    memset(buffer7, 0, sizeof(buffer7));
    len_buff6 = getText("t51", buffer6, sizeof(buffer6)); //รับค่าจากTextbox"t51"มาโชว์ที่len_buff6
    len_buff7 = getText("t52", buffer7, sizeof(buffer7)); //รับค่าจากTextbox"t52"มาโชว์ที่len_buff7
    callPage("14");
    memset(number6, 0, sizeof(number6));
    memset(number7, 0, sizeof(number7));
    len_num6 = getText("t141", number6, sizeof(number6)); //รับค่าจากTextbox"t141"มาโชว์ที่len_num6
    len_num7 = getText("t142", number7, sizeof(number7)); //รับค่าจากTextbox"t142"มาโชว์ที่len_num7

    // ----------------------------------------------------------------------
    // Channel 4
    // ----------------------------------------------------------------------
#if PRINT_DEBUG
    Serial.print("Buffer6[] = ");
    for (ibuff6 = 0; ibuff6 < len_buff6; ibuff6++)
    {
      Serial.print(buffer6[ibuff6]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Buffer7[] = ");
    for (ibuff7 = 0; ibuff7 < len_buff7; ibuff7++)
    {
      Serial.print(buffer7[ibuff7]);
    }
    Serial.println();
#endif

#if PRINT_DEBUG
    Serial.print("Number6[] = ");
    for (inum6 = 0; inum6 < len_num6; inum6++)
    {
      Serial.print(number6[inum6]);
    }
    Serial.println();
#endif
#if PRINT_DEBUG
    Serial.print("Number7[] = ");
    for (inum7 = 0; inum7 < len_num7; inum7++)
    {
      Serial.print(number7[inum7]);
    }
    Serial.println();
#endif

    // ----------------------------------------------------------------------
    // Channel 4
    // ----------------------------------------------------------------------
    String Y = String(buffer6);
    Serial.print("Y = ");
    Serial.println(Y);

    if (Y == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GM4 = 0.993;
      Serial.print("GM4 = ");
      Serial.println(GM4, 3);
    }
    else if (Y == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GM4 = 1.39;
      Serial.print("GM4 = ");
      Serial.println(GM4);
    }
    else if (Y == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GM4 = 1.00;
      Serial.print("GM4 = ");
      Serial.println(GM4);
    }
    else if (Y == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GM4 = 1.01;
      Serial.print("GM4 = ");
      Serial.println(GM4);
    }
    else
    {
      GM4 = atof(buffer6); //รับค่าbuffer6 มาเก็บไว้ที่GM4
      Serial.print("GM4 = ");
      Serial.println(GM4, 3);
    }

    String Z = String(buffer7);
    Serial.print("Z = ");
    Serial.println(Z);

    if (Z == "O2")
    {
      float O2 = 0.993;
      Serial.print("O2 = ");
      Serial.println(O2);
      GF4 = 0.993;
      Serial.print("GF4 = ");
      Serial.println(GF4, 3);
    }
    else if (Z == "Ar")
    {
      float Ar = 1.39;
      Serial.print("Ar = ");
      Serial.println(Ar);
      GF4 = 1.39;
      Serial.print("GF4 = ");
      Serial.println(GF4);
    }
    else if (Z == "N2")
    {
      float N2 = 1.00;
      Serial.print("N2 = ");
      Serial.println(N2);
      GF4 = 1.00;
      Serial.print("GF4 = ");
      Serial.println(GF4);
    }
    else if (Z == "H2")
    {
      float H2 = 1.01;
      Serial.print("H2 = ");
      Serial.println(H2);
      GF4 = 1.01;
      Serial.print("GF4 = ");
      Serial.println(GF4);
    }
    else
    {
      GF4 = atof(buffer7); //รับค่าbuffer7 มาเก็บไว้ที่GF4
      Serial.print("GF4 = ");
      Serial.println(GF4, 3);
    }

    FS4 = atof(number6); //รับค่าnumber6 มาเก็บไว้ทีFS4
    Serial.print("FS4 = ");
    Serial.println(FS4, 4);

    SP4 = atof(number7);  //รับค่าnumber7 มาเก็บไว้ทีSP4
    Serial.print("SP4 = ");
    Serial.println(SP4, 4);

    if (SP4 > FS4) //ถ้าSP4 มีค่ามากกว่า FS4 ให้โชว์หน้าที่30
    {
      callPage("30");
      G = 0;
      voltage4(G); //Set DAC voltage
      Serial.print("G = ");
      Serial.println(G);
    }
    else
    {
      callPage("22");

      // ----------------------------------------------------------------------
      // Part Calculate Channel 4
      // ----------------------------------------------------------------------
      FSN4 = ( GF4 / GM4 ) * FS4  ; //รับค่าGF4,GM4และFS4มาคำนวณ แล้วเก็บค่าไว้ที่FSN4
      Serial.print("FSN4(sccm) = ");
      Serial.println(FSN4);

      SPN4 = ( FSN4 / FS4 ) * SP4 ; //รับค่าFSN4,FS4และSP4มาคำนวณ แล้วเก็บค่าไว้ที่SPN4
      if (SPN4 > FSN4) //ถ้าSPN4 มีค่ามากกว่า FSN4 ให้ SPN4 = FSN4
      {
        SPN4 = FSN4;
      }
      Serial.print("SPN4 = ");
      Serial.println(SPN4);
      Serial.println(SPN4, BIN);
       
      G = ( 4095 * SPN4 ) / FSN4 ; //แปลงค่าSPN4ให้อยู่ในช่วง 0-4095 byte 
      voltage4(G); //Set DAC voltage
      Serial.print("G = ");
      Serial.println(G, BIN);
      Serial.println(G);
      
      F = ( FSN4 * G ) / 4095 ; //แปลงช่วง 0-4095 ให้อยู่ในค่าFSN4
      Serial.print("F(sccm) = ");
      Serial.println(F);
      Serial.println("_______________________________ END CHANNEL 4 _______________________________");
      Serial.println("End ask.");

      ADC4 = true ;
      callPage("22");
    }
  }
}
void checkSTOP4(boolean _flag)
{
  if (_flag)
  {
    ADC4 = false ;
    ADC4 = false ;
    ADC4 = false ;
    G = 0;
    voltage4(G); //Set DAC voltage
    Serial.print("G = ");
    Serial.println(G);
    setText("t7", "STOP4");

    MassflowtoNextion4 = 0;
    dtostrf(MassflowtoNextion4, 4, 2, sbuff4);
    Serial.print("sbuff4 = ");
    Serial.println(sbuff4);
    setText("t3", sbuff4); //โชว์ข้อความของค่าsubff4ที่เก็บไว้ ในTextboxที่t3
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
      //ADC1 = false;
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
      dataBuff[byteIdx] = (byte)incomingChar; //ให้เก็บค่าของincomingCharมาใส่ที่dataBuff


#if PRINT_NEXTION_COMMU
      Serial.print("Data stored at byte IDX = ");
      Serial.println(byteIdx, DEC);
      Serial.println();
#endif
   // }

    if (byteIdx == 5) //ถ้ารับค่ามาเก็บ5ตัวให้ทำตามในวงเล็บต่อ
    {
      if (dataBuff[3] == 0xFF && dataBuff[4] == 0xFF && dataBuff[5] == 0xFF) //ถ้ารับรหัสFF FF FFกลับมาให้ทำตามในวงเล็บต่อ
      {
        nextionEtxCome = true; //ให้nextionEtxCome เป็นจริง

#if PRINT_NEXTION_COMMU
        Serial.println("ETX Come.........................");
        Serial.println();
#endif
      }
    }
  }
    byteIdx++;
    if (5 < byteIdx) byteIdx = 5;
	
	
    
  }
}
// ----------------------------------------------------------------------
// Task resetNextionStxCome
// ----------------------------------------------------------------------
void resetNextionStxCome()
{
  if (nextionStxCome)
  {
    nextionStxCome = false;

#if PRINT_NEXTION_COMMU
    Serial.println("Reset STX. Command expired."); //ปริ๊นข้อความใน""
    Serial.println();
#endif
  }
}
// ----------------------------------------------------------------------
// Task resetNextionEtxCome
// ----------------------------------------------------------------------
void resetNextionEtxCome()
{
  int iii;
  if (nextionEtxCome)
  {
    // nextionStxCome = false;
    nextionEtxCome = false;
    //for(iii=0;iii<6;iii++)
    //dataBuff[iii] = 0x00;

#if PRINT_NEXTION_COMMU
    Serial.println("Reset ETX. Command expired."); //ปริ๊นข้อความใน""
    Serial.println();
#endif
  }
}
//##############################################################################
//                             PROCEDURES OR FUNCTIONS
//##############################################################################
// ----------------------------------------------------------------------
// Task Measure Flow 1
// ----------------------------------------------------------------------
void taskMeasureFlow1(boolean _flag)
{
  if (_flag)
  {
    if (millis() > Showvalue1)
    {
      Showvalue1 = 2000 + millis();
      Serial.print("Showvalu1e1: ");
      Serial.println(Showvalue1);
      stateValue1 = !stateValue1 ;
      if (stateValue1 == 1)
      {
        analogValue1 = analogRead(A1);
        Serial.print("analogValue1 = ");
        Serial.println(analogValue1);

        V_ch1 = ( 5.0 / 1023 ) * analogValue1;
        Serial.print("Vout(V_ch1) = ");
        Serial.println(V_ch1);

        VtoSccm_1 = ( FSN1 / 5.0 ) * V_ch1;
        Serial.print("VtoSccm_1 = ");
        Serial.println(VtoSccm_1);
        delay(100);

        dtostrf( VtoSccm_1, 4, 2, sbuff1);
        Serial.print("sbuff1 = ");
        Serial.println(sbuff1);
        setText("t353", sbuff1);
        setText("t0", sbuff1);

      }
      /*else
        {
        analogValue11 = analogRead(A2);
        Serial.print("analogValue11 = ");
        Serial.println(analogValue11);
        }  */  
		
    }
	
	/*taskADC1_CNT++;
    if ((1000 / INTERVAL) <= taskADC1_CNT) // 500ms/10ms = 50 counts ==> 500ms ON 500ms OFF
    {
      taskADC1_CNT = 0; // Reset counter <--

      // led Mission
       stateValue1 = !stateValue1 ;
      if (stateValue1 == 1)
      {
        analogValue1 = analogRead(A1);
        Serial.print("analogValue1 = ");
        Serial.println(analogValue1);

        V_ch1 = ( 5.0 / 1023 ) * analogValue1;
        Serial.print("Vout(V_ch1) = ");
        Serial.println(V_ch1);

        VtoSccm_1 = ( FSN1 / 5.0 ) * V_ch1;
        Serial.print("VtoSccm_1 = ");
        Serial.println(VtoSccm_1);
        delay(100);

        dtostrf( VtoSccm_1, 4, 2, sbuff1);
        Serial.print("sbuff1 = ");
        Serial.println(sbuff1);
        setText("t353", sbuff1);
        setText("t0", sbuff1);

      }     
      
    }*/
  }
}
void taskMeasureFlow2(boolean _flag)
{
  if (_flag)
  {
    if (millis() > Showvalue2)
    {
      Showvalue2 = 1000 + millis();
      Serial.print("Showvalue2: ");
      Serial.println(Showvalue2);
      stateValue2 = !stateValue2 ;
      if (stateValue2 == 1)
      {
        analogValue2 = analogRead(A2);
        Serial.print("analogValue2 = ");
        Serial.println(analogValue2);

        V_ch2 = ( 5.0 / 1023 ) * analogValue2;
        Serial.print("Vout(V_ch2) = ");
        Serial.println(V_ch2);

        VtoSccm_2 = ( FSN2 / 5.0 ) * V_ch2;
        Serial.print("VtoSccm_2 = ");
        Serial.println(VtoSccm_2);
        delay(100);

        dtostrf( VtoSccm_2, 4, 2, sbuff2);
        Serial.print("sbuff2 = ");
        Serial.println(sbuff2);
        setText("t1", sbuff2);
        setText("t363", sbuff1);
      }
      /*else
        {
        analogValue11 = analogRead(A2);
        Serial.print("analogValue11 = ");
        Serial.println(analogValue11);
        }    */
    }
	
	/*taskADC2_CNT++;
    if ((1000 / INTERVAL) <= taskADC2_CNT) // 500ms/10ms = 50 counts ==> 500ms ON 500ms OFF
    {
      taskADC2_CNT = 0; // Reset counter <--

      // led Mission
       stateValue2 = !stateValue2 ;
      if (stateValue2 == 1)
      {
        analogValue2 = analogRead(A2);
        Serial.print("analogValue2 = ");
        Serial.println(analogValue2);

        V_ch2 = ( 5.0 / 1023 ) * analogValue2;
        Serial.print("Vout(V_ch2) = ");
        Serial.println(V_ch2);

        VtoSccm_2 = ( FSN2 / 5.0 ) * V_ch2;
        Serial.print("VtoSccm_2 = ");
        Serial.println(VtoSccm_2);
        delay(100);

        dtostrf( VtoSccm_2, 4, 2, sbuff2);
        Serial.print("sbuff2 = ");
        Serial.println(sbuff2);
        setText("t1", sbuff2);
        setText("t363", sbuff1);

      }     
      
    }*/
  }
}
void taskMeasureFlow3(boolean _flag)
{
  if (_flag)
  {
    if (millis() > Showvalue3)
    {
      Showvalue3 = 1000 + millis();
      Serial.print("Showvalue3: ");
      Serial.println(Showvalue3);
      stateValue3 = !stateValue3 ;
      if (stateValue3 == 1)
      {
        analogValue3 = analogRead(A3);
        Serial.print("analogValue3 = ");
        Serial.println(analogValue3);

        V_ch3 = ( 5.0 / 1023 ) * analogValue3;
        Serial.print("Vout(V_ch3) = ");
        Serial.println(V_ch3);

        VtoSccm_3 = ( FSN3 / 5.0 ) * V_ch3;
        Serial.print("VtoSccm_3 = ");
        Serial.println(VtoSccm_3);
        delay(100);

        dtostrf( VtoSccm_3, 4, 2, sbuff3);
        Serial.print("sbuff3 = ");
        Serial.println(sbuff3);
        setText("t2", sbuff3);
        setText("t373", sbuff1);
      }
      /*else
        {
        analogValue11 = analogRead(A2);
        Serial.print("analogValue11 = ");
        Serial.println(analogValue11);
        }   */ 
    }
	/*taskADC3_CNT++;
    if ((1000 / INTERVAL) <= taskADC3_CNT) // 500ms/10ms = 50 counts ==> 500ms ON 500ms OFF
    {
      taskADC3_CNT = 0; // Reset counter <--

      // led Mission
       stateValue3 = !stateValue3 ;
      if (stateValue3 == 1)
      {
        analogValue3 = analogRead(A3);
        Serial.print("analogValue3 = ");
        Serial.println(analogValue3);

        V_ch3 = ( 5.0 / 1023 ) * analogValue3;
        Serial.print("Vout(V_ch3) = ");
        Serial.println(V_ch3);

        VtoSccm_3 = ( FSN3 / 5.0 ) * V_ch3;
        Serial.print("VtoSccm_3 = ");
        Serial.println(VtoSccm_3);
        delay(100);

        dtostrf( VtoSccm_3, 4, 2, sbuff3);
        Serial.print("sbuff3 = ");
        Serial.println(sbuff3);
        setText("t2", sbuff3);
        setText("t373", sbuff1);

      }     
      
    }*/
  }
}
void taskMeasureFlow4(boolean _flag)
{
  if (_flag)
  {
    if (millis() > Showvalue4)
    {
      Showvalue4 = 1000 + millis();
      Serial.print("Showvalue4: ");
      Serial.println(Showvalue4);
      stateValue4 = !stateValue4 ;
      if (stateValue4 == 1)
      {
        analogValue4 = analogRead(A4);
        Serial.print("analogValue4 = ");
        Serial.println(analogValue4);

        V_ch4 = ( 5.0 / 1023 ) * analogValue4;
        Serial.print("Vout(V_ch4) = ");
        Serial.println(V_ch4);

        VtoSccm_4 = ( FSN4 / 5.0 ) * V_ch4;
        Serial.print("VtoSccm_4 = ");
        Serial.println(VtoSccm_4);
        delay(100);

        dtostrf( VtoSccm_4, 4, 2, sbuff4);
        Serial.print("sbuff4 = ");
        Serial.println(sbuff4);
        setText("t3", sbuff4);
        setText("t383", sbuff1);
      }
      /*else
        {
        analogValue11 = analogRead(A2);
        Serial.print("analogValue11 = ");
        Serial.println(analogValue11);
        }  */  
    }
	/*taskADC4_CNT++;
    if ((1000 / INTERVAL) <= taskADC4_CNT) // 500ms/10ms = 50 counts ==> 500ms ON 500ms OFF
    {
      taskADC4_CNT = 0; // Reset counter <--

      // led Mission
       stateValue4 = !stateValue4 ;
      if (stateValue4 == 1)
      {
        analogValue4 = analogRead(A4);
        Serial.print("analogValue4 = ");
        Serial.println(analogValue4);

        V_ch4 = ( 5.0 / 1023 ) * analogValue4;
        Serial.print("Vout(V_ch4) = ");
        Serial.println(V_ch4);

        VtoSccm_4 = ( FSN4 / 5.0 ) * V_ch4;
        Serial.print("VtoSccm_4 = ");
        Serial.println(VtoSccm_4);
        delay(100);

        dtostrf( VtoSccm_4, 4, 2, sbuff4);
        Serial.print("sbuff4 = ");
        Serial.println(sbuff4);
        setText("t3", sbuff4);
        setText("t383", sbuff1);

      }     
      
    }*/
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
    if ((MY_TIME_BLINK / INTERVAL) <= taskBlink_CNT) // 500ms/10ms = 50 counts ==> 500ms ON 500ms OFF
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
