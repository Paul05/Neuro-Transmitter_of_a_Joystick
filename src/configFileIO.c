/*
 * File:   fileIO.c   
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: This class is set up to read/write a file for the user's configuration information.
 *  
 * Created Spring, 2013
 */


#include <stdio.h>
#include "usbSerialComm.h"

/*
 * This function saves the information that the user has written!
 */
int outputFile(int baudRate){
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
/*
 * This reads the file (Configuration.txt) from the user's local folder.
 * It will then read through it and save the information as it is written in the file.
 *
 * IMPORTANT: The user must NOT change the format in the file, or else it will not work!
 *
 * TODO: Make it not break if it is changed in the file.
 */
int inputFile(int baudRate){
    char buffer[BUFSIZ];
	char configFile[] = "Configuration.txt";
	FILE *fp = NULL;
    char *string;
    char *token;
    
    fp = fopen(configFile, "r"); /* open file for reading */
    if(fp == NULL)
    {
        printf("Failed to open file for reading\n");
        return -3;
    }
    
    while(fgets(buffer, BUFSIZ, fp) != NULL){
        
/*        string = buffer;
        token = strsep(&string, " ");
        strsep(&string, " "); //Used to throw away the second token ("=")
        if(strncmp(token, "Forward", 100) == 0){
            token = strsep(&string, " ");
            sscanf(token, "%c", &extG_controllerForwardCmd);
        }else if(strncmp(token, "Backward", 100) == 0){
            token = strsep(&string, " ");
            sscanf(token, "%c", &extG_controllerBackCmd);
        }else if(strncmp(token, "Right", 100) == 0){
            token = strsep(&string, " ");
            sscanf(token, "%c", &extG_controllerRightCmd);
        }else if(strncmp(token, "Left", 100) == 0){
            token = strsep(&string, " ");
            sscanf(token, "%c", &extG_controllerLeftCmd);
        }else if(strncmp(token, "Exit", 100) == 0){
            token = strsep(&string, " ");
            sscanf(token, "%c", &extG_controllerExitCmd);
        }if(strncmp(token, "Baud", 100) == 0){
            token = strsep(&string, " ");
            sscanf(token, "%d", &baudRate);
        }
*/
    }
    fclose(fp);
    
    return 0;

    
}