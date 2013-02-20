/*
 * File:   forward.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose:
 *
 * Created Spring, 2013
 */
void goForward(){				//Function gets called as part of the predestined movement
	digitalWrite(RIGHT_MOTOR, STATE);	//Writes the current state to the RIGHT_MOTOR
	digitalWrite(LEFT_MOTOR, STATE);	//Writes the current state to the LEFT_MOTOR
}

//END file forward.c
