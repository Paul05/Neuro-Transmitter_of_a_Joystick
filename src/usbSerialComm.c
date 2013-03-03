/*
 * File:   usbSerialComm.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: Using Windows OS, contains functions to communicate with a serial port
 * which is intended to be an arduino connected via USB.
 *
 * Created Spring, 2013
 */


#include <Windows.h>
#include <stdio.h>
#include <conio.h>


/*
 One to open the correct serial port correctly.
One to read data from the serial port.
One to send data to the serial port.
One to close the serial port when you are done.
 */


int setupCommunication(const char portName[], const int portBaudRate)
{
    HANDLE hDevice = CreateFile(L"COM2",GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,0);

    if (hDevice !=INVALID_HANDLE_VALUE)
    {
        printf("Port opened! \n");
        DCB lpTest;
        GetCommState(hDevice,&lpTest);
        lpTest.BaudRate = CBR_9600;
        lpTest.ByteSize = 8;
        lpTest.Parity = NOPARITY;
        lpTest.StopBits = ONESTOPBIT;
        SetCommState(hDevice,&lpTest);

        DWORD btsIO;

      //  WriteFile(hDevice,test,strlen(test),&btsIO,NULL);

        CloseHandle(hDevice);

        return 1;
    }
    else
    {
        printf("FAILED\n");
        return 0;
    }


}

//END file usbSerialComm.c
