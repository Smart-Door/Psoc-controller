/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "uart_comm.h"
#include "motor.h"
#include "sensor.h"
#include "UART_1.h"
#include "PWM_1.h"

int venter_10_sek = 10000;

// Function prototype for processing commands
void processCommand(const char* command);

void processCommand(const char* command) {
    // Process the command here
    // For example:
    if (strcmp(command, "open_door") == 0) {
        
        PWM_1_Start();  //turns on led, shows Psoc is working
        
        UART_1_PutString("opens door\r\n");
        motor_open(); // Opens the door
        UART_1_PutString("The door is now open, waiting 10 seconds\r\n");
        CyDelay(venter_10_sek);
        UART_1_PutString("closing door now\r\n");
        motor_close(); //opens again if sensor is active and trying to close after 10 sec
        UART_1_PutString("door_closed\r\n"); //RPI takes control again
        
       
        PWM_1_Stop(); //turns off led, shows Psoc is done
    }
    else
    {
        UART_1_PutString("Ugyldig kommando modtaget: ");
        UART_1_PutString(command);
        UART_1_PutString("\r\n");
    }
   
}

void Handle_UART_Command(void) {
   
    static char command[15] = {0}; // Adjust the size as needed, static to preserve contents
    static unsigned int bufIndex = 0; // Static to preserve contents

    // Process all available characters
    while(UART_1_GetRxBufferSize()) {
        char received = UART_1_GetChar(); // Read one character
        if(received == '\r' || received == '\n') { // Check for end of line
            if (bufIndex > 0) { // Make sure the buffer is not empty
                processCommand(command);// check if command is valid
                
                command[bufIndex] = '\0'; // Null-terminate the string
                bufIndex = 0; // Reset buffer index
            }
        } else if (bufIndex < sizeof(command) - 1) {
            command[bufIndex++] = received; // Store the character
        } else {
            // Buffer overflow protection
            bufIndex = 0; 
        }
    }

     
}
/* [] END OF FILE */
