/*
 * File:   left.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: 
 *
 * Created Spring, 2013
 */
void goLeft(){					//Function gets called as part of the predestined movement
	digitalWrite(RIGHT_MOTOR, STATE);	//Writes the current state to the RIGHT_MOTOR
	digitalWrite(LEFT_MOTOR, !STATE);	//Writes the opposite state to the LEFT_MOTOR (disabling the motor)
}
//END file left.c
