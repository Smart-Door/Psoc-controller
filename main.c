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
#include "project.h"
#include "uart_comm.h" 
#include "sensor.h"


  
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    UART_1_Start();
    
    UART_1_PutString("Hello bitch! program begins now\r\n");
    
    for(;;)
    {
//        bool test = CheckWeight();
//         if (test) {
//            UART_1_PutString("Weight threshold exceeded!\r\n");
//        }
        
        /* Place your application code here. */
        Handle_UART_Command();
        
    }
}

/* [] END OF FILE */
