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
	ORIGINAL AUTHOR: Darryl Monroe
	EDITOR: Michael Berg
	DESCRIPTION: This code is designed to have an arduino go in a pattern of *Forward->Left->Right* and it will continue
			this pattern every 5 seconds.
	VERSION: 1.0.2
	DATE: Friday, February 15, 2013
*/

const int BUTTON = 12;				//States that the BUTTON is connected to pin 12.
const int LEFT_MOTOR = 7;			//States that the left MOTOR is connected to pin 7.
const int RIGHT_MOTOR = 4;			//States that the right MOTOR is connected to pin 4. I think this is a motor pin, yes?
const int INTERRUPT = 0;			//Uses '0' as the interrupt number, which is set up with pin 2.
volatile int STATE = HIGH;			//Gives the variable STATE which will change between HIGH and LOW allowing for movement.

void setup(){							//Initial setup process for pins on input and output.
  	pinMode(BUTTON, INPUT);	 				//Sets pin 12 as the only input
	pinMode(RIGHT_MOTOR, OUTPUT);				//Sets pin 4 as an output
  	pinMode(LEFT_MOTOR, OUTPUT);	 			//Sets pin 7 as an output
  	attachInterrupt(INTERRUPT, buttonPressed, RISING);	//Sets up the interrupt pin, specifices the called function and what mode to use
}

void loop(){						//Main loop which is constantly being run on the arduino
	digitalRead(BUTTON);				//Reads the state of digital pin 12
	if(STATE == LOW){				//If the STATE is not HIGH then the movement should be halted. 
		digitalWrite(LEFT_MOTOR, STATE);	//Disables the LEFT_MOTOR
		digitalWrite(RIGHT_MOTOR, STATE);	//Disables the RIGHT_MOTOR
	}else{						//Else if the STATE is HIGH continue the predestined movement.
		goForward();				//Calls the "goForward" function which has both motors going, allowing for forward movement.
		delay(5000);				//Delays the arduino for 5 seconds (the arduino still goes straight)
		goLeft();				//Calls the "goLeft" function which turns off the left motor and turns on the right motor so it goes left.
		delay(5000);				//Delays the arduino for 5 seconds (the arduino still goes left)
		goRight();				//Calls the "goRight" function which turns off the right motor and turns on the left motor so it goes right.
		delay(5000);				//Delays the arduino for 5 seconds for the last time (the arduino still goes right)
	}
}

void buttonPressed(){				// function buttonPressed which gets called when an interrupt pin gets triggered
	STATE = !STATE;		 		// switches variable state to its opposite. From HIGH to LOW and vice versa, allowing the process to stop
}

void goRight(){					//Function gets called as part of the predestined movement
	digitalWrite(LEFT_MOTOR, STATE);	//Writes the current state to the LEFT_MOTOR
	digitalWrite(RIGHT_MOTOR, !STATE);	//Writes the opposite state to the RIGHT_MOTOR (disabling the motor)

}

void goLeft(){					//Function gets called as part of the predestined movement
	digitalWrite(RIGHT_MOTOR, STATE);	//Writes the current state to the RIGHT_MOTOR
	digitalWrite(LEFT_MOTOR, !STATE);	//Writes the opposite state to the LEFT_MOTOR (disabling the motor)
}

void goForward(){				//Function gets called as part of the predestined movement
	digitalWrite(RIGHT_MOTOR, STATE);	//Writes the current state to the RIGHT_MOTOR
	digitalWrite(LEFT_MOTOR, STATE);	//Writes the current state to the LEFT_MOTOR
}
 
//END file arduinoCode.c
