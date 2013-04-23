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
DCB g_controDeviceConnectionSettings; //DCB structure(Windows)
int g_connectedFlag = 0; //flag for connection to controller (0 not connected and 1 is connected)

char extG_controllerTestCmd = 't';
char extG_controllerForwardCmd = 'w';
char extG_controllerBackCmd = 's';
char extG_controllerRightCmd = 'd';
char extG_controllerLeftCmd = 'a';
char extG_controllerExitCmd = 'x';


/**
 * This function sets the baud rate if it's valid versus the valid baud rates
 * for Windows operating system's serial ports.
 * @param int baudNumber  to set if it's valid
 * @return int for success 1 is success, 0 is false
 */
int setBaudRate(const int baudNumber)
{
    int returnedNumber = 0;

    switch(baudNumber)
    {
        case 110:
            g_controDeviceConnectionSettings.BaudRate = CBR_110;
            returnedNumber = 1;
            break;
        case 300:
            g_controDeviceConnectionSettings.BaudRate = CBR_300;
            returnedNumber = 1;
            break;
        case 600:
            g_controDeviceConnectionSettings.BaudRate = CBR_600;
            returnedNumber = 1;
            break;
        case 1200:
            g_controDeviceConnectionSettings.BaudRate = CBR_1200;
            returnedNumber = 1;
            break;
        case 2400:
            g_controDeviceConnectionSettings.BaudRate = CBR_2400;
            returnedNumber = 1;
            break;
        case 4800:
            g_controDeviceConnectionSettings.BaudRate = CBR_4800;
            returnedNumber = 1;
            break;
        case 9600:
            g_controDeviceConnectionSettings.BaudRate = CBR_9600;
            returnedNumber = 1;
            break;
        case 14400:
            g_controDeviceConnectionSettings.BaudRate = CBR_14400;
            returnedNumber = 1;
            break;
        case 19200:
            g_controDeviceConnectionSettings.BaudRate = CBR_19200;
            returnedNumber = 1;
            break;
        case 38400:
            g_controDeviceConnectionSettings.BaudRate = CBR_38400;
            returnedNumber = 1;
            break;
        case 57600:
            g_controDeviceConnectionSettings.BaudRate = CBR_57600;
            returnedNumber = 1;
            break;
        case 115200:
            g_controDeviceConnectionSettings.BaudRate = CBR_115200;
            returnedNumber = 1;
            break;
        case 128000:
            g_controDeviceConnectionSettings.BaudRate = CBR_128000;
            returnedNumber = 1;
            break;
        case 256000:
            g_controDeviceConnectionSettings.BaudRate = CBR_256000;
            returnedNumber = 1;
            break;
        default:
            returnedNumber = 0;
            break;
    }

    return returnedNumber;

} //end setBaudRate function


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
    int resultFlag = 0;

    g_controlDevice = CreateFile(inPortName, GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0); //opens serial port for read and write and locks it

    if (g_controlDevice != INVALID_HANDLE_VALUE && g_controlDevice != NULL) //if successfully opened
    {
        printf("\nSerial Port Opened! \n\n");

        g_controDeviceConnectionSettings.DCBlength = sizeof(DCB);   //set length
        GetCommState(g_controlDevice,&g_controDeviceConnectionSettings); //retrieve current control settings for comm device
        
        resultFlag = setBaudRate(inPortBaudRate);

        if (resultFlag == 1)
        {
            resultFlag = 0;
            
            g_controDeviceConnectionSettings.ByteSize = 8;
            g_controDeviceConnectionSettings.Parity = NOPARITY;   //set parity
            g_controDeviceConnectionSettings.StopBits = ONESTOPBIT;   //set how many stop bits

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

            SetCommState(g_controlDevice,&g_controDeviceConnectionSettings); //set the current control settings for the device
            g_connectedFlag = 1; //set flag to say connection established.

            printf("\nSerial Port Settings Established! \n");

            resultFlag = 1; //success
        }
        else
        {
            printf("\n*Error setting baud rate: %d. Baud rate not found! "
                    "\n\tPlease make sure the baud rate is valid for serial "
                    "port communication. \n\n", inPortBaudRate);
        }
    }
    else
    {
        printf("\n*Error opening serial port %s at rate %i! Communication not established. \n\n",
                inPortName,inPortBaudRate);       
    }

    return resultFlag;
    
} //end function to setup communication with Arduino


/**
 * Closes the active connection and frees up resources.
 * @return int 0 for failure and non-zero for success
 */
int closeCommunication(void)
{
    char tempToSend[] = {extG_controllerExitCmd};

    if (g_connectedFlag > 0)
    {
        WriteFile(g_controlDevice,tempToSend,strlen(tempToSend),&g_btsIO,NULL); //sends exit command to the Arduino
    }

    return CloseHandle(g_controlDevice); //close the connection and return result (0 = failed)
    
} //end closeCommunication function


/**
 * Tests the connection (send and recieve) to the WChair Controller device.
 * Connected through the currently open "file". This function assumes
 * that the Controller may have just started, and as such has a delay built in.
 * The controller should be setup when it recieves the test command to send it back
 * on the serial port.
 * 
 * @return  int 0 for failure and 1 for success
 */
int testControllerCommunication(void)
{
    char tempToSend[] = {extG_controllerTestCmd};
    char tempToRecieve[strlen(tempToSend)+1];
    int resultFlag = 0;
  
    if (g_connectedFlag > 0)
    {
		printf("\nAttempting to communicate with the controller... ");
        delayProgram(2000);
        WriteFile(g_controlDevice,tempToSend,strlen(tempToSend),&g_btsIO,NULL);        
		ReadFile(g_controlDevice, &tempToRecieve, strlen(tempToSend), &g_btsIO, NULL); //blocks until input found! (can set timeout if desired)

        if ( strncmp(tempToRecieve,tempToSend,strlen(tempToSend)) == 0 )
        {
            resultFlag = 1; //success controller connected and communicating
			printf("\n\nController is connected and communication has been established.\n\n");
        }
    }

    if (resultFlag == 0)
    {
        printf("\n*Communication with WheelChair Controller failed!"
                " \n\tMake sure the port and baud rate are correct and that"
                " the Controller is connected and powered up. \n\n");
    }
    
    return resultFlag;

} //end testCommunication function


/**
 * Test the connection and motor/wheelchair movement capability of the
 * connected device with a defined test. 
 * This can be used in a startup test or for troubleshooting issues.
 */
void testWheelChairOperation(void)
{
	  printf("\nNow testing wheel chair movement and controller operation..."
			"\n\t Make sure there is a clear area around the wheelchair! \n\n"
			"Trying left movement... \n\n");
      sendToWheelChairController(extG_controllerLeftCmd); 
      delayProgram(2000);
	  printf("Trying right movement... \n\n");
      sendToWheelChairController(extG_controllerRightCmd);
      delayProgram(2000);
	  printf("Trying forward movement... \n\n");
      sendToWheelChairController(extG_controllerForwardCmd);
      delayProgram(2000);
	  printf("Trying backward movement... \n\n");
      sendToWheelChairController(extG_controllerBackCmd);
      delayProgram(2000);
	  printf("Finished testing wheelchair and controller operation.\n"
			"\tIf the wheelchair did not move as intended please make sure"
			"the device is connected and functioning properly.\n\n");

} //end testOperaiton 


/**
 * Sends a char to the currently open serial port.
 * No error checking due for speed reasons and most errors
 * are bigger failures, that cannot be rectified. If data doesn't get
 * transmitted, new data will be along shortly.
 * 
 * @param toSend char to send to Arduino
 */
void sendToWheelChairController(const char toSend)
{
    char tempToSend[] = {toSend};
    WriteFile(g_controlDevice,tempToSend,strlen(tempToSend),&g_btsIO,NULL); //writes char to controller
    //Not checking for errors here because new data will be passed along later and speed is needed.

} //end sendIntToArduino function


/**
 * Delays the program, used for delays between serial communication.
 * @param time int that is a time unit in milliseconds
 */
void delayProgram(const int time)
{
    Sleep(time);
} //end delayProgram function

//END file usbSerialComm.c
