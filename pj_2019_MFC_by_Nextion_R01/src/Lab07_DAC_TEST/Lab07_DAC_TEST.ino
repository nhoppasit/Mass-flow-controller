#include <Adafruit_MCP4725.h> 
Adafruit_MCP4725 dac;

// ----------------------------------------------------------------------
// Channel 1
// ----------------------------------------------------------------------
float Vout_1;
float Vout_sccm_FS_1;
float Vout_sccm_SP_1;
float FSN1; //Full Scale New 1
float SPN1; //Set Point New 1
float Flowrate1,Flowout1;
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
float Flowrate2,Flowout2;
float FS2; //Full Scale 2
float SP2; //Set Point 2
float GT2; // Type of gas 2
float GM2; // Gas of massflow 2
int C;
int D;
int analogValue2;   

void setup(void) 
{
  Serial.begin(9600);
  dac.begin(0x60);  //Start DAC. DAC address 0x60 
  pinMode(A0, INPUT);

  dac.begin(0x61); //Start DAC. DAC address 0x61
  pinMode(A1, INPUT);
}

void voltage1(unsigned int A)
{
  dac.begin(0x60);  //Start DAC. DAC address 0x60 
  dac.setVoltage(A, false); // Set DAC voltage. false 
}

void voltage2(unsigned int C)
{
  dac.begin(0x61);  //Start DAC. DAC address 0x61
  dac.setVoltage(C, false); // Set DAC voltage. false 
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
// Part Calculate Channel 1
// ----------------------------------------------------------------------

    SPN1 = SP1 * ( GM1 / GT1 );
    Serial.print("SPN1 = ");
    Serial.println(SPN1);    
    Serial.println(SPN1,BIN);
    
    A = map( SPN1, 0, FS1, 0, 4095); //ฟังชั่นเที่ยบบรรหยัดไตรยางmassflow  กำหนด FS1 = 100 แปลง 0-100 ให้อยู่ในช่วง 0-4095 byte
    voltage1(A); //Set DAC voltage
    Serial.print("A = ");
    Serial.println(A,BIN);
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
      
    /* Vout_sccm_SP_1 = ( SP1 / 5 ) * Vout_1;  //เปลี่ยนหน่วยSet Point จากVเป็น sccm
      Serial.print("Vout_sccm_SP_1 = ");
      Serial.println(Vout_sccm_SP_1); */
      
      FSN1 = ( GT1 / GM1 )* FS1  ;  //คิดFull Scale ค่าใหม่
      Serial.print("FSN1(sccm) = ");
      Serial.println(FSN1);
            
     /* SPN1 = ( GT1 / GM1 )* Vout_sccm_SP_1  ;  //คิดSet point ค่าใหม่
      Serial.print("SPN1(sccm) = ");
      Serial.println(SPN1); */

     /* Flowrate1 = ( SPN1 / FS1 ) ;  //คิดค่าอัตราการไหล
      Serial.print("Flowrate1(sccm) = ");
      Serial.println(Flowrate1); */

      /* Flowrate1 = ( Vout_sccm_FS_1 / SP1 ) * FSN1 ;  //คิดค่าอัตราการไหล
      Serial.print("Flowrate1(sccm) = ");
      Serial.println(Flowrate1); */
      
      Flowout1 = ( SP1 / FSN1 ) * 5 ; // กำหนดให้ FS1 = 100 แปลงหน่วยจากsccmเป็น v
      Serial.print("Flowrate_Vout1(V) = ");
      Serial.println( Flowout1); 
      Serial.println("_______________________________ END CHANNEL 1 _______________________________");
      
// ----------------------------------------------------------------------
// Part Calculate Channel 2
// ----------------------------------------------------------------------

    SPN2 = SP2 * ( GM2 / GT2 );
    Serial.print("SPN2 = ");
    Serial.println(SPN2);    
    Serial.println(SPN2,BIN);
    
    C = map( SPN2, 0, FS2, 0, 4095); //ฟังชั่นเที่ยบบรรหยัดไตรยางmassflow  กำหนด FS2 = 100 แปลง 0-100 ให้อยู่ในช่วง 0-4095 byte
    voltage2(C); //Set DAC voltage
    Serial.print("C = ");
    Serial.println(C,BIN);
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
      
  /*  Vout_sccm_SP_2 = ( SP2 / 5 ) * Vout_2;  //เปลี่ยนหน่วยSet Point จาก V เป็น sccm
      Serial.print("Vout_sccm_SP_2 = ");
      Serial.println(Vout_sccm_SP_2);*/
      
    FSN2 = ( GT2 / GM2 )* FS2  ;  //คิดFull Scale ค่าใหม่
      Serial.print("FSN2(sccm) = ");
      Serial.println(FSN2);

   /* SPN2 = ( GT2 / GM2 )* Vout_sccm_SP_2  ;  //คิดSet point ค่าใหม่
      Serial.print("SPN2(sccm) = ");
      Serial.println(SPN2);

    Flowrate2 = ( SPN2 / FSN2 )*100 ;  //คิดค่าอัตราการไหล
      Serial.print("Flowrate2(sccm) = ");
      Serial.println(Flowrate2); */

    Flowout2 = ( SP2 / FSN2 ) * 5 ; // กำหนดให้ FS2 = 100 แปลงหน่วยจากsccmเป็น v
      Serial.print("Flowrate_Vout2(V) = ");
      Serial.println( Flowout2); 
      Serial.println("_______________________________ END CHANNEL 2 _______________________________");
   }
}
