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
const int LED = 13;			        //States that the LED is connected to pin 13 (Built-in)
const int FORWARDSERVO = 40;                    //States that the servo motor to move forward/back is connected to pin 40
const int SIDESERVO = 41;                       //States that the servo motor to move sideways (left/right) is connected to pin 41
const int BUTTON = 12;				//States that the BUTTON is connected to pin 12.
const int LEFT_MOTOR = 7;			//States that the left MOTOR is connected to pin 7.
const int RIGHT_MOTOR = 8;			//States that the right MOTOR is connected to pin 4.
const int TOGGLE_SWITCH = 4;                    //Current default value of the toggle switch being pin 8.
const int INTERRUPT = 0;			//Uses '0' as the interrupt number, which is set up with pin 2.
const int INTERRUPT_TWO = 1;                    //Uses '1' as the interrupt number, which is set up with pin 3.
volatile int STATE = LOW;			//Gives the variable STATE which will change between HIGH and LOW allowing for movement.
volatile int SWITCH = HIGH;			//Initializes the state of SWITCH to HIGH
int number;

/*
 * The four inputs that need to be changed if the user decides to change the inputs
 * in the source code.
 */
char inputLeft = 'a';
char inputRight = 'd';
char inputForward = 'w';
char inputBackward = 's';
/*
 * End user-adjusted information.
 */

const int PULSE = 1500;                         //Pulse value for servo motors
//Number used for communication between the Arduino and Keyboard via Serial Monitor

void setup(){							//Initial setup process for pins on input and output.
  Serial.begin(9600);					//Allows for use of the Serial Monitor
  pinMode(BUTTON, INPUT);	 				//Sets pin 12 as an input
  pinMode(TOGGLE_SWITCH, INPUT);                          //sets pin 8 as another input.
  pinMode(RIGHT_MOTOR, OUTPUT);				//Sets pin 4 as an output
  pinMode(LEFT_MOTOR, OUTPUT);	 			//Sets pin 7 as an output
  pinMode(FORWARDSERVO, OUTPUT);
  pinMode(SIDESERVO, OUTPUT);
  attachInterrupt(INTERRUPT, buttonPressed, RISING);	//Sets up the interrupt pin, specifices the called function and what mode to use
  attachInterrupt(INTERRUPT_TWO, toggleSwitch, CHANGE);   //Sets the interrupte of the toggle
}

void loop(){			        //Main loop which is constantly being run on the arduino
  number = 0;                         // zero the incoming number ready for a new read

  digitalWrite(SIDESERVO, HIGH);    //Set the pin to HIGH to +5V
  delayMicroseconds(PULSE);         //Wait for a specific time (timed pulse)
  digitalWrite(SIDESERVO, LOW);     //Set the pin to LOW
  delay(20);                        //Servo needs to be updated every 20-40ms


  delay(3000); //Keeps the previous motor spinning for 3 seconds
    
    /*
     * BEGIN:
     * Below code would be used for the serial reception and it would turn on the
     * servos depending on this. The code itself checks against the preset chars to 
     * evaluate if the servos will go forward, backward, left, or right.
     */
  while (Serial.available() == 0)
  {
    digitalWrite(LEFT_MOTOR, LOW);
    digitalWrite(RIGHT_MOTOR, LOW);
    //Disables the digital pins so that nothing is happening if you are not looking left or right. 
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
    }
    else
      goRight();
  }
    /*
     * END 
     * old code that is to be changed/is outdated in regards to our servos.
     */
    
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

void goRight(){
    //Push the vertical servo to the right to have the wheelchair go right.

}

void goLeft(){
    //Move the vertical (sideways) servo to the left to make the controller go left.
}

void goForward(){
    //Turn one of the servos on to go forward (the horizontal servo goes forward so the controller goes forward)
}

void goBackward(){
    //Push the horizontal servo backward to have the wheelchair/controller go backwards.
}

//END file arduinoCode.c

