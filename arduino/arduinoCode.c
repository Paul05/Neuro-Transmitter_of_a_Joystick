/*
 * File:   right.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose:
 *
 * Created Spring, 2013
 *
 	DESCRIPTION: This code is designed to have an arduino go in a pattern of *Forward->Left->Right* and it will continue
 			this pattern every 5 seconds.
 	VERSION: 1.0.4
 	DATE: Friday, February 15, 2013
 */

#include <Servo.h>						//Includes the servo library

Servo FORWARDSERVO;						//Creates the servo object to control a servo 
Servo SIDESERVO;

const int INTERRUPT = 0;			//Uses '0' as the interrupt number, which is set up with pin 2.
volatile int BUTTONSTATE;
int number;

const int forwardservopin = 9;
const int sideservopin = 8;

boolean firstRun = true;
boolean secondRun = false;
boolean turnTo90 = true;
boolean turnTo45 = true;
/*
 * *******USER-ADJUSTED INFORMATION*******
 */
char inputLeft = 'a';
char inputRight = 'd';
char inputForward = 'w';
char inputBackward = 's';
char testChar = 't';
chat exitChar = 'x';

/*
 * *******USER-ADJUSTED INFORMATION*******
 */

const int PULSE = 1500;                         //Pulse value for servo motors
//Number used for communication between the Arduino and Keyboard via Serial Monitor

void setup(){							//Initial setup process for pins on input and output.
  Serial.begin(9600);					//Allows for use of the Serial Monitor
  FORWARDSERVO.attach(forwardservopin);
  SIDESERVO.attach(sideservopin);
  attachInterrupt(INTERRUPT, buttonPressed, RISING);	//Sets up the interrupt pin, specifices the called function and what mode to use
  FORWARDSERVO.write(20);
  SIDESERVO.write(40);
}

void loop(){			        //Main loop which is constantly being run on the arduino
  FORWARDSERVO.attach(forwardservopin);
  SIDESERVO.attach(sideservopin);
  number = 0;                         // zero the incoming number ready for a new read
  

  /*
     * BEGIN:
   * Below code would be used for the serial reception and it would turn on the
   * servos depending on this. The code itself checks against the preset chars to 
   * evaluate if the servos will go forward, backward, left, or right.
   */
  while (Serial.available() == 0){
    //Do nothing  
  }

  while (Serial.available() > 0)
  {
    number = Serial.read();   // read the number in the serial buffer,
    // remove the ASCII text offset for zero: '0'
  }

  if (number == inputLeft){
    goLeft();
  }
  else if (number == inputRight){
    goRight();
  }
  else if (number == inputForward){
    goForward();
  }
  else if (number == inputBackward){
    goBackward();
  }
  else if (number == testChar){
	Serial.write(testChar);
  }

  Serial.flush();
  /*
     * END IF/ELSE INFORMATION.
   */
}

void buttonPressed(){				// Function will disable the servo motors for manual override
  FORWARDSERVO.write(20);
  SIDESERVO.write(40);
  SIDESERVO.detach();
  FORWARDSERVO.detach();
}

void goRight(){
  //Push the vertical servo to the right to have the wheelchair go right.
 for(int i = 45; i >= 0; i -= 2)
    {
      //If the servo has reached 90 degrees, start to move the other direction to 45 degrees
      if(SIDESERVO.read() < 5)
      {        
        SIDESERVO.write(0);//Set the servo to 90 degrees exactly
        break;
      }
      SIDESERVO.write(i);
      delay(250);
    }
    delay(1500);
  
    for(int i = 0; i <= 45; i+= 2)
    {
      //If the servo has reached 0 degrees, start to move the other direction to 90 degrees
      if(SIDESERVO.read() >= 40)
      {
        SIDESERVO.write(45);//Set the servo to 45 degrees exactly
        break;
      }      
      
      SIDESERVO.write(i);
      delay(125);
    }
  SIDESERVO.detach();
}

void goLeft(){
  //Move the vertical (sideways) servo to the left to make the controller go left.
       for(int i = 45; i <= 90; i += 2)
    {
      //If the servo has reached 90 degrees, start to move the other direction to 45 degrees
      if(SIDESERVO.read() > 85)
      {        
        SIDESERVO.write(90);//Set the servo to 90 degrees exactly
        break;
      }
      SIDESERVO.write(i);
      delay(125);
    }
    delay(500);
  
    for(int i = 90; i >= 45; i-= 2)
    {
      //If the servo has reached 0 degrees, start to move the other direction to 90 degrees
      if(SIDESERVO.read() <= 50)
      {
        SIDESERVO.write(35);//Set the servo to 45 degrees exactly
        break;
      }      
      
      SIDESERVO.write(i);
      delay(50);
    }
  SIDESERVO.write(45);
  SIDESERVO.detach();
}

void goForward(){

     for(int i = 20; i <= 70; i += 2)
    {
      //If the servo has reached 90 degrees, start to move the other direction to 45 degrees
      if(FORWARDSERVO.read() > 65)
      {        
        FORWARDSERVO.write(70);//Set the servo to 90 degrees exactly
        break;
      }
      FORWARDSERVO.write(i);
      delay(75);
    }
    
  
    for(int i = 70; i >= 20; i-= 2)
    {
      //If the servo has reached 0 degrees, start to move the other direction to 90 degrees
      if(FORWARDSERVO.read() <= 25)
      {
        FORWARDSERVO.write(20);//Set the servo to 45 degrees exactly
        break;
      }      
      
      FORWARDSERVO.write(i);
      delay(75);
    }
  FORWARDSERVO.detach();
}

void goBackward(){
       for(int i = 20; i >= 0; i -= 2)
    {
      //If the servo has reached 90 degrees, start to move the other direction to 45 degrees
      if(FORWARDSERVO.read() < 5)
      {        
        FORWARDSERVO.write(0);//Set the servo to 90 degrees exactly
        break;
      }
      FORWARDSERVO.write(i);
      delay(125);
    }
    delay(2000);
  
    for(int i = 0; i <= 20; i+= 2)
    {
      //If the servo has reached 0 degrees, start to move the other direction to 90 degrees
      if(FORWARDSERVO.read() >= 20)
      {
        FORWARDSERVO.write(20);//Set the servo to 45 degrees exactly
        break;
      }      
      
      FORWARDSERVO.write(i);
      delay(125);
    }
  FORWARDSERVO.detach();
}

//END file arduinoCode.c