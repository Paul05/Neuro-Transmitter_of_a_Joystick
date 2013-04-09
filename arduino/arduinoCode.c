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

/*
 * *******USER-ADJUSTED INFORMATION*******
 */
char inputLeft = 'a';
char inputRight = 'd';
char inputForward = 'w';
char inputBackward = 's';
/*
 * *******USER-ADJUSTED INFORMATION*******
 */

const int PULSE = 1500;                         //Pulse value for servo motors
//Number used for communication between the Arduino and Keyboard via Serial Monitor

void setup(){							//Initial setup process for pins on input and output.
  Serial.begin(9600);					//Allows for use of the Serial Monitor
  FORWARDSERVO.attach(8);
  SIDESERVO.attach(9);
  attachInterrupt(INTERRUPT, buttonPressed, RISING);	//Sets up the interrupt pin, specifices the called function and what mode to use
}

void loop(){			        //Main loop which is constantly being run on the arduino
  FORWARDSERVO.attach(8);
  SIDESERVO.attach(9);
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
  else {
    Serial.println("Sorry, I didn't recognize your input. Please re-enter your input.");
  }
  Serial.flush();
  /*
     * END IF/ELSE INFORMATION.
   */
}

void buttonPressed(){				// Function will disable the servo motors for manual override
  SIDESERVO.detach();
  FORWARDSERVO.detach();
}

void goRight(){
  //Push the vertical servo to the right to have the wheelchair go right.
  SIDESERVO.write(120);
  delay(15);
  SIDESERVO.write(-150);
  delay(15);
  SIDESERVO.detach();
}

void goLeft(){
  //Move the vertical (sideways) servo to the left to make the controller go left.
  SIDESERVO.write(-170);
  delay(15);
  SIDESERVO.write(100);
  delay(15);
  SIDESERVO.detach();
}

void goForward(){
  //Turn one of the servos on to go forward (the horizontal servo goes forward so the controller goes forward)
  FORWARDSERVO.write(-170);
  delay(15);
  FORWARDSERVO.write(100);
  delay(15);
  FORWARDSERVO.detach();
}

void goBackward(){
  //Push the horizontal servo backward to have the wheelchair/controller go backwards.
  FORWARDSERVO.write(120);
  delay(15);
  FORWARDSERVO.write(-150);
  delay(15);
  FORWARDSERVO.detach();
}

//END file arduinoCode.c