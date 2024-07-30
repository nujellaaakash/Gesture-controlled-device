CODE:_

const int trigger1 = 2; //Trigger pin of 1st Sesnor

const int echo1 = 3; //Echo pin of 1st Sesnor

const int trigger2 = 4; //Trigger pin of 2nd Sesnor

const int echo2 = 5;//Echo pin of 2nd Sesnor


long time_taken;

int dist,distL,distR;
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX, TX

void setup() {

Serial.begin(9600); 

  
 BTSerial.begin(9600);
pinMode(trigger1, OUTPUT); 

pinMode(echo1, INPUT); 

pinMode(trigger2, OUTPUT); 

pinMode(echo2, INPUT); 

}


/###Function to calculate distance###/

void calculate_distance(int trigger, int echo)

{

digitalWrite(trigger, LOW);

delayMicroseconds(10);

digitalWrite(trigger, HIGH);

delayMicroseconds(10);

digitalWrite(trigger, LOW);


time_taken = pulseIn(echo, HIGH);

dist= time_taken*0.034/2;

if (dist>50)

dist = 50;

}


void loop() { //infinite loopy

calculate_distance(trigger1,echo1);

distL =dist; //get distance of left sensor


calculate_distance(trigger2,echo2);

distR =dist; //get distance of right sensor

//Lock Right - Control Mode

if (distR>=20 && distR<=30||distL>=20 && distL<=30)

{

  delay(50); //Hand Hold Time

  calculate_distance(trigger2,echo2);

  distR =dist;
  calculate_distance(trigger1,echo1);

  distL =dist;
  

  if(distR>=20 && distR<=30)
  {
        BTSerial.println("Forward");
Serial.println ("Forward"); delay (50);}
  if(distL>=20 && distL<=30)
  {    BTSerial.println("Rewind");

    Serial.println ("Rewind"); delay (50);}

}
delay(50);
}



PYTHON CODE: 
import serial                                      # add Serial library for serial communication
import pyautogui                                   # add pyautogui library for programmatically controlling the mouse and keyboard.

Arduino_Serial = serial.Serial('COM8',9600)       # Initialize serial and Create Serial port object called Arduino_Serial
 
while 1:
    incoming_data = str (Arduino_Serial.readline()) # read the serial data and print it as line
    print(incoming_data)                            # print the incoming Serial data
    if 'Rewind' in incoming_data:                    # if incoming data is 'down'
        #pyautogui.press('down')                   # performs "down arrow" operation which scrolls down the page
        #pyautogui.scroll(-1)
        pyautogui.press('down')
         
    if 'Forward' in incoming_data:                      # if incoming data is 'up'
        #pyautogui.press('up')                      # performs "up arrow" operation which scrolls up the page
        #pyautogui.scroll(1)
        pyautogui.press('up')
    incoming_data = "";                            # clears the data

