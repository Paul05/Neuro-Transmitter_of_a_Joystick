/* 
 * File:   main.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: Alg to smooth inputs. *
 *
 * Created Spring, 2013
 */

const int BUTTON = 12;				//States that the BUTTON is connected to pin 12.
const int LEFT_MOTOR = 7;			//States that the left MOTOR is connected to pin 7.
const int RIGHT_MOTOR = 4;			//States that the right MOTOR is connected to pin 4.
const int TOGGLE_SWITCH = 8;        //Current default value of the toggle switch being pin 8.
const int INTERRUPT = 0;			//Uses '0' as the interrupt number, which is set up with pin 2.
volatile int STATE = HIGH;			//Gives the variable STATE which will change between HIGH and LOW allowing for movement.
volatile int SWITCH = HIGH;

void setup(){							//Initial setup process for pins on input and output.
  	pinMode(BUTTON, INPUT);	 				//Sets pin 12 as the first input
    pinMode(TOGGLE_SWITCH, INPUT);          //Sets pin 8 as the second input.
	pinMode(RIGHT_MOTOR, OUTPUT);				//Sets pin 4 as an output
  	pinMode(LEFT_MOTOR, OUTPUT);	 			//Sets pin 7 as an output
  	attachInterrupt(INTERRUPT, buttonPressed, RISING);	//Sets up the interrupt pin, specifices the called function and what mode to use
    attachInterrupt(INTERRUPT, toggleSwitch, CHANGE);
}

void loop(){						//Main loop which is constantly being run on the arduino
	digitalRead(BUTTON);				//Reads the state of digital pin 12
    digitalRead(TOGGLE_SWITCH);         //Reads the state of digital pin 8.
    if(STATE == HIGH)
    {
        if(SWITCH == HIGH){
            digitalWrite(LEFT_MOTOR, STATE);
        }else
            digitalWrite(RIGHT_MOTOR, STATE);
    }
}

void buttonPressed(){
//    if(STATE == HIGH)
//    {
//        if(SWITCH == HIGH){
//            digitalWrite(LEFT_MOTOR, STATE);
//        }else
//            digitalWrite(RIGHT_MOTOR, STATE);
//    }
    STATE = !STATE;
}

//END File main.c
