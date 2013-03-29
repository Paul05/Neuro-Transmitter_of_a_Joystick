//
//  changeKeys.c
//  
//
//  Created by Michael Berg on 3/29/13.
//
//

#include <stdio.h>

void changeKeys(){
    char defaultChange = '';
    printf("The default inputs are W for forward, A for backward, S for left, D for right, and X for exiting the program while moving the wheelchair. Do you wish to change the defaults? Type [Y] for yes or [N] for no.\n");
    defaultChange = getCharConsole();
    defaultChange = tolower(defaultChange);
    if(defaultChange == 'y'){
        printf("Do the motion to go forward and that will be the new forward key\n");
        arduinoForward = tolower(getCharConsole());
        printf("Now the command to go backwards in the wheelchair. \n");
        arduinoBack = tolower(getCharConsole());
        printf("Fantastic, halfway done. What would be the key command for left?\n");
        arduinoLeft = tolower(getCharConsole());
        printf("And last but not least the command to go right. \n");
        arduinoRight = tolower(getCharConsole());
        printf("Also, what is the new key to exit the program?\n");
        arduinoExit = tolower(getCharConsole());
        printf("Fantastic! All of the keys have now been changed succesfully.\n");
    }else{
        printf("All right, the defaults for forward, back, left, right, and exit have stayed the same.\n\n");
    }
    
    
}