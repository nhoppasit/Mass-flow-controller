#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 dac;

float   V;
float Vout_sccm_FS;
float Vout_sccm_SP;
float FSN1;
float SPN1;
float Flowrate,Flowout;
float FS1;
float SP1;
float GT1;
float GM1;
int A;
int B;
int analogValue;


void setup(void) {
  Serial.begin(9600);
  dac.begin(0x60);
  dac.begin(0X61);
  pinMode(A0, INPUT);
 
}

void voltage1(unsigned int volt1)
{
  dac.begin(0x60);
  dac.setVoltage(volt1, false);
}

void loop(void)
{
   if (Serial.available() > 0)
{
    //String inChar = Serial.readStringUntil(',');
    String inChar0 = Serial.readStringUntil(',');
    String inChar1 = Serial.readStringUntil(',');
    String inChar2 = Serial.readStringUntil(',');

    //FS1  = inChar.toFloat(); // fullscale    
    SP1  = inChar0.toFloat();//setpoint
    GT1  = inChar1.toFloat();//type of gas
    GM1  = inChar2.toFloat();//gas of massflow

    A = map( SP1, 0, 100, 0, 4095); //ฟังชั่นเที่ยบบรรหยัดไตรยางmassflowตัวที่1 กำหนด FS = 100
    voltage1(A);
    Serial.print("A = ");
    Serial.println(A,BIN);
    Serial.println(A);
    
    B = map( A, 0, 4095, 0, 100);  //กำหนด FS = 100
    Serial.print("B(sccm) = ");
    Serial.println(B);

      
    analogValue = analogRead(A0);
      Serial.print("analogValue = ");
      Serial.println(analogValue);

    V = ( 5.0 / 4095 ) * analogValue;
      Serial.print("Vout(V) = ");
      Serial.println(V);

    Vout_sccm_FS = ( 100 / 5 ) * V; //กำหนด FS = 100
      Serial.print("Vout_sccm_FS = ");
      Serial.println(Vout_sccm_FS);
      
    Vout_sccm_SP = ( SP1 / 5 ) * V;
      Serial.print("Vout_sccm_SP = ");
      Serial.println(Vout_sccm_SP);
      
    FSN1 = ( GT1 / GM1 )* Vout_sccm_FS  ;
      Serial.print("FSN1(sccm) = ");
      Serial.println(FSN1);

    SPN1 = ( GT1 / GM1 )* Vout_sccm_SP  ;
      Serial.print("SPN1(sccm) = ");
      Serial.println(SPN1);

    Flowrate = ( SPN1 / FSN1 )*100 ; 
      Serial.print("Flowrate(sccm) = ");
      Serial.println(Flowrate);

    Flowout = ( SP1 / 100 ) * 5 ; // กำหนดให้ FS = 100;
      Serial.print("Flowrate_Vout(V) = ");
      Serial.println( Flowout);   

   }
  
}
