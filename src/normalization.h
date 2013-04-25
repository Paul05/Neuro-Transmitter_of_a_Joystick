/*
* File: normalization.h
* Author: Neuro-Transmitter Group
* Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
* Class: CST315 & CST316 ASU Polytechnic
*
* Purpose: Handles the normalization for input from a Neuro-Headset.
*           The current version represents the Emotiv Epoc Headset and
*           the intricacies of their proprietary algorithm and the limitations
*           of that headset. Although, it does generally deal with the problem
*           of measuring eye movement and other facial movements with an EEG/EMG
*           device in general.
*
* Created Spring, 2013
*/

#ifndef NORMALIZATION_H
#define	NORMALIZATION_H

void callNormalizeDirectionFuncs(const char key, const int normalizeOptFlag);

#endif	/* NORMALIZATION_H */

//END file normalization.h/
