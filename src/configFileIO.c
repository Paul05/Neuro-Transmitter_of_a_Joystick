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

const char g_configFile[] = "Configuration.neuro";
FILE *gp_filePointer = NULL;

/*
 * This function is used to separate the information that is read in from the file 
 * of user's last saved configuration settings. It takes the string to seperate
 * and the delimeter to seperate on. It returns the seperated element of the string.
 * @param p_string, p_delimeter
 * @return
 */
char* mystrsep(char** p_string, const char* p_delimeter)
{
    char* p_start = *p_string;
    char* p_temp;
    
    p_temp = (p_start != NULL) ? strpbrk(p_start, p_delimeter) : NULL;
    
    if (p_temp == NULL)
    {
        *p_string = NULL;
    }
    else
    {
        *p_temp = '\0';
        *p_string = p_temp + 1;
    }
    
    return p_start;
    
} //end mystrsep

/**
 * This function saves the configuration settings that the user can change
 * to a configuration file in the program's folder. This file than can be reloaded
 * for quick setup with the inputConfigFile function.
 * @param baudRate
 * @return -1 for failure and 0 for success
 */
int outputConfigFile(const int baudRate, const char portName[])
{
    gp_filePointer = fopen(g_configFile, "w"); /* open file for writing */
    
    if(gp_filePointer == NULL) /* checks if the file doesn't exist/returns null */
    {
        printf("\n*Failed to create configuration file! Check folder permissions. \n\n");
        return -1;
    }
    else
    {
        fputs("Forward = ", gp_filePointer);
        fputc(extG_controllerForwardCmd, gp_filePointer);
        fputs("\nBackward = ", gp_filePointer);
        fputc(extG_controllerBackCmd, gp_filePointer);
        fputs("\nRight = ", gp_filePointer);
        fputc(extG_controllerRightCmd, gp_filePointer);
        fputs("\nLeft = ", gp_filePointer);
        fputc(extG_controllerLeftCmd, gp_filePointer);
        fputs("\nExit = ", gp_filePointer);
        fputc(extG_controllerExitCmd, gp_filePointer);
        fputs("\nBaud = ", gp_filePointer);
        fprintf(gp_filePointer, "%d", baudRate);
        fputs("\nPort = ", gp_filePointer);
        fprintf(gp_filePointer, "%s\n", portName);
        fclose(gp_filePointer); /* close file */
        printf("\n\n*****Configurations have been saved!*****\n\n");
        return 0;
    }
} //end outputFile function


/**
 * This reads in a previously saved configuration file for user changeable
 * settings in this program. It takes an input parameter of the portName and returns
 * the new portName in that variable. It returns -3 for failure and the baudRate
 * otherwise for success in addition to setting the global variables for the other values.
 * @return -3 for failure or saved baudRate for success
 */
int inputConfigFile(char portName[])
{
    char buffer[BUFSIZ];
    char *string;
    char *token;
    int baudRate = 0;
    
    gp_filePointer = fopen(g_configFile, "r"); /* open file for reading */
    if(gp_filePointer == NULL)
    {
        printf("\n\n*Failed to open file for reading! "
                "\n\tMake sure you saved a configuration file previously \n\tand "
                "security permissions are correct.\n\n");
        return -3;
    }
    else
    {
        while(fgets(buffer, BUFSIZ, gp_filePointer) != NULL)
        {
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
            }else if(strncmp(token, "Baud", 100) == 0){
                token = mystrsep(&string, " ");
                sscanf(token, "%d", &baudRate);
            }else if(strncmp(token, "Port", 100) == 0){
                token = mystrsep(&string, " ");
                sscanf(token, "%s", portName);
            }

        } //end while go through config file

        fclose(gp_filePointer);
        return baudRate;

    } //end if/else don't load on null   
}//end inputFile function


/*
 * Checks if the configuration file exists. Returns an int 1 for success.
 * @return 0 for failure and 1 for success
 */
int checkForExistingConfigFile(void)
{
    gp_filePointer = fopen(g_configFile, "r"); /* open file for reading */

    if(gp_filePointer == NULL)
    {
        return 0;
    }
    else
    {
        fclose(gp_filePointer); 
        return 1;
    }
    
}//end checkFile function

//END File configFileIO.c
