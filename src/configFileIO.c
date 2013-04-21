/*
 * File:   fileIO.c   (Windows Version)
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: This class is set up to read/write a file for the user's configuration information.
 *  
 * Note: This is platform specific (Windows) and somewhat compiler specific.
 *       It uses Windows.h and conio.h header files.
 *
 * Created Spring, 2013
 */

#include <Windows.h>
#include <stdio.h>
#include "usbSerialComm.h"

void outputFile(int baudRate){
	char buffer[BUFSIZ];
	char configFile[] = "Configuration.txt";
	FILE *fp = NULL;
    
    fp = fopen(configFile, "w"); /* open file for writing */
    
    if(fp == NULL) /* checks if the file doesn't exist/returns null */
    {
        printf("Failed to open writeable file!\n");
        return -1;
    }
    fputs("Forward = ", fp);
    fputc(extG_controllerForwardCmd, fp);
    fputs("\nBackward = ", fp);
    fputc(extG_controllerBackCmd, fp);
    fputs("\nRight = ", fp);
    fputc(extG_controllerRightCmd, fp);
    fputs("\nLeft = ", fp);
    fputc(extG_controllerLeftCmd, fp);
    fputs("\nExit = ", fp);
    fputc(extG_controllerExitCmd, fp);
    fputs("\nBaud = ", fp);
    fprintf(fp, "%d\n", baudRate);
    fclose(fp); /* close file */
	return 0;
}

void inputFile(void){
    char buffer[BUFSIZ];
	char configFile[] = "Configuration.txt";
	FILE *fp = NULL;
    char *toFree;
    char *string;
    char *token;
    
    fp = fopen(configFile, "r"); /* open file for reading */
    if(fp == NULL)
    {
        printf("Failed to open file for reading\n");
        return -3;
    }
    
    while(fgets(buffer, BUFSIZ, fp) != NULL){
        //        sscanf("%s", );
        toFree = buffer;
        string = buffer;
        token = strsep(&string, " ");
        strsep(&string, " "); //Used to throw away the second token ("=")
        if(strncmp(token, "Forward", 100) == 0){
            token = strsep(&string, " ");
//            printf("%s", token);
        }else if(strncmp(token, "Backward", 100) == 0){
            token = strsep(&string, " ");
//            printf("%s", token);
        }else if(strncmp(token, "Right", 100) == 0){
            token = strsep(&string, " ");
//            printf("%s", token);
        }else if(strncmp(token, "Left", 100) == 0){
            token = strsep(&string, " ");
//            printf("%s", token);
        }else if(strncmp(token, "Exit", 100) == 0){
            token = strsep(&string, " ");
//            printf("%s", token);
        }if(strncmp(token, "Baud", 100) == 0){
            token = strsep(&string, " ");
//            printf("%s", token);
        }
        
    }
    free(toFree);
    fclose(fp);
    
    return 0;

    
}