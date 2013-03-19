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

#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include "usbSerialComm.h"


HANDLE g_arduinoDevice = NULL; //global variable that is a file handle to be used for Arduino Connection


/**
 * Purpose: Sets up communication on port specified at baud rate specified if
 * possible and handles the details. It returns an integer where non-zero is
 * success meaning the connection was setup successfully.
 *
 * For more information on CreateFile see this link:
 * http://msdn.microsoft.com/en-us/library/windows/desktop/aa363858%28v=vs.85%29.aspx
 *
 * @param portName String name of port to open (if COM10+ needs to be DOS name \\.\COM10 etc.)
 * @param portBaudRate Int for the baud rate of connection (serial) to the Arduino 9600 is standard.
 * @return int for success 0 is failed and 1 is success
 */
int setupCommunication(const char inPortName[], const int inPortBaudRate)
{
     g_arduinoDevice = CreateFile(inPortName, GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0); //opens serial port for read and write and locks it

    if (g_arduinoDevice != INVALID_HANDLE_VALUE && g_arduinoDevice != NULL) //if successfully opened
    {
        printf("\nDevice Port opened! \n\n");

        DCB arduinoControlSettings; //DCB structure(Windows)
        arduinoControlSettings.DCBlength = sizeof(DCB);   //set length
        GetCommState(g_arduinoDevice,&arduinoControlSettings); //retrieve current control settings for comm device
        arduinoControlSettings.BaudRate = CBR_9600;    //right now hard code this to 9600 otherwise use baud rate   TODO!!!
        arduinoControlSettings.ByteSize = 8;
        arduinoControlSettings.Parity = NOPARITY;   //set parity
        arduinoControlSettings.StopBits = ONESTOPBIT;   //set how many stop bits

/*  We will have to see about this, char is 8 bits, we might have to use ints! Arduino has a weird timing issue.
 *  Also, need setup delay because Arduino resets when first connect. 
 *
 * Also: enum baudRates { ?? } for various baud rates
 
        arduinoControlSettings.fBinary = FALSE;            // Binary mode; no EOF check
        arduinoControlSettings.fOutxCtsFlow = TRUE;         // No CTS output flow control
        arduinoControlSettings.fOutxDsrFlow = FALSE;         // No DSR output flow control
        arduinoControlSettings.fDtrControl = DTR_CONTROL_ENABLE;  // DTR flow control type
        arduinoControlSettings.fDsrSensitivity = FALSE;      // DSR sensitivity
        arduinoControlSettings.fTXContinueOnXoff = TRUE;     // XOFF continues Tx
        arduinoControlSettings.fOutX = FALSE;                // No XON/XOFF out flow control
        arduinoControlSettings.fInX = FALSE;                 // No XON/XOFF in flow control
        arduinoControlSettings.fErrorChar = FALSE;           // Disable error replacement
        arduinoControlSettings.fNull = FALSE;                // Disable null stripping
        //lpTest.fRtsControl = RTS_CONTROL_ENABLE; //// RTS flow control
        arduinoControlSettings.fAbortOnError = TRUE;        // Do not abort reads/writes on error
*/

        SetCommState(g_arduinoDevice,&arduinoControlSettings); //set the current control settings for the device

        printf("\nDevice Settings Established! \n");
        
        return 1; //success
    }
    else
    {
        printf("\n*Error opening serial port %s at rate %i! Communication not established. \n\n",
                inPortName,inPortBaudRate);
        return 0; //failure
    }
} //end function to setup communication with Arduino


/**
 * Closes the active connection and frees up resources.
 * @return int 0 for failure and non-zero for success
 */
int closeCommunication(void)
{
    return CloseHandle(g_arduinoDevice); //close the connection and return result (0 = failed)
    
} //end closeCommunication function


/**
 * Tests the connection (send and recieve) from the Arduino device
 * connected on the currently open connection.
 * @return  int 0 for failure and non-zero for success
 */
int testCommunication(void)
{
     DWORD btsIO;
     //Write in delay first then... 
     //Send char T for example and arduino will communicate back
     //WriteFile(g_arduinoDevice,test,strlen(test),&btsIO,NULL);

     return 1;

} //end testCommunication function 


/**
 * Sends an integer to the currently open device.
 * @param toSend integer to send to Arduino
 */
void sendIntToArduino(int toSend)
{
    
    /*
     * We could set something up:
     *  w = 1 forward
     *  a = 2 left
     *  d = 3 right
     *  s = -1 reverse
     *  ? = 0 neutral do nothing
     *  t = 9 test
     */

    //WriteFile(g_arduinoDevice,test,strlen(test),&btsIO,NULL);

   
} //end sendIntToArduino function

//END file usbSerialComm.c
