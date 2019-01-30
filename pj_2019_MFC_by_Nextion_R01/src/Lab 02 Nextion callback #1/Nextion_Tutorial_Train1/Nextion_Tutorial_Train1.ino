// ############################################################################################################################################
// ############################################################# DECLARATION ##################################################################
// ############################################################################################################################################
#include <Nextion.h>  // Include the nextion library (the official one) https://github.com/itead/ITEADLIB_Arduino_Nextion
                      // Make sure you edit the NexConfig.h file on the library folder to set the correct serial port for the display.
                      // By default it's set to Serial1, which most arduino boards don't have.
                      // Change "#define nexSerial Serial1" to "#define nexSerial Serial" if you are using arduino uno, nano, etc.



int variable1 = 0;  // Create a variable to have a counter going up by one on each cycle
int counter = 0;  // Create a variable to have a counter for the + and - buttons
int CurrentPage = 0;  // Create a variable to store which page is currently loaded


// Declare objects that we are going to read from the display. This includes buttons, sliders, text boxes, etc:
NexButton b1 = NexButton(0, 9, "b1");  // Button added
NexButton b0 = NexButton(0, 1, "b0");  // Button added
NexButton b4 = NexButton(0, 11, "b4");  // Button added
NexDSButton bt0 = NexDSButton(0, 8, "bt0");  // Dual state button added
NexSlider h0 = NexSlider(0, 4, "h0");  // Slider added
NexText t5 = NexText(2, 12, "t5");  // Text box added, so we can read it
NexText t6 = NexText(2, 13, "t6");  // Text box added, so we can read it
NexText t7 = NexText(2, 14, "t7");  // Text box added, so we can read it
NexRadio r0 = NexRadio(2, 4, "r0");  // Radio checkbox added
NexRadio r1 = NexRadio(2, 5, "r1");  // Radio checkbox added
NexRadio r2 = NexRadio(2, 6, "r2");  // Radio checkbox added
NexCheckbox c0 = NexCheckbox(2, 3, "c0");  // Checkbox added
NexButton j0 = NexButton(2, 2, "j0");  // Progress bar as a button added, so if we press the progress bar we can create an action
NexButton b21 = NexButton(2, 10, "b21");  // Button added
NexButton b22 = NexButton(2, 16, "b22");  // Button added
NexButton b23 = NexButton(2, 18, "b23");  // Button added
NexButton b24 = NexButton(2, 19, "b24");  // Button added

// Declare pages:
NexPage page0 = NexPage(0, 0, "page0");  // Page added as a touch event
NexPage page1 = NexPage(1, 0, "page1");  // Page added as a touch event
NexPage page2 = NexPage(2, 0, "page2");  // Page added as a touch event

// End of declaring objects

// ############################################################################################################################################
// ############################################################# MEMORIES ##################################################################
// ############################################################################################################################################
char buffer[100] = {0};  // This is needed only if you are going to receive a text from the display. You can remove it otherwise.
                         // Further on this sketch I do receive text so that's why I created this buffer.

// Declare touch event objects to the touch event list: 
NexTouch *nex_listen_list[] = 
{
  &b1,  // Button added
  &b0,  // Button added
  &b4,  // Button added
  &b21,  // Button added
  &b22,  // Button added
  &b23,  // Button added
  &b24,  // Button added
  &bt0,  // Dual state button added
  &h0,  // Slider added
  &r0,  // Radio checkbox added
  &r1,  // Radio checkbox added
  &r2,  // Radio checkbox added
  &c0,  // Checkbox added
  &j0,  // Progress bar as a button added
  &page0,  // Page added as a touch event
  &page1,  // Page added as a touch event
  &page2,  // Page added as a touch event
  NULL  // String terminated
};  // End of touch event list


// ############################################################################################################################################
// ############################################################# CALL BACK / EVENTS ##################################################################
// ############################################################################################################################################
////////////////////////// Touch events:
void b1PushCallback(void *ptr)  // Press event for button b1
{
  digitalWrite(13, HIGH);  // Turn ON internal LED
}  // End of press event

void b1PopCallback(void *ptr)  // Release event for button b1
{
  digitalWrite(13, LOW);  // Turn OFF internal LED
}  // End of release event

void b0PushCallback(void *ptr)  // Press event for button b0
{
  counter = counter - 1;  // Subtract 1 to the current value of the counter

  Serial.print("n3.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print(counter);  // This is the value you want to send to that object and atribute mentioned before.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
}  // End of press event

void b4PushCallback(void *ptr)  // Press event for button b4
{
  counter = counter + 1;  // Add 1 to the current value of the counter

  Serial.print("n3.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print(counter);  // This is the value you want to send to that object and atribute mentioned before.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
}  // End of press event

void bt0PopCallback(void *ptr)  // Release event for dual state button bt0
{
  uint32_t number5 = 0;  // Create variable to store value we are going to get
  bt0.getValue(&number5);  // Read value of dual state button to know the state (0 or 1)

  if(number5 == 1){  // If dual state button is equal to 1 (meaning is ON)...
    digitalWrite(13, HIGH);  // Turn ON internal LED
  }else{  // Since the dual state button is OFF...
    digitalWrite(13, LOW);  // Turn OFF internal LED
  }
}  // End of release event





void h0PopCallback(void *ptr)  // Release event for slider
{
  uint32_t number2 = 0;  // Create variable to store value of slider
  h0.getValue(&number2);  // Read the value of the slider
  
  // I got a problem where sometimes I received a 0 instead of the correct slider value.
  // To fix this I will put a condition that if I get a 0, I am going to read again the slider to make sure I get the real value.
  // I am going to do this a few times because sometimes it takes a few tries to get the correct value.
  // The problem looks like it have something to do with touch events. Everytime the display sends a touch event,
  // we need to wait that data to finish transmiting before we can get another data from the display (in this case
  // we want the slider position). For this reason it's important to use a high serial baud (ideally 115200)
  // so it doesn't have to wait too long for the touch event to finish sending the data.

  // The "Are you sure is 0?" begins:
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  // The "Are you sure is 0?" ended. At this point, if the slider keep showing as 0, then it really is at 0.

  // Now is going to send the value it received by the slider:
  Serial.print("n4.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print(number2);  // This is the value you want to send to that object and atribute mentioned before.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
}  // End of release event





void r0PushCallback(void *ptr)  // Press event for radio checkbox
{
  Serial.print("n9.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print(1);  // This is the value you want to send to that object and atribute mentioned before.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
}  // End of press event





void r1PushCallback(void *ptr)  // Press event for radio checkbox
{
  Serial.print("n9.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print(2);  // This is the value you want to send to that object and atribute mentioned before.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
}  // End of press event





void r2PushCallback(void *ptr)  // Press event for radio checkbox
{
  Serial.print("n9.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print(3);  // This is the value you want to send to that object and atribute mentioned before.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
}  // End of press event





void c0PushCallback(void *ptr)  // Press event for checkbox
{
  uint32_t number3 = 0;  // Create variable to store the value of the state of the checkbox
  c0.getValue(&number3);  // Read the state of the checkbox
  Serial.print("n1.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print(number3);  // This is the value you want to send to that object and atribute mentioned before.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
}  // End of press event





void j0PushCallback(void *ptr)  // Press event for progress bar
{
  Serial.print("j0.pco=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print(63488);  // Code for the color red
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
}  // End of press event





void b21PushCallback(void *ptr)  // Press event for "Home" button on page 2
{
  Serial.print("page 0");  // Sending this it's going to tell the nextion display to go to page 0.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
}  // End of press event





void b22PushCallback(void *ptr)  // Press event for "Send" button on page 2
{
  memset(buffer, 0, sizeof(buffer));  // Clear the buffer, so we can start using it
  t5.getText(buffer, sizeof(buffer));  // Read the text on the object t5 and store it on the buffer

  // Now is going to send the text we received to object t23:
  Serial.print("t23.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  Serial.print(buffer);  // This is the text you want to send to that object and atribute mentioned before.
  Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
}  // End of press event





void b23PushCallback(void *ptr)  // Press event for "Send" button on page 2
{
  memset(buffer, 0, sizeof(buffer));  // Clear the buffer, so we can start using it
  t6.getText(buffer, sizeof(buffer));  // Read the text on the object t6 and store it on the buffer

  // Now is going to send the text we received to object t23:
  Serial.print("t23.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  Serial.print(buffer);  // This is the text you want to send to that object and atribute mentioned before.
  Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
}  // End of press event





void b24PushCallback(void *ptr)  // Press event for "Send" button on page 2
{
  memset(buffer, 0, sizeof(buffer));  // Clear the buffer, so we can start using it
  t7.getText(buffer, sizeof(buffer));  // Read the text on the object t7 and store it on the buffer

  // Now is going to send the text we received to object t23:
  Serial.print("t23.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  Serial.print(buffer);  // This is the text you want to send to that object and atribute mentioned before.
  Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);
}  // End of press event





// Page change event:
void page0PushCallback(void *ptr)  // If page 0 is loaded on the display, the following is going to execute:
{
  CurrentPage = 0;  // Set variable as 0 so from now on arduino knows page 0 is loaded on the display
}  // End of press event


// Page change event:
void page1PushCallback(void *ptr)  // If page 1 is loaded on the display, the following is going to execute:
{
  CurrentPage = 1;  // Set variable as 1 so from now on arduino knows page 1 is loaded on the display
}  // End of press event


// Page change event:
void page2PushCallback(void *ptr)  // If page 2 is loaded on the display, the following is going to execute:
{
  CurrentPage = 2;  // Set variable as 2 so from now on arduino knows page 2 is loaded on the display
}  // End of press event

////////////////////////// End of touch events

// ############################################################################################################################################
// ############################################################# SETUP ##################################################################
// ############################################################################################################################################
void setup() {  // Put your setup code here, to run once:
  
  Serial.begin(9600);  // Start serial comunication at baud=9600


  // I am going to change the Serial baud to a faster rate.
  // The reason is that the slider have a glitch when we try to read it's value.
  // One way to solve it was to increase the speed of the serial port.
  delay(500);  // This dalay is just in case the nextion display didn't start yet, to be sure it will receive the following command.
  Serial.print("baud=115200");  // Set new baud rate of nextion to 115200, but it's temporal. Next time nextion is power on,
                                // it will retore to default baud of 9600.
                                // To take effect, make sure to reboot the arduino (reseting arduino is not enough).
                                // If you want to change the default baud, send the command as "bauds=115200", instead of "baud=115200".
                                // If you change the default baud, everytime the nextion is power ON is going to have that baud rate, and
                                // would not be necessery to set the baud on the setup anymore.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to nextion.
  Serial.write(0xff);
  Serial.write(0xff);

  Serial.end();  // End the serial comunication of baud=9600

  Serial.begin(115200);  // Start serial comunication at baud=115200

  // Register the event callback functions of each touch event:
  b1.attachPush(b1PushCallback);  // Button press
  b1.attachPop(b1PopCallback);  // Button release
  b0.attachPush(b0PushCallback);  // Button press
  b4.attachPush(b4PushCallback);  // Button press
  b21.attachPush(b21PushCallback);  // Button press
  b22.attachPush(b22PushCallback);  // Button press
  b23.attachPush(b23PushCallback);  // Button press
  b24.attachPush(b24PushCallback);  // Button press
  bt0.attachPop(bt0PopCallback);  // Dual state button bt0 release
  h0.attachPop(h0PopCallback);  // Slider release
  r0.attachPush(r0PushCallback);  // Radio checkbox press
  r1.attachPush(r1PushCallback);  // Radio checkbox press
  r2.attachPush(r2PushCallback);  // Radio checkbox press
  c0.attachPush(c0PushCallback);  // Radio checkbox press
  j0.attachPush(j0PushCallback);  // Progress bar as a button press
  page0.attachPush(page0PushCallback);  // Page press event
  page1.attachPush(page1PushCallback);  // Page press event
  page2.attachPush(page2PushCallback);  // Page press event

  // End of registering the event callback functions

  pinMode(13, OUTPUT);

}  // End of setup

// ############################################################################################################################################
// ############################################################# LOOP ##################################################################
// ############################################################################################################################################
void loop() {  // Put your main code here, to run repeatedly:


  delay(30);  // This is the only delay on this loop.
              // I put this delay because without it, the timer on the display would stop running.
              // The timer I am talking about is the one called tm0 on page 0 (of my example nextion project).
              // Aparently we shouldn't send data to the display too often.



  // I created the following variable to have a dynamic number to send to the display:
  variable1++;  // Add 1 to the variable1
  if(variable1 > 240){  // If the variable is above 240
    variable1 = 0;  // Set variable to 0 to start over
  }

  // Send variable1 value to the object called n0:
  Serial.print("n0.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print(variable1);  // This is the value you want to send to that object and atribute mentioned before.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);

  // Send page number to the object called np:
  Serial.print("np.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.print(CurrentPage);  // This is the value you want to send to that object and atribute mentioned before.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);

  // Sending data to the display to nonexistent objects on the current page creates an error code sent by the display.
  if(CurrentPage == 0){  // If the display is on page 0, do the following:
  
    // Send a text to the object called t1:
    Serial.print("t1.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.print("Hello!");  // This is the text you want to send to that object and atribute mentioned before.
    Serial.print("\"");  // Since we are sending text, and not a number, we need to send double quote before and after the actual text.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }
  if(CurrentPage == 1){  // If the display is on page 1, do the following:
  
    // Send a new value to the waveform. In this case we are sending the variable1 value that goes from 0 to 240:
    Serial.print("add 2,0,");  // This sends data to the waveform. There are 3 numbers you have to put with a comma
                               // between them: [objectID],[Channel],[Value]
                               // In this case 2 is the ID of the waveform; 0 is the channel number; and last value is
                               // going to be send in the next line:
    Serial.print(variable1);  // This is the value we are going to send for the waveform and channel mentioned previously.
                              // Range is from 0 to 255. Going over 255 will show the graphic line going to 0 and continue from there.
                              // Each number it's a pixel. This means you can't do waveforms over 255 pixels high. Over that is unusable.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  }

  if(CurrentPage == 2){  // If the display is on page 2, do the following:
  
    // Send variable1 value to the progress bar called j0:
    // If we send a value greater than 100, we are going to receive an error and this cause lag on the arduino loop, so we are
    // going to constrain the value to avoid going over 100:
    int variable2 = constrain(variable1, 0, 100);  // limits value between 0 and 100 to prevent going over this limits

    Serial.print("j0.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print(variable2);  // This is the value you want to send to that object and atribute mentioned before.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);


    // Send variable1 value to the gauge called z0:
    // Range for the gauge is from 0 to 360. Don't send a greater value or the display is going to send an error code and
    // that creates lag on the arduino loop.
    Serial.print("z0.val=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
    Serial.print(variable1);  // This is the value you want to send to that object and atribute mentioned before.
    Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
    Serial.write(0xff);
    Serial.write(0xff);
  
  }

  // We are going to check the list of touch events we enter previously to
  // know if any touch event just happened, and excecute the corresponding instructions:

  nexLoop(nex_listen_list);  // Check for any touch event

}  // End of loop


