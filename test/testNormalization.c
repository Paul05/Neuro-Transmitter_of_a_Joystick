/*
* File: testMain.c
*
* Author: The Neuro-Transmitter Group
*         Frank Liu, Darryl Monroe, Michael Berg, Paul Spaude
*
* Class: CST315 & CST316 ASU Polytechnic
*        Copyright ASU Polytechnic 2013 All Rights Reserved.
*
* Function: Unit tests for the code found in main.c under src.
*
* Created: Spring, 2013
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "../src/normalization.h"

/**
 * Unit test for performMenuActionTest
 * @return 1 for success and 0 for failure
 */
int performTestaKey(void)
{
    int i;
	int result = 1;
    int resultFlag = 1;
    char passChar[6];
    char failChar[6];
    
    passChar[0] = 'w';
    passChar[1] = 'a';
    passChar[2] = 's';
    passChar[3] = 'd';
    passChar[4] = 'x';
    passChar[5] = 't';
    
    failChar[0] = 'z';
    failChar[1] = 'c';
    failChar[2] = 'v';
    failChar[3] = 'f';
    failChar[4] = 'g';
    failChar[5] = 'p';
    
    printf("Testing aKey... \n");

    for(i=0; i < 6; i++)
    {
        printf("The key %c should pass as a default working key.\n", passChar[i]);
        result = aKey(passChar[i]); 

        if (result < 1)
        {
            resultFlag = 0;
            printf("\n\t***Failure: didn't recieve expected positive return value!***\n");
            break;
        }
    }
    printf("\n");

    if ( result > 0)
    {
        for(i=0; i < 6; i++)
        {
            printf("The key %c should fail as a default working key.\n", failChar[i]);
			
            result = aKey(failChar[i]);

            if (result > 0)
            {
                resultFlag = 0;
                printf("\n\t***Failure: didn't recieve expected negative return value!***\n");
                break;
            }
        }
    }

    printf("\nFinished testing aKey function\n");

    return resultFlag;

} //end test for performMenuAction


/**
* This function runs the suite of tests above.
* @return 1 for success and 0 for failure
*/
int testNormalization(void)
{
    int success;

    printf("Testing normalization.c (aKey)... \n");
    success = performTestaKey();

    printf("\nnormalization.c suite finished: ");

    if (success == 1)
    {
        printf("success!\n");
    }
    else
    {
        printf("failure!\n");
    }

    return success;
       
} //testMain

//END File testMain.c
