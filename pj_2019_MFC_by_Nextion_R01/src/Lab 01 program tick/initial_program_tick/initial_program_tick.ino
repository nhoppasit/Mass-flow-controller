// -----------------------------------
// CPU tick
// -----------------------------------
#define INTERVAL         10 // ms
unsigned long previousMillis;
boolean       tick_state;

// -----------------------------------
// TASK BLINK
// -----------------------------------
#define TIME_BLINK     1000 // ms
boolean Blink = false; // ใช้จำสถานะไฟกระพริบ
int taskBlink_CNT;

void setup() 
{
  // put your setup code here, to run once:

}

void loop() 
{
	tick();
	
	taskBlink(tick_state);
}

// ================================= PROCEDURES =========================================
// -----------------------------------
// Program Tick
// -----------------------------------
void tick()
{
  tick_state = false;
  if(millis() - previousMillis > INTERVAL)
  {       
    previousMillis = millis();    
    tick_state = true;
  }
}

// -----------------------------------
// TK01 = Blink
// -----------------------------------
void taskBlink(boolean _flag)
{
  if(_flag)
  {
    taskBlink_CNT++;
    if(taskBlink_CNT > TIME_BLINK/INTERVAL)
    {
      taskBlink_CNT = 0; // Reset counter <-- 
      if(!Blink)
      {      
        //LED ON
        Blink=true;
      }
      else
      {      
        //LED OFF
        Blink=false;
      }
    }
  }  
}