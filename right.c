/*
 * File:   right.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose:
 *
 * Created Spring, 2013
 */
void goRight(){					//Function gets called as part of the predestined movement
	digitalWrite(LEFT_MOTOR, STATE);	//Writes the current state to the LEFT_MOTOR
	digitalWrite(RIGHT_MOTOR, !STATE);	//Writes the opposite state to the RIGHT_MOTOR (disabling the motor)
    
}

//END file right.c
