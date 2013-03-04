/*
 * File:   usbSerialComm.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: Contains functions to communicate with a serial port
 *          which is intended to be an arduino connected via USB.
 *  *
 * Note: This is platform specific (Windows) and somewhat compiler specific.
 *       It uses Windows.h and conio.h header files.
 *
 * Created Spring, 2013
 */

#ifndef USBSERIALCOMM_H

 #ifndef STDPORTLENGTH
    #define STDPORTLENGTH 5    //size of the standard 1-9 com ports plus null
 #endif
 #ifndef LRGERPORTLENGTH
    #define LRGERPORTLENGTH 6    //size of 10+ com ports plus null
 #endif
 #ifndef DEVICENAMEAPPEND
    #define DEVICENAMEAPPEND "\\\\.\\"   //device or "DOS" name for serial port (this is backslashed for C, regular is: '\\.\COMXX'
 #endif
 #ifndef LWRBAUDRATE
    #define LWRBAUDRATE 110      //lower possible baud rate
 #endif
 #ifndef UPPRBAUDRATE
    #define UPPRBAUDRATE 256000  //upper possible baud rate
 #endif

#define	USBSERIALCOMM_H

int setupCommunication(const char portName[], const int portBaudRate);
int closeCommunication(void);
int testCommunication(void);
void sendIntToArduino(int toSend);

#endif	/* USBSERIALCOMM_H */

//END file usbSerialComm.h/
