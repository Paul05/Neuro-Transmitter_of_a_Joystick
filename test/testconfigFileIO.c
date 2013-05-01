/*
* File: testconfigFileIO.c
*
* Author: The Neuro-Transmitter Group
*         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
*
* Class: CST315 & CST316 ASU Polytechnic
*        Copyright ASU Polytechnic 2013 All Rights Reserved.
*
* Function: Unit tests for the code found in configFileIO.c under src.
*
* NOTE: RETURNS WARNING FROM ANT BUILD, COMMENTING OUT TEST FOR POSSIBLE FUTURE USE.
 *
* Created: Spring, 2013
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/configFileIO.h"

/**
 * Unit test for function mystrsep
 * @return 1 for success and 0 for failure
 */
int performMyStrsep(void)
{
//    char* buffer[20];// = "Walk this way";
    int i;
	int result = 1;
    int resultFlag = 1;
    char* string;
    string = "Walk this way";
    char* token;
//    token = mystrsep(&string, " ");
//    string = buffer;
//    token = mystrsep(&string, " ");

    
    
    printf("Testing mystrsep... \n");
    
    printf("Using strsep with \" \" as the seperator.");

    for(i = 0; i < 3; ++i){
//        token = mystrsep(&string, " ");
        
        if(strncmp(token, "Walk", 100) == 0){
            result = 1;
        }else if(strncmp(token, "this", 100) == 0){
            result = 1;
        }else if(strncmp(token, "way", 100) == 0){
            result = 1;
        }else{
            printf("\n\t***Failure: didn't receive expected value!***\n");
            result = 0;
            resultFlag = 0;
            break;
        }
        
    } //end for loop
    printf("\n");
//    string = buffer;
//    token = mystrsep(&string, "q");


    if (result > 0)
    {
            printf("Using strsep with \"q\" as the seperator.");
        
        for(i = 0; i < 3; ++i){
//            token = mystrsep(&string, "q");
            

            if (strncmp(token, "Walk", 100) == 0 || strncmp(token, "this", 100) == 0 || strncmp(token, "way", 100) == 0)
            {
                resultFlag = 0;
                printf("\n\t***Failure: received a value!***\n");
                break;
            }
        }
    }

    printf("\nFinished testing mystrsep function\n");

    return resultFlag;

} //end test for mystrsep


/**
* This function runs the suite of tests above.
* @return 1 for success and 0 for failure
*/
int testMystrsep(void)
{
    int success;

    printf("Testing configFileIO.c (mystrsep)... \n");
    success = performMyStrsep();

    printf("\nconfigFileIO.c suite finished: ");

    if (success == 1)
    {
        printf("success!\n");
    }
    else
    {
        printf("failure!\n");
    }

    return success;
       
} //testMystrsep

//END File testMystrsep.c
