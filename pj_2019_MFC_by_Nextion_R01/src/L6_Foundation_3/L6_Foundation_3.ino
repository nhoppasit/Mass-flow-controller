#define PRINT_NEXTION_COMMU 1
#define PRINT_DEBUG 1

//##############################################################################
//                             DECLARATIONS
//##############################################################################

#include "NextionHardware.h";
#include "NextionText.h";

#include "MCP4922.h"
#include <SPI.h>

MCP4922 DAC_A(51, 52, 34, 5); // (MOSI,SCK,CS,LDAC) define Connections for MEGA_board
MCP4922 DAC_B(51, 52, 53, 5); // (MOSI,SCK,CS,LDAC) define Connections for MEGA_board

// ----------------------------------------------------------------------
// Channel 1
// ----------------------------------------------------------------------
float Vout_1;
float Vout_sccm_FS_1;
float Vout_sccm_SP_1;
float FSNN1;
float FSN1; //Full Scale New 1
float SPN1; //Set Point New 1
float Flowrate1, Flowout1;
float FS1; //Full Scale 1
float SP1; //Set Point 1
float GF1; // Type of gas 1
float GM1; // Gas of massflow 1
float A;
float B;
int analogValue1;

// ----------------------------------------------------------------------
// Channel 2
// ----------------------------------------------------------------------
float Vout_2;
float Vout_sccm_FS_2;
float Vout_sccm_SP_2;
float FSN2; //Full Scale New 2
float SPN2; //Set Point New 2
float Flowrate2, Flowout2;
float FS2; //Full Scale 2
float SP2; //Set Point 2
float GF2; // Type of gas 2
float GM2; // Gas of massflow 2
float C;
float D;
int analogValue2;

// ----------------------------------------------------------------------
// Channel 3
// ----------------------------------------------------------------------
float Vout_3;
float Vout_sccm_FS_3;
float Vout_sccm_SP_3;
float FSN3; //Full Scale New 3
float SPN3; //Set Point New 3
float Flowrate3, Flowout3;
float FS3; //Full Scale 3
float SP3; //Set Point 3
float GF3; // Type of gas 3
float GM3; // Gas of massflow 3
float E;
float F;
int analogValue3;

// ----------------------------------------------------------------------
// Channel 4
// ----------------------------------------------------------------------
float Vout_4;
float Vout_sccm_FS_4;
float Vout_sccm_SP_4;
float FSN4; //Full Scale New 4
float SPN4; //Set Point New 4
float Flowrate4, Flowout4;
float FS4; //Full Scale 4
float SP4; //Set Point 4
float GF4; // Type of gas 4
float GM4; // Gas of massflow 4
float G;
float H;
int analogValue4;

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
//int MY_TIME_BLINK = 1000; //หน่วยความจำ
int MY_TIME_BLINK = 500;
boolean Blink = false; // ใช้จำสถานะไฟกระพริบ
int taskBlink_CNT; // จำเวลา [1,20] / C++[0,19]

int TIME_ADC1 = 500;
int taskADC1_CNT;
boolean ADC1 = false;
// ----------------------------------------------------------------------
// Serial communication variables
// ----------------------------------------------------------------------
char incomingChar;//หน่วยความจำ
int byteIdx;
boolean nextionStxCome, nextionEtxCome;
byte dataBuff[6];

// ----------------------------------------------------------------------
// Nextion variables ch1
// ----------------------------------------------------------------------
char buffer[100] = {0};
int len_buff;  // add
int ibuff;  // add
char buffer1[100] = {0};
int len_buff1;
int ibuff1;

char number[100] ;
int len_num;
int inum;
char number1[100] ;
int len_num1;
int inum1;

// ----------------------------------------------------------------------
// Nextion variables ch2
// ----------------------------------------------------------------------
char buffer2[100] = {0};
int len_buff2;  // add
int ibuff2;  // add
char buffer3[100] = {0};
int len_buff3;
int ibuff3;

char number2[100] ;
int len_num2;
int inum2;
char number3[100] ;
int len_num3;
int inum3;

// ----------------------------------------------------------------------
// Nextion variables ch3
// ----------------------------------------------------------------------
char buffer4[100] = {0};
int len_buff4;  // add
int ibuff4;  // add
char buffer5[100] = {0};
int len_buff5;
int ibuff5;

char number4[100] ;
int len_num4;
int inum4;
char number5[100] ;
int len_num5;
int inum5;

// ----------------------------------------------------------------------
// Nextion variables ch4
// ----------------------------------------------------------------------
char buffer6[100] = {0};
int len_buff6;  // add
int ibuff6;  // add
char buffer7[100] = {0};
int len_buff7;
int ibuff7;

char number6[100] ;
int len_num6;
int inum6;
char number7[100] ;
int len_num7;
int inum7;

// ----------------------------------------------------------------------
// Show Text After Massflow Process
// ----------------------------------------------------------------------
float V_ch1;
float VtoSccm_1;
char sbuff1[8];
double MassflowtoNextion1 ;
String value1;

float V_ch2;
float VtoSccm_2;
char sbuff2[8];
double MassflowtoNextion2 = 20;
String value2;

float V_ch3;
float VtoSccm_3;
char sbuff3[8];
double MassflowtoNextion3 = 20;
String value3;

float V_ch4;
float VtoSccm_4;
char sbuff4[8];
double MassflowtoNextion4 = 20;
String value4;

// ----------------------------------------------------------------------
// Select Voltage
// ----------------------------------------------------------------------
int pin = 10;
//int in = 7; // Coil
int val;
//##############################################################################
//                             SETUP
//##############################################################################
void setup() {

  systemInit();

  Serial.print("Software started. Hello PC.");

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  Serial.begin(115200);
  SPI.begin();
  
  pinMode(pin,OUTPUT);
 // pinMode(in,INPUT);
}
void voltage1(unsigned int A)
{
  DAC_A.Set(A, C);
}
void voltage2(unsigned int C)
{
  DAC_A.Set(A, C);
}
void voltage3(unsigned int E)
{
  DAC_B.Set(E, G);
}
void voltage4(unsigned int G)
{
  DAC_B.Set(E, G);
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
  taskMeasureFlow1(tick_state && ADC1);

  // ............................
  // NEXTION MISSIONS
  // ............................
  //taskIncBlinkPeriod(nextionEtxCome && dataBuff[0] == 0x01 && dataBuff[1] == 0x02 && dataBuff[2] == 0x00);
  //taskDecBlinkPeriod(nextionEtxCome && dataBuff[0] == 0x02 && dataBuff[1] == 0x02 && dataBuff[2] == 0x00);
  voltagecheck1(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x1F && dataBuff[1] == 0x02 && dataBuff[2] == 0x01); // 65 1F 02 01 FF FF FF
  voltagecheck2(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x1F && dataBuff[1] == 0x03 && dataBuff[2] == 0x01); // 65 1F 03 01 FF FF FF
  // ............................
  // CHECK STRAT
  // ............................
  checkChannel1(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x16 && dataBuff[1] == 0x0B && dataBuff[2] == 0x00); // 65 16 0B 00 FF FF FF ปุ่ม start ตรวจสอบค่า FullScale and SetPoint
  checkChannel2(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x16 && dataBuff[1] == 0x0C && dataBuff[2] == 0x00); // 65 16 0C 00 FF FF FF ปุ่ม start ตรวจสอบค่า FullScale and SetPoint
  checkChannel3(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x16 && dataBuff[1] == 0x0D && dataBuff[2] == 0x00); // 65 16 0D 00 FF FF FF ปุ่ม start ตรวจสอบค่า FullScale and SetPoint
  checkChannel4(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x16 && dataBuff[1] == 0x0E && dataBuff[2] == 0x00); // 65 16 0E 00 FF FF FF ปุ่ม start ตรวจสอบค่า FullScale and SetPoint

  // ............................
  // CHECK STOP
  // ............................
  checkSTOP1(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x16 && dataBuff[1] == 0x07 && dataBuff[2] == 0x00); // 65 16 07 00 FF FF FF ปุ่ม stop
  checkSTOP2(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x16 && dataBuff[1] == 0x08 && dataBuff[2] == 0x00); // 65 16 08 00 FF FF FF ปุ่ม stop
  checkSTOP3(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x16 && dataBuff[1] == 0x09 && dataBuff[2] == 0x00); // 65 16 09 00 FF FF FF ปุ่ม stop
  checkSTOP4(nextionStxCome && nextionEtxCome && dataBuff[0] == 0x16 && dataBuff[1] == 0x0A && dataBuff[2] == 0x00); // 65 16 0A 00 FF FF FF ปุ่ม stop

  
  resetNextionEtxCome();
}
void voltagecheck1 (boolean _flag) 
{
	if (_flag)
	{
		digitalWrite(pin, HIGH);
	}
}
void voltagecheck2 (boolean _flag) 
{
	if (_flag)
	{
		digitalWrite(pin, LOW);		
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
    len_buff = getText("t21", buffer, sizeof(buffer));
    len_buff1 = getText("t22", buffer1, sizeof(buffer1));
    callPage("11");
    memset(number, 0, sizeof(number));
    memset(number1, 0, sizeof(number1));
    len_num = getText("t111", number, sizeof(number));
    len_num1 = getText("t112", number1, sizeof(number1));

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
      GF1 = atof(buffer1);
      Serial.print("GF1 = ");
      Serial.println(GF1, 3);
    }

    FS1 = atof(number);
    Serial.print("FS1 = ");
    Serial.println(FS1);

    SP1 = 0;
    SP1 = atof(number1);
    Serial.print("SP1 = ");
    Serial.println(SP1);

    if (SP1 > FS1)
    {
      callPage("27");

      A = 0;
      voltage1(A); //Set DAC voltage
      Serial.print("A = ");
      Serial.println(A);

      // ----------------------------------------------------------------------
      // Part Show Value 1
      // ----------------------------------------------------------------------
      V_ch1 = ( 5.0 / 1023 ) * analogValue1;
      Serial.print("Vout(V_ch1) = ");
      Serial.println(V_ch1);

      VtoSccm_1 = ( SP1 / 5.0 ) * V_ch1;
      Serial.print("VtoSccm_1 = ");
      Serial.println(VtoSccm_1);
      delay(100);

      MassflowtoNextion1 = 0;
      dtostrf(MassflowtoNextion1, 4, 2, sbuff1);
      Serial.print("sbuff1 = ");
      Serial.println(sbuff1);
      setText("t0", sbuff1);
    }
    else
    {
      callPage("22");

      // ----------------------------------------------------------------------
      // Part Calculate Channel 1
      // ----------------------------------------------------------------------
      FSN1 = ( GF1 / GM1 ) * FS1;
      Serial.print("FSN1(sccm) = ");
      Serial.println(FSN1);

      SPN1 = ( FSN1 / FS1 ) * SP1 ;
      if (SPN1 > FSN1)
      {
        SPN1 = FSN1;
      }
      Serial.print("SPN1 = ");
      Serial.println(SPN1);

      //A = map( SPN1, 0, FSN1, 0, 4095);  //ฟังชั่นเที่ยบบรรหยัดไตรยางmassflow  กำหนด FS1 = 100 แปลง 0-100 ให้อยู่ในช่วง 0-4095 byte
	  A = ( 4095 * SPN1 ) / FSN1 ;
      voltage1(A); //Set DAC voltage
      Serial.print("A = ");
      Serial.println(A, BIN);
      Serial.println(A);

      //B = map( A, 0, 4095, 0, FSN1);  //กำหนด FS1 = 100 //แปลง 0-4095 ให้อยู่ในช่วง 0-100 sccm
	  B = ( FSN1 * A ) / 4095 ;
      Serial.print("B(sccm) = ");
      Serial.println(B);

      analogValue1 = analogRead(A2);  //  อ่านค่า input จากขาanalog A0
      Serial.print("analogValue1 = ");
      Serial.println(analogValue1);

      Vout_1 = ( 5.0 / 4095 ) * analogValue1; //แปลงค่าจากดิจิตอลเป็นอนาลอก
	  //Vout_1 = ( 5.0 / 1023 ) * analogValue1; 
      Serial.print("Vout_1(V) = ");
      Serial.println(Vout_1);

      Vout_sccm_FS_1 = ( FS1 / 5 ) * Vout_1; //กำหนด FS1 = 100 เปลี่ยนหน่วยFull ScaleจากVเป็น sccm
      Serial.print("Vout_sccm_FS_1 = ");
      Serial.println(Vout_sccm_FS_1);

      Flowout1 = ( SPN1 / FSN1  ) * 5  ; // กำหนดให้ FS1 = 100 แปลงหน่วยจากsccmเป็น v
      Serial.print("Flowrate_Vout1(V) = ");
      Serial.println( Flowout1, 3);
      Serial.println("_______________________________ END CHANNEL 1 _______________________________");
      setText("t4", "START1");
      Serial.println("End ask.");

      // ----------------------------------------------------------------------
      // Part Show Value 1
      // ----------------------------------------------------------------------
      analogValue1 = analogRead(A2);
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
      setText("t0", sbuff1);
	  
	  ADC1 = true ;
    }
  }
}
void checkSTOP1(boolean _flag)
{
  if (_flag)
  {
	  Serial.print("Stop enter ");
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
    setText("t0", sbuff1);
	
	
	
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
    len_buff2 = getText("t31", buffer2, sizeof(buffer2));
    len_buff3 = getText("t32", buffer3, sizeof(buffer3));
    callPage("12");
    memset(number2, 0, sizeof(number2));
    memset(number3, 0, sizeof(number3));
    len_num2 = getText("t121", number2, sizeof(number2));
    len_num3 = getText("t122", number3, sizeof(number3));

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
      GM2 = atof(buffer2);
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
      GF2 = atof(buffer3);
      Serial.print("GF2 = ");
      Serial.println(GF2, 3);
    }

    FS2 = atof(number2);
    Serial.print("FS2 = ");
    Serial.println(FS2, 4);

    SP2 = atof(number3);
    Serial.print("SP2 = ");
    Serial.println(SP2, 4);

    if (SP2 > FS2)
    {
      callPage("28");

      C = 0;
      voltage2(C);	 //Set DAC voltage
      Serial.print("C = ");
      Serial.println(C);

      // ----------------------------------------------------------------------
      // Part Show Value 2
      // ----------------------------------------------------------------------
      V_ch2 = ( 5.0 / 1023 ) * analogValue2;
      Serial.print("Vout(V_ch2) = ");
      Serial.println(V_ch2);

      VtoSccm_2 = ( SP2 / 5.0 ) * V_ch2;
      Serial.print("VtoSccm_2 = ");
      Serial.println(VtoSccm_2);
      delay(100);

      MassflowtoNextion2 = 0;
      dtostrf(MassflowtoNextion2, 4, 2, sbuff2);
      Serial.print("sbuff2 = ");
      Serial.println(sbuff2);
      setText("t1", sbuff2);
    }
    else
    {
      callPage("22");

      // ----------------------------------------------------------------------
      // Part Calculate Channel 2
      // ----------------------------------------------------------------------

      FSN2 = ( GF2 / GM2 ) * FS2  ; //คิดFull Scale ค่าใหม่
      Serial.print("FSN2(sccm) = ");
      Serial.println(FSN2);

      SPN2 = ( FSN2 / FS2 ) * SP2 ;
      if (SPN2 > FSN2)
      {
        SPN2 = FSN2;
      }
      Serial.print("SPN2 = ");
      Serial.println(SPN2);

      //C = map( SPN2, 0, FSN2, 0, 4095); //ฟังชั่นเที่ยบบรรหยัดไตรยางmassflow  กำหนด FS2 = 100 แปลง 0-100 ให้อยู่ในช่วง 0-4095 byte
	  C = ( 4095 * SPN2 ) / FSN2 ;
      voltage2(C); //Set DAC voltage
      Serial.print("C = ");
      Serial.println(C, BIN);
      Serial.println(C);

      //D = map( C, 0, 4095, 0, FSN2);  //กำหนด FS2 = 100 //แปลง 0-4095 ให้อยู่ในช่วง 0-100 sccm
	  D = ( FSN2 * C ) / 4095 ;
      Serial.print("D(sccm) = ");
      Serial.println(D);

      analogValue2 = analogRead(A3);  //  อ่านค่า input จากขาanalog A1
      Serial.print("analogValue2 = ");
      Serial.println(analogValue2);

      Vout_2 = ( 5.0 / 4095 ) * analogValue2; //แปลงค่าจากดิจิตอลเป็นอนาลอก
      Serial.print("Vout_2(V) = ");
      Serial.println(Vout_2);

      Vout_sccm_FS_2 = ( FS2 / 5 ) * Vout_2; //กำหนด FS2 = 100 เปลี่ยนหน่วยFull Scale จาก V เป็น sccm
      Serial.print("Vout_sccm_FS_2 = ");
      Serial.println(Vout_sccm_FS_2);

      Flowout2 = ( SPN2 / FSN2 ) * 5 ; // กำหนดให้ FS2 = 100 แปลงหน่วยจากsccmเป็น v
      Serial.print("Flowrate_Vout2(V) = ");
      Serial.println( Flowout2, 3);
      Serial.println("_______________________________ END CHANNEL 2 _______________________________");

      Serial.println("End ask.");
      setText("t5", "START2");

      // ----------------------------------------------------------------------
      // Part Show Value 2
      // ----------------------------------------------------------------------
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
    }
  }
}
void checkSTOP2(boolean _flag)
{
  if (_flag)
  {
    C = 0;
    voltage2(C);	 //Set DAC voltage
    Serial.print("C = ");
    Serial.println(C);
    setText("t5", "STOP2");

    MassflowtoNextion2 = 0;
    dtostrf(MassflowtoNextion2, 4, 2, sbuff2);
    Serial.print("sbuff2 = ");
    Serial.println(sbuff2);
    setText("t1", sbuff2);
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
    len_buff4 = getText("t41", buffer4, sizeof(buffer4));
    len_buff5 = getText("t42", buffer5, sizeof(buffer5));
    callPage("13");
    memset(number4, 0, sizeof(number4));
    memset(number5, 0, sizeof(number5));
    len_num4 = getText("t131", number4, sizeof(number4));
    len_num5 = getText("t132", number5, sizeof(number5));

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
      GM3 = atof(buffer4);
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
      GF3 = atof(buffer5);
      Serial.print("GF3 = ");
      Serial.println(GF3, 3);
    }

    FS3 = atof(number4);
    Serial.print("FS3 = ");
    Serial.println(FS3);

    SP3 = atof(number5);
    Serial.print("SP3 = ");
    Serial.println(SP3);

    if (SP3 > FS3)
    {
      callPage("29");
      E = 0;
      voltage3(E); //Set DAC voltage
      Serial.print("E = ");
      Serial.println(E);

      // ----------------------------------------------------------------------
      // Part Show Value 3
      // ----------------------------------------------------------------------
      V_ch3 = ( 5.0 / 1023 ) * analogValue3;
      Serial.print("Vout(V_ch3) = ");
      Serial.println(V_ch3);

      VtoSccm_3 = ( SP3 / 5.0 ) * V_ch3;
      Serial.print("VtoSccm_3 = ");
      Serial.println(VtoSccm_3);
      delay(100);

      MassflowtoNextion3 = 0;
      dtostrf(MassflowtoNextion3, 4, 2, sbuff3);
      Serial.print("sbuff3 = ");
      Serial.println(sbuff3);
      setText("t2", sbuff3);
    }
    else
    {
      callPage("22");
      // ----------------------------------------------------------------------
      // Part Calculate Channel 3
      // ----------------------------------------------------------------------

      FSN3 = ( GF3 / GM3 ) * FS3  ; //คิดFull Scale ค่าใหม่
      Serial.print("FSN3(sccm) = ");
      Serial.println(FSN3);

      SPN3 = ( FSN3 / FS3 ) * SP3 ;
      if (SPN3 > FSN3)
      {
        SPN3 = FSN3;
      }
      Serial.print("SPN3 = ");
      Serial.println(SPN3);

      //E = map( SPN3, 0, FSN3, 0, 4095); //ฟังชั่นเที่ยบบรรหยัดไตรยางmassflow  กำหนด FS1 = 100 แปลง 0-100 ให้อยู่ในช่วง 0-4095 byte
	  E = ( 4095 * SPN3 ) / FSN3 ;
      voltage3(E);//Set DAC voltage
      Serial.print("E = ");
      Serial.println(E, BIN);
      Serial.println(E);

      //F = map( E, 0, 4095, 0, FSN3); //กำหนด FS1 = 100 //แปลง 0-4095 ให้อยู่ในช่วง 0-100 sccm
	  F = ( FSN3 * E ) / 4095 ;
      Serial.print("F(sccm) = ");
      Serial.println(F);

      analogValue3 = analogRead(A4);  //  อ่านค่า input จากขาanalog A4 DAC ขา14
      Serial.print("analogValue3 = ");
      Serial.println(analogValue3);

      Vout_3 = ( 5.0 / 4095 ) * analogValue3; //แปลงค่าจากดิจิตอลเป็นอนาลอก
      Serial.print("Vout_3(V) = ");
      Serial.println(Vout_3);

      Vout_sccm_FS_3 = ( FS3 / 5 ) * Vout_3; //กำหนด FS1 = 100 เปลี่ยนหน่วยFull ScaleจากVเป็น sccm
      Serial.print("Vout_sccm_FS_3 = ");
      Serial.println(Vout_sccm_FS_3);

      Flowout3 = ( SPN3 / FSN3 ) * 5 ; //  แปลงหน่วยจากsccmเป็น v
      Serial.print("Flowrate_Vout3(V) = ");
      Serial.println( Flowout3, 3);
      Serial.println("_______________________________ END CHANNEL 3 _______________________________");
      Serial.println("End ask.");
      setText("t6", "START3");

      // ----------------------------------------------------------------------
      // Part Show Value 3
      // ----------------------------------------------------------------------
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
    }
  }
}
void checkSTOP3(boolean _flag)
{
  if (_flag)
  {
    E = 0;
    voltage3(E); //Set DAC voltage
    Serial.print("E = ");
    Serial.println(E);
    setText("t6", "STOP3");

    MassflowtoNextion3 = 0;
    dtostrf(MassflowtoNextion3, 4, 2, sbuff3);
    Serial.print("sbuff3 = ");
    Serial.println(sbuff3);
    setText("t2", sbuff3);
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
    len_buff6 = getText("t51", buffer6, sizeof(buffer6));
    len_buff7 = getText("t52", buffer7, sizeof(buffer7));
    callPage("14");
    memset(number6, 0, sizeof(number6));
    memset(number7, 0, sizeof(number7));
    len_num6 = getText("t141", number6, sizeof(number6));
    len_num7 = getText("t142", number7, sizeof(number7));

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
      GM4 = atof(buffer6);
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
      GF4 = atof(buffer7);
      Serial.print("GF4 = ");
      Serial.println(GF4, 3);
    }

    FS4 = atof(number6);
    Serial.print("FS4 = ");
    Serial.println(FS4, 4);

    SP4 = atof(number7);
    Serial.print("SP4 = ");
    Serial.println(SP4, 4);

    if (SP4 > FS4)
    {
      callPage("30");

      G = 0;
      voltage4(G); //Set DAC voltage
      Serial.print("G = ");
      Serial.println(G);

      // ----------------------------------------------------------------------
      // Part Show Value 4
      // ----------------------------------------------------------------------
      V_ch4 = ( 5.0 / 1023 ) * analogValue4;
      Serial.print("Vout(V_ch4) = ");
      Serial.println(V_ch4);

      VtoSccm_4 = ( SP4 / 5.0 ) * V_ch4;
      Serial.print("VtoSccm_4 = ");
      Serial.println(VtoSccm_4);
      delay(100);

      MassflowtoNextion4 = 0;
      dtostrf(MassflowtoNextion4, 4, 2, sbuff4);
      Serial.print("sbuff4 = ");
      Serial.println(sbuff4);
      setText("t3", sbuff4);
    }
    else
    {
      callPage("22");

      // ----------------------------------------------------------------------
      // Part Calculate Channel 4
      // ----------------------------------------------------------------------
      FSN4 = ( GF4 / GM4 ) * FS4  ; //คิดFull Scale ค่าใหม่
      Serial.print("FSN4(sccm) = ");
      Serial.println(FSN4);

      SPN4 = ( FSN4 / FS4 ) * SP4 ;
      if (SPN4 > FSN4)
      {
        SPN4 = FSN4;
      }
      Serial.print("SPN4 = ");
      Serial.println(SPN4);
      Serial.println(SPN4, BIN);

      //G = map( SPN4, 0, FSN4, 0, 4095); //ฟังชั่นเที่ยบบรรหยัดไตรยางmassflow  กำหนด FS2 = 100 แปลง 0-100 ให้อยู่ในช่วง 0-4095 byte
	  G = ( 4095 * SPN4 ) / FSN4 ;
      voltage4(G); //Set DAC voltage
      Serial.print("G = ");
      Serial.println(G, BIN);
      Serial.println(G);

      //F = map( G, 0, 4095, 0, FSN4);  //กำหนด FS2 = 100 //แปลง 0-4095 ให้อยู่ในช่วง 0-100 sccm
	  F = ( FSN4 * G ) / 4095 ;
      Serial.print("F(sccm) = ");
      Serial.println(F);

      analogValue4 = analogRead(A5);  //  อ่านค่า input จากขาanalog A5 DAC ขา10
      Serial.print("analogValue4 = ");
      Serial.println(analogValue4);

      Vout_4 = ( 5.0 / 4095 ) * analogValue4; //แปลงค่าจากดิจิตอลเป็นอนาลอก
      Serial.print("Vout_4(V) = ");
      Serial.println(Vout_4);

      Vout_sccm_FS_4 = ( FS4 / 5 ) * Vout_4; //กำหนด FS2 = 100 เปลี่ยนหน่วยFull Scale จาก V เป็น sccm
      Serial.print("Vout_sccm_FS_4 = ");
      Serial.println(Vout_sccm_FS_4);

      Flowout4 = ( SPN4 / FSN4 ) * 5 ; // กำหนดให้ FS2 = 100 แปลงหน่วยจากsccmเป็น v
      Serial.print("Flowrate_Vout4(V) = ");
      Serial.println( Flowout4, 3);
      Serial.println("_______________________________ END CHANNEL 4 _______________________________");
      Serial.println("End ask.");
      setText("t7", "START4");

      // ----------------------------------------------------------------------
      // Part Show Value 4
      // ----------------------------------------------------------------------
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
    }
  }
}
void checkSTOP4(boolean _flag)
{
  if (_flag)
  {
    G = 0;
    voltage4(G); //Set DAC voltage
    Serial.print("G = ");
    Serial.println(G);
    setText("t7", "STOP4");

    MassflowtoNextion4 = 0;
    dtostrf(MassflowtoNextion4, 4, 2, sbuff4);
    Serial.print("sbuff4 = ");
    Serial.println(sbuff4);
    setText("t3", sbuff4);
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
		ADC1 = false;
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
	  nextionStxCome = false;
    nextionEtxCome = false;
	
	for(iii=0;iii<6;iii++)
		dataBuff[iii] = 0x00;

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
    taskADC1_CNT++;
    if ((TIME_ADC1 / INTERVAL) <= taskADC1_CNT) //1000ms/10ms = 100 counts ==> 1000 ms
    {
      taskADC1_CNT = 0; // Reset counter <--
	  analogValue1 = analogRead(A2);

	  analogValue1 = analogRead(A2);
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
      setText("t0", sbuff1);

	 // Read ADC 1
	 //	ADC1 convert to sccm
	 // SetText display

    }
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
//void taskIncBlinkPeriod(boolean _flag)
//{
//if (_flag)
//{
//MY_TIME_BLINK = MY_TIME_BLINK + 50; //อัพเดตหน่วยความจำ
//if (2000 < MY_TIME_BLINK) MY_TIME_BLINK = 2000; //ถ้าหน่วยความจำมากกว่า 2000
// Serial.print("Increase MY_TIME_BLINK to "); //ให้ปริ๊นข้อความใน""
// Serial.print(MY_TIME_BLINK, DEC);  //ให้ไฟกระพริบ
// Serial.println();
//  }
//}

// ----------------------------------------------------------------------
// Task ลดคาบเวลาในการ Blink
// ----------------------------------------------------------------------
//void taskDecBlinkPeriod(boolean _flag)
//{
//if (_flag)
//{
//  MY_TIME_BLINK = MY_TIME_BLINK - 50; //อัพเดตหน่วยความจำ
//  if (MY_TIME_BLINK < 50) MY_TIME_BLINK = 50; //ถ้าหน่วยความจำน้อยกว่า 50
//   Serial.print("Decrease MY_TIME_BLINK to ");  //ให้ปริ๊นข้อความใน""
//  Serial.print(MY_TIME_BLINK, DEC); //ให้ไฟกระพริบ
//  Serial.println();
//  }
//}
