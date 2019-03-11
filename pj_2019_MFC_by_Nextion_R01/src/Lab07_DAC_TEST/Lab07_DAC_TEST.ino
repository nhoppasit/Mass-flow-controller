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
float FSN1; //Full Scale New 1
float SPN1; //Set Point New 1
float Flowrate1, Flowout1;
float FS1; //Full Scale 1
float SP1; //Set Point 1
float GT1; // Type of gas 1
float GM1; // Gas of massflow 1
int A;
int B;
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
float GT2; // Type of gas 2
float GM2; // Gas of massflow 2
int C;
int D;
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
float GT3; // Type of gas 3
float GM3; // Gas of massflow 3
int E;
int F;
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
float GT4; // Type of gas 4
float GM4; // Gas of massflow 4
int G;
int H;
int analogValue4;

void setup(void)
{
  Serial.begin(9600);
  SPI.begin();
}

void voltage1(unsigned int A)
{
  DAC_A.Set(A, 0);
}
void voltage2(unsigned int C)
{
  DAC_A.Set(A, C);
}
void voltage3(unsigned int E)
{
  DAC_B.Set(E, 0);
}
void voltage4(unsigned int G)
{
  DAC_B.Set(E, G);
}

void loop(void)
{
  if (Serial.available() > 0) //เช็คว่ามีการพิมพ์ค่าที่มากกว่า 0 เข้ามามั้ย
  {
    // ----------------------------------------------------------------------
    // Set Value Channel 1
    // ----------------------------------------------------------------------

    String inChar = Serial.readStringUntil(','); // fullscale1 อ่านตัวอักษรจากสตรีมไปเป็นสตริง แล้วเมื่อพบ "," จะสิ้นสุดฟังก์ชั่น
    String inChar0 = Serial.readStringUntil(','); // Set Point1
    String inChar1 = Serial.readStringUntil(','); // type of Gas1
    String inChar2 = Serial.readStringUntil(',');  // Gas of massflow1

    FS1  = inChar.toFloat(); // fullscale1   แปลงค่าจากตัวแปรประเภทตัวอักขระเป็นตัวแปรประเภทตัวเลขทศนิยม
    SP1  = inChar0.toFloat();//setpoint1  แปลงค่าจากตัวแปรประเภทตัวอักขระเป็นตัวแปรประเภทตัวเลขทศนิยม
    GT1  = inChar1.toFloat();//type of gas1  แปลงค่าจากตัวแปรประเภทตัวอักขระเป็นตัวแปรประเภทตัวเลขทศนิยม
    GM1  = inChar2.toFloat();//gas of massflow 1 แปลงค่าจากตัวแปรประเภทตัวอักขระเป็นตัวแปรประเภทตัวเลขทศนิยม

    // ----------------------------------------------------------------------
    // Set Value Channel 2
    // ----------------------------------------------------------------------

    String inChar3 = Serial.readStringUntil(','); // fullscale2 อ่านตัวอักษรจากสตรีมไปเป็นสตริง แล้วเมื่อพบ "," จะสิ้นสุดฟังก์ชั่น
    String inChar4 = Serial.readStringUntil(','); // Set Point2
    String inChar5 = Serial.readStringUntil(','); // type of Gas2
    String inChar6 = Serial.readStringUntil(',');  // Gas of massflow2

    FS2  = inChar3.toFloat(); // fullscale2   แปลงค่าจากตัวแปรประเภทตัวอักขระเป็นตัวแปรประเภทตัวเลขทศนิยม
    SP2  = inChar4.toFloat();//setpoint2  แปลงค่าจากตัวแปรประเภทตัวอักขระเป็นตัวแปรประเภทตัวเลขทศนิยม
    GT2  = inChar5.toFloat();//type of gas2  แปลงค่าจากตัวแปรประเภทตัวอักขระเป็นตัวแปรประเภทตัวเลขทศนิยม
    GM2  = inChar6.toFloat();//gas of massflow2 แปลงค่าจากตัวแปรประเภทตัวอักขระเป็นตัวแปรประเภทตัวเลขทศนิยม

        // ----------------------------------------------------------------------
    // Set Value Channel 3
    // ----------------------------------------------------------------------

    String inChar7 = Serial.readStringUntil(','); // fullscale3 อ่านตัวอักษรจากสตรีมไปเป็นสตริง แล้วเมื่อพบ "," จะสิ้นสุดฟังก์ชั่น
    String inChar8 = Serial.readStringUntil(','); // Set Point3
    String inChar9 = Serial.readStringUntil(','); // type of Gas3
    String inChar10 = Serial.readStringUntil(',');  // Gas of massflow3

    FS3  = inChar7.toFloat(); // fullscale3   แปลงค่าจากตัวแปรประเภทตัวอักขระเป็นตัวแปรประเภทตัวเลขทศนิยม
    SP3  = inChar8.toFloat();//setpoint3  แปลงค่าจากตัวแปรประเภทตัวอักขระเป็นตัวแปรประเภทตัวเลขทศนิยม
    GT3  = inChar9.toFloat();//type of gas3  แปลงค่าจากตัวแปรประเภทตัวอักขระเป็นตัวแปรประเภทตัวเลขทศนิยม
    GM3  = inChar10.toFloat();//gas of massflow 3 แปลงค่าจากตัวแปรประเภทตัวอักขระเป็นตัวแปรประเภทตัวเลขทศนิยม

    // ----------------------------------------------------------------------
    // Set Value Channel 4
    // ----------------------------------------------------------------------

    String inChar11 = Serial.readStringUntil(','); // fullscale4 อ่านตัวอักษรจากสตรีมไปเป็นสตริง แล้วเมื่อพบ "," จะสิ้นสุดฟังก์ชั่น
    String inChar12 = Serial.readStringUntil(','); // Set Point4
    String inChar13 = Serial.readStringUntil(','); // type of Gas4
    String inChar14 = Serial.readStringUntil(',');  // Gas of massflow4

    FS4  = inChar11.toFloat(); // fullscale4   แปลงค่าจากตัวแปรประเภทตัวอักขระเป็นตัวแปรประเภทตัวเลขทศนิยม
    SP4  = inChar12.toFloat();//setpoint4  แปลงค่าจากตัวแปรประเภทตัวอักขระเป็นตัวแปรประเภทตัวเลขทศนิยม
    GT4  = inChar13.toFloat();//type of gas4  แปลงค่าจากตัวแปรประเภทตัวอักขระเป็นตัวแปรประเภทตัวเลขทศนิยม
    GM4  = inChar14.toFloat();//gas of massflow4 แปลงค่าจากตัวแปรประเภทตัวอักขระเป็นตัวแปรประเภทตัวเลขทศนิยม

    // ----------------------------------------------------------------------
    // Part Calculate Channel 1
    // ----------------------------------------------------------------------

    SPN1 = SP1 * ( GM1 / GT1 );
    Serial.print("SPN1 = ");
    Serial.println(SPN1);
    Serial.println(SPN1, BIN);

    A = map( SPN1, 0, FS1, 0, 4095); //ฟังชั่นเที่ยบบรรหยัดไตรยางmassflow  กำหนด FS1 = 100 แปลง 0-100 ให้อยู่ในช่วง 0-4095 byte
    voltage1(A); //Set DAC voltage
    Serial.print("A = ");
    Serial.println(A, BIN);
    Serial.println(A);

    B = map( A, 0, 4095, 0, FS1);  //กำหนด FS1 = 100 //แปลง 0-4095 ให้อยู่ในช่วง 0-100 sccm
    Serial.print("B(sccm) = ");
    Serial.println(B);

    analogValue1 = analogRead(A0);  //  อ่านค่า input จากขาanalog A0
    Serial.print("analogValue1 = ");
    Serial.println(analogValue1);

    Vout_1 = ( 5.0 / 4095 ) * analogValue1; //แปลงค่าจากดิจิตอลเป็นอนาลอก
    Serial.print("Vout_1(V) = ");
    Serial.println(Vout_1);

    Vout_sccm_FS_1 = ( FS1 / 5 ) * Vout_1; //กำหนด FS1 = 100 เปลี่ยนหน่วยFull ScaleจากVเป็น sccm
    Serial.print("Vout_sccm_FS_1 = ");
    Serial.println(Vout_sccm_FS_1);

    FSN1 = ( GT1 / GM1 ) * FS1  ; //คิดFull Scale ค่าใหม่
    Serial.print("FSN1(sccm) = ");
    Serial.println(FSN1);
    
    Flowout1 = ( SP1 / FSN1 ) * 5 ; // กำหนดให้ FS1 = 100 แปลงหน่วยจากsccmเป็น v
    Serial.print("Flowrate_Vout1(V) = ");
    Serial.println( Flowout1,3);
    Serial.println("_______________________________ END CHANNEL 1 _______________________________");

    // ----------------------------------------------------------------------
    // Part Calculate Channel 2
    // ----------------------------------------------------------------------

    SPN2 = SP2 * ( GM2 / GT2 );
    Serial.print("SPN2 = ");
    Serial.println(SPN2);
    Serial.println(SPN2, BIN);

    C = map( SPN2, 0, FS2, 0, 4095); //ฟังชั่นเที่ยบบรรหยัดไตรยางmassflow  กำหนด FS2 = 100 แปลง 0-100 ให้อยู่ในช่วง 0-4095 byte
    voltage2(C); //Set DAC voltage
    Serial.print("C = ");
    Serial.println(C, BIN);
    Serial.println(C);

    D = map( C, 0, 4095, 0, FS2);  //กำหนด FS2 = 100 //แปลง 0-4095 ให้อยู่ในช่วง 0-100 sccm
    Serial.print("D(sccm) = ");
    Serial.println(D);

    analogValue2 = analogRead(A1);  //  อ่านค่า input จากขาanalog A1
    Serial.print("analogValue2 = ");
    Serial.println(analogValue2);

    Vout_2 = ( 5.0 / 4095 ) * analogValue2; //แปลงค่าจากดิจิตอลเป็นอนาลอก
    Serial.print("Vout_2(V) = ");
    Serial.println(Vout_2);

    Vout_sccm_FS_2 = ( FS2 / 5 ) * Vout_2; //กำหนด FS2 = 100 เปลี่ยนหน่วยFull Scale จาก V เป็น sccm
    Serial.print("Vout_sccm_FS_2 = ");
    Serial.println(Vout_sccm_FS_2);

    FSN2 = ( GT2 / GM2 ) * FS2  ; //คิดFull Scale ค่าใหม่
    Serial.print("FSN2(sccm) = ");
    Serial.println(FSN2);

    Flowout2 = ( SP2 / FSN2 ) * 5 ; // กำหนดให้ FS2 = 100 แปลงหน่วยจากsccmเป็น v
    Serial.print("Flowrate_Vout2(V) = ");
    Serial.println( Flowout2,3);
    Serial.println("_______________________________ END CHANNEL 2 _______________________________");
// ----------------------------------------------------------------------
    // Part Calculate Channel 3
    // ----------------------------------------------------------------------

    SPN3 = SP3 * ( GM3 / GT3 );
    Serial.print("SPN3 = ");
    Serial.println(SPN3);
    Serial.println(SPN3, BIN);

    E = map( SPN3, 0, FS3, 0, 4095); //ฟังชั่นเที่ยบบรรหยัดไตรยางmassflow  กำหนด FS1 = 100 แปลง 0-100 ให้อยู่ในช่วง 0-4095 byte
    voltage3(E); //Set DAC voltage
    Serial.print("E = ");
    Serial.println(E, BIN);
    Serial.println(E);

    F = map( E, 0, 4095, 0, FS3);  //กำหนด FS1 = 100 //แปลง 0-4095 ให้อยู่ในช่วง 0-100 sccm
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

    FSN3 = ( GT3 / GM3 ) * FS3  ; //คิดFull Scale ค่าใหม่
    Serial.print("FSN3(sccm) = ");
    Serial.println(FSN3);

    Flowout3 = ( SP3 / FSN3 ) * 5 ; // กำหนดให้ FS1 = 100 แปลงหน่วยจากsccmเป็น v
    Serial.print("Flowrate_Vout3(V) = ");
    Serial.println( Flowout3, 3);
    Serial.println("_______________________________ END CHANNEL 3 _______________________________");

    // ----------------------------------------------------------------------
    // Part Calculate Channel 4
    // ----------------------------------------------------------------------

    SPN4 = SP4 * ( GM4 / GT4 );
    Serial.print("SPN4 = ");
    Serial.println(SPN4);
    Serial.println(SPN4, BIN);

    G = map( SPN4, 0, FS4, 0, 4095); //ฟังชั่นเที่ยบบรรหยัดไตรยางmassflow  กำหนด FS2 = 100 แปลง 0-100 ให้อยู่ในช่วง 0-4095 byte
    voltage4(G); //Set DAC voltage
    Serial.print("G = ");
    Serial.println(G, BIN);
    Serial.println(G);

    F = map( G, 0, 4095, 0, FS4);  //กำหนด FS2 = 100 //แปลง 0-4095 ให้อยู่ในช่วง 0-100 sccm
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

    FSN4 = ( GT4 / GM4 ) * FS4  ; //คิดFull Scale ค่าใหม่
    Serial.print("FSN4(sccm) = ");
    Serial.println(FSN4);

    Flowout4 = ( SP4 / FSN4 ) * 5 ; // กำหนดให้ FS2 = 100 แปลงหน่วยจากsccmเป็น v
    Serial.print("Flowrate_Vout4(V) = ");
    Serial.println( Flowout4, 3);
    Serial.println("_______________________________ END CHANNEL 4 _______________________________");

      }
}
