/*
 * File:   usbSerialComm.c   (Windows Version)
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: Contains functions to communicate with a serial port
 *          which is intended to be an control device connected via USB.
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

HANDLE g_controlDevice = NULL; //global variable that is a file handle to be used for Arduino Connection
DWORD g_btsIO;   //global variable that is used by the writeFile cmd to record number of bytes written


char extG_controllerTestCmd = 't';
char extG_controllerForwardCmd = 'w';
char extG_controllerBackCmd = 's';
char extG_controllerRightCmd = 'd';
char extG_controllerLeftCmd = 'a';
char extG_controllerExitCmd = 'x';
char g_last_userInpt[3];

int g_count = 0;

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
     g_controlDevice = CreateFile(inPortName, GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0); //opens serial port for read and write and locks it

    if (g_controlDevice != INVALID_HANDLE_VALUE && g_controlDevice != NULL) //if successfully opened
    {
        printf("\nSerial Port Opened! \n\n");

        DCB controDeviceConnectionSettings; //DCB structure(Windows)
        controDeviceConnectionSettings.DCBlength = sizeof(DCB);   //set length
        GetCommState(g_controlDevice,&controDeviceConnectionSettings); //retrieve current control settings for comm device
        controDeviceConnectionSettings.BaudRate = CBR_9600;    //right now hard code this to 9600 otherwise use baud rate   TODO!!!
        controDeviceConnectionSettings.ByteSize = 8;
        controDeviceConnectionSettings.Parity = NOPARITY;   //set parity
        controDeviceConnectionSettings.StopBits = ONESTOPBIT;   //set how many stop bits

        /*Alternate section once Arduino exhibits failure to communicate, these turn off various port settings
        controDeviceConnectionSettings.fBinary = FALSE;            // Binary mode; no EOF check
        controDeviceConnectionSettings.fOutxCtsFlow = TRUE;         // No CTS output flow control
        controDeviceConnectionSettings.fOutxDsrFlow = FALSE;         // No DSR output flow control
        controDeviceConnectionSettings.fDtrControl = DTR_CONTROL_ENABLE;  // DTR flow control type
        controDeviceConnectionSettings.fDsrSensitivity = FALSE;      // DSR sensitivity
        controDeviceConnectionSettings.fTXContinueOnXoff = TRUE;     // XOFF continues Tx
        controDeviceConnectionSettings.fOutX = FALSE;                // No XON/XOFF out flow control
        controDeviceConnectionSettings.fInX = FALSE;                 // No XON/XOFF in flow control
        controDeviceConnectionSettings.fErrorChar = FALSE;           // Disable error replacement
        controDeviceConnectionSettings.fNull = FALSE;                // Disable null stripping
        //lpTest.fRtsControl = RTS_CONTROL_ENABLE; //// RTS flow control
        controDeviceConnectionSettings.fAbortOnError = TRUE;        // Do not abort reads/writes on error
        */

        //Add enumeration for all baud rates? TODO

        SetCommState(g_controlDevice,&controDeviceConnectionSettings); //set the current control settings for the device

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
    return CloseHandle(g_controlDevice); //close the connection and return result (0 = failed)
    
} //end closeCommunication function


/**
 * Tests the connection (send and recieve) to the Arduino device.
 * Connected through the currently open "file". This function assumes
 * that the Arduino may have just started, and as such has a delay built in.
 * @return  int 0 for failure and non-zero for success
 */
int testControllerCommunication(void)
{
    char tempToSend[] = {extG_controllerTestCmd};
    delayProgram(2000);
    WriteFile(g_controlDevice,tempToSend,strlen(tempToSend),&g_btsIO,NULL);

    //TODO: Readfile here if we wish to do an 'ACK' from the Arduino

    return 1;

} //end testCommunication function


/**
 * Test the connection and motor/wheelchair movement capability of the
 * connected device with a defined test. 
 * This can be used in a startup test or for troubleshooting issues.
 */
void testWheelChairOperation(void)
{
      sendToWheelChairController(extG_controllerLeftCmd); 
      delayProgram(1500);
      sendToWheelChairController(extG_controllerRightCmd);
      delayProgram(1500);
      sendToWheelChairController(extG_controllerForwardCmd);
      delayProgram(1500);
      sendToWheelChairController(extG_controllerBackCmd);
      delayProgram(1500);
} //end testOperaiton 


/**
 * Sends a char to the currently open serial port.
 * @param toSend char to send to Arduino
 */
void sendToWheelChairController(char toSend)
{
    char tempToSend[] = {toSend};
    WriteFile(g_controlDevice,tempToSend,strlen(tempToSend),&g_btsIO,NULL); //writes char to arduino
} //end sendIntToArduino function


/**
 * Delays the program, used for delays between serial communication.
 * @param time int that is a time unit in milliseconds
 */
void delayProgram(int time)
{
    Sleep(time);
}
//END file usbSerialComm.c
