/*
 * File:   usbSerialComm.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: Contains functions to communicate with a serial port
 *          which is intended to be an arduino connected via USB.
 *  *
 * Note: This header file is platform neutral and designed to be used with
		  usbSerialCommNoWin and usbSerialCommWin depending. When installed
		  or built the name will be changed to usbSerialComm.c depending on 
		  the OS. 
 *
 * Created Spring, 2013
 */

#ifndef USBSERIALCOMM_H

//May have to redo these for linux port, probably put these in the usbSerialCommWin.c file and make another for the Unix version
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


//Global Commands for the controller
extern char extG_controllerTestCmd;
extern char extG_controllerForwardCmd;
extern char extG_controllerBackCmd;
extern char extG_controllerRightCmd;
extern char extG_controllerLeftCmd;
extern char extG_controllerExitCmd;


#define	USBSERIALCOMM_H

int setupCommunication(const char portName[], const int portBaudRate);
int closeCommunication(void);
int testControllerCommunication(void);
void testWheelChairOperation(void);
void sendToWheelChairController(const char toSend);
void delayProgram(const int time);

#endif	/* USBSERIALCOMM_H */

//END file usbSerialComm.h/
