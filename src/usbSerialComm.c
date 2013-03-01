/*
 * File:   usbSerialComm.c
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose:
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


void setupCommunication()
{
    HANDLE hDevice = CreateFile(L"COM2",GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,0);

    char test[10] = "crap";
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

        WriteFile(hDevice,test,strlen(test),&btsIO,NULL);

        CloseHandle(hDevice);
    }


}




void usbSerialComm()
{
    printf("usbSerialComm\n");
}
//END file usbSerialComm.c
