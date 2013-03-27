/*
 * File:   usbSerialComm.c   (Windows Version)
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: Contains functions to communicate with a serial port
 *          which is intended to be an arduino connected via USB.
 *  
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
DWORD g_btsIO;   //global variable that is used by the writeFile cmd to record number of bytes written
char g_stringToSend[] = "x"; //global variable used for string to send

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
        printf("\nSerial Port Opened! \n\n");

        DCB arduinoControlSettings; //DCB structure(Windows)
        arduinoControlSettings.DCBlength = sizeof(DCB);   //set length
        GetCommState(g_arduinoDevice,&arduinoControlSettings); //retrieve current control settings for comm device
        arduinoControlSettings.BaudRate = CBR_9600;    //right now hard code this to 9600 otherwise use baud rate   TODO!!!
        arduinoControlSettings.ByteSize = 8;
        arduinoControlSettings.Parity = NOPARITY;   //set parity
        arduinoControlSettings.StopBits = ONESTOPBIT;   //set how many stop bits

        /*Alternate section once Arduino exhibits failure to communicate, these turn off various port settings
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

        //Add enumeration for all baud rates? TODO

        SetCommState(g_arduinoDevice,&arduinoControlSettings); //set the current control settings for the device

        printf("\nSerial Port Settings Established! \n");
        
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
 * Tests the connection (send and recieve) to the Arduino device.
 * Connected through the currently open "file". This function assumes
 * that the Arduino may have just started, and as such has a delay built in.
 * @return  int 0 for failure and non-zero for success
 */
int testCommunication(void)
{
    Sleep(1000);   
    WriteFile(g_arduinoDevice,arduinoTest,strlen(arduinoTest),&g_btsIO,NULL);

    //TODO: Readfile here if we wish to do an 'ACK' from the Arduno

    return 1;

} //end testCommunication function


/**
 * Test the connection and motor/wheelchair movment capability of the
 * Arduino with a defined test. This can be used in a startup test or for
 * troubleshooting issues.
 * @return int 0 for failure and non-zero for success
 */
int testMotorMovement(void)
{
      sendToArduino(arduinoLeft); //Test Actual Movement (Wheelchair turns left then right for example, test functions etc.) //TODO
      Sleep(500);
      sendToArduino(arduinoRight);
}


/**
 * Sends a char to the currently open serial port.
 * @param toSend char to send to Arduino
 */
void sendToArduino(char toSend[])
{
   WriteFile(g_arduinoDevice,toSend,strlen(toSend),&g_btsIO,NULL); //writes char to arduino
} //end sendIntToArduino function

void delayProgram(int time){
#ifdef WIN32
    sleep(time);
#else
#ifdef LINUX
    usleep(time*1000);
}
//END file usbSerialComm.c
