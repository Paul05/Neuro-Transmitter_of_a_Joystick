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
const int LED = 13;					//States that the LED is connected to pin 13 (Built-in)
const int BUTTON = 12;				//States that the BUTTON is connected to pin 12.
const int LEFT_MOTOR = 7;			//States that the left MOTOR is connected to pin 7.
const int RIGHT_MOTOR = 8;			//States that the right MOTOR is connected to pin 4.
const int TOGGLE_SWITCH = 4;        //Current default value of the toggle switch being pin 8.
const int INTERRUPT = 0;			//Uses '0' as the interrupt number, which is set up with pin 2.
const int INTERRUPT_TWO = 1;        //Uses '1' as the interrupt number, which is set up with pin 3.
volatile int STATE = LOW;			//Gives the variable STATE which will change between HIGH and LOW allowing for movement.
volatile int SWITCH = HIGH;			//Initializes the state of SWITCH to HIGH
int number;
char inputLeft = 'a';
char inputRight = 'd';
							//Number used for communication between the Arduino and Keyboard via Serial Monitor

void setup(){							//Initial setup process for pins on input and output.
  	Serial.begin(9600);					//Allows for use of the Serial Monitor
	pinMode(BUTTON, INPUT);	 				//Sets pin 12 as an input
    pinMode(TOGGLE_SWITCH, INPUT);          //sets pin 8 as another input.
	pinMode(RIGHT_MOTOR, OUTPUT);				//Sets pin 4 as an output
  	pinMode(LEFT_MOTOR, OUTPUT);	 			//Sets pin 7 as an output
  	attachInterrupt(INTERRUPT, buttonPressed, RISING);	//Sets up the interrupt pin, specifices the called function and what mode to use
    attachInterrupt(INTERRUPT_TWO, toggleSwitch, CHANGE); //Sets the interrupte of the toggle
}

void loop(){						//Main loop which is constantly being run on the arduino
  number = 0;
  					// zero the incoming number ready for a new read
  while (Serial.available() == 0)
  {
    // do nothing until something enters the serial buffer
  } 
  while (Serial.available() > 0)
  {
    number = Serial.read();   // read the number in the serial buffer,
									// remove the ASCII text offset for zero: '0'
  }

  Serial.print("You entered: ");
  Serial.println(number);
  
  if (number == inputLeft){
        Serial.println("Turning the Right Motor off");
	Serial.println("Turning the Left Motor on");
	digitalWrite(RIGHT_MOTOR, LOW);
	digitalWrite(LEFT_MOTOR, HIGH);
	}
  else if (number == inputRight){
        Serial.println("Turning the Left Motor off");
	Serial.println("Turning the Right Motor on");
	digitalWrite(LEFT_MOTOR, LOW);
	digitalWrite(RIGHT_MOTOR, HIGH);
	}
  else {
    digitalWrite(LEFT_MOTOR, LOW);
    digitalWrite(RIGHT_MOTOR, LOW);
  }
  Serial.flush();
	
	digitalRead(BUTTON);				//Reads the state of digital pin 12
    digitalRead(TOGGLE_SWITCH);         //Reads the state of digital pin 8.
    if(STATE == HIGH)
    {
        if(SWITCH == HIGH){
            goLeft();
        }else
            goRight();
    }
}

void toggleSwitch(){
    SWITCH = !SWITCH;       //Changes which motor to go.
}

void buttonPressed(){				// function buttonPressed which gets called when an interrupt pin gets triggered
	STATE = !STATE;		 		// switches variable state to its opposite. From HIGH to LOW and vice versa, allowing the process to stop
    if(STATE == LOW){
        digitalWrite(LEFT_MOTOR, STATE);
        digitalWrite(RIGHT_MOTOR, STATE);
    }
    
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
