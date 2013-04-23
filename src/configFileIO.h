/*
 * File:   fileIO.h
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: This file contains functions to read/write from or to a file
 *          containing the user's last saved or current configuration information.
 *
 * Created Spring, 2013
 */

#ifndef CONFIGFILEIO_H
#define CONFIGFILEIO_H

int outputConfigFile(const int baudRate, const char portName[]);
int inputConfigFile(char portName[]);
int checkForExistingConfigFile(void);

#endif /* CONFIGFILEIO_H */

//End of configFileIO.h