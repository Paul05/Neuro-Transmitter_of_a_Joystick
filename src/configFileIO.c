/*
 * File:   fileIO.c   
 * Author: Neuro-Transmitter Group
 *         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
 * Class: CST315 & CST316 ASU Polytechnic
 *
 * Purpose: This file contains functions to read/write from or to a file
 *          containing the user's last saved or current configuration information.
 *  
 * Created Spring, 2013
 */

#include <stdio.h>
#include <string.h>
#include "usbSerialComm.h"

char configFile[] = "Configuration.neuro";
FILE *fp = NULL;
int baudRate;

/*
 * This function is used to separate the information that is read in from the file 
 *  (Configuration.txt)
 * @param stringp, delim
 * @return
 */

char* mystrsep(char** stringp, const char* delim)
{
    char* start = *stringp;
    char* p;
    
    p = (start != NULL) ? strpbrk(start, delim) : NULL;
    
    if (p == NULL)
    {
        *stringp = NULL;
    }
    else
    {
        *p = '\0';
        *stringp = p + 1;
    }
    
    return start;
}

/**
 * This function saves the information that the user has written!
 * 
 * @param baudRate
 * @return
 */
int outputFile(int baudRate)
{
    
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
    printf("\n\n*****Configuration has been saved!*****\n\n");
	return 0;
} //end outputFile function


/**
 * This reads the file (Configuration.txt) from the user's local folder.
 * It will then read through it and save the information as it is written in the file.
 *
 * IMPORTANT: The user must NOT change the format in the file, or else it will not work!
 *
 * TODO: Make it not break if it is changed in the file.
 * 
 * @param baudRate
 * @return
 */
int inputFile()
{
    char buffer[BUFSIZ];
    char *string;
    char *token;
    
    fp = fopen(configFile, "r"); /* open file for reading */
    if(fp == NULL)
    {
        printf("Failed to open file for reading\n");
        return -3;
    }
    
    while(fgets(buffer, BUFSIZ, fp) != NULL){
        
        string = buffer;
        token = mystrsep(&string, " ");
        mystrsep(&string, " "); //Used to throw away the second token ("=")
        if(strncmp(token, "Forward", 100) == 0){
            token = mystrsep(&string, " ");
            sscanf(token, "%c", &extG_controllerForwardCmd);
        }else if(strncmp(token, "Backward", 100) == 0){
            token = mystrsep(&string, " ");
            sscanf(token, "%c", &extG_controllerBackCmd);
        }else if(strncmp(token, "Right", 100) == 0){
            token = mystrsep(&string, " ");
            sscanf(token, "%c", &extG_controllerRightCmd);
        }else if(strncmp(token, "Left", 100) == 0){
            token = mystrsep(&string, " ");
            sscanf(token, "%c", &extG_controllerLeftCmd);
        }else if(strncmp(token, "Exit", 100) == 0){
            token = mystrsep(&string, " ");
            sscanf(token, "%c", &extG_controllerExitCmd);
        }if(strncmp(token, "Baud", 100) == 0){
            token = mystrsep(&string, " ");
            sscanf(token, "%d", &baudRate);
        }
        
    }
    fclose(fp);
    
    return baudRate;
    
}//end inputFile function

/*
 * Checks if the file exists, and then shows the user the configuration
 * @param baudRate
 * @return
 */

int checkFile(){
    fp = fopen(configFile, "r"); /* open file for reading */
    if(fp == NULL)
    {
        return 0;
    }
    fclose(fp);
    
    printf("Configuration file found in folder!"
           "\nLoading information...");
    inputFile(baudRate);
    printf("Complete!");
    return 1;
    
    
}//end checkFile function

//END File configFileIO.c
