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
#include "motor.h"
#include "project.h"
#include "sensor.h"



void motor_open()
{
    uint8_t speed  = 10;  //Variabel to Motor speed
    int fullRotationSteps = 200; //50 steps is one cycle
    
    for (int i = 0; i < fullRotationSteps; i++)
    {
        IN_1_Write(0);
        IN_2_Write(1);
        IN_3_Write(1);
        IN_4_Write(0);   
                
        CyDelay(speed);
                 
        IN_1_Write(0);
        IN_2_Write(1);
        IN_3_Write(0);
        IN_4_Write(1);

        CyDelay(speed);
                
        IN_1_Write(1);
        IN_2_Write(0);
        IN_3_Write(0);
        IN_4_Write(1);
          
        CyDelay(speed);
                
        IN_1_Write(1);
        IN_2_Write(0);
        IN_3_Write(1);
        IN_4_Write(0);
               
        CyDelay(speed);
    }
}

void motor_close()
{
    uint8_t speed  = 10; 
    int fullRotationSteps = 200;
    int currentStep;
    
    for (currentStep = 0; currentStep < fullRotationSteps; currentStep++)
    {
          bool sensorIsActive = CheckWeight();
        //stopper motor med det samme hvis sensor er aktiv
        if(sensorIsActive)
        {
            
            motor_stop();
            CyDelay(3000);// delay neccesary due to spole energy
            UART_1_PutString("obstruction_detected\r\n");  
            //the door opens fast to start position, with parameter of startstep  
            motor_fast_open( fullRotationSteps - currentStep);
            break;
        }
        
    
        IN_1_Write(1);
        IN_2_Write(0);
        IN_3_Write(1);
        IN_4_Write(0);
              
        CyDelay(speed);
       
        IN_1_Write(1);
        IN_2_Write(0);
        IN_3_Write(0);
        IN_4_Write(1);
          
        CyDelay(speed);
                
        IN_1_Write(0);
        IN_2_Write(1);
        IN_3_Write(0);
        IN_4_Write(1);
     
        CyDelay(speed);
                
        IN_1_Write(0);
        IN_2_Write(1);
        IN_3_Write(1);
        IN_4_Write(0);   
                
        CyDelay(speed);
    }
}

void motor_fast_open(int startStep)
{
    uint8_t speed  = 5;  
    int fullRotationSteps = 200;
    
    for (int i = startStep; i < fullRotationSteps; i++)
    {
        IN_1_Write(0);
        IN_2_Write(1);
        IN_3_Write(1);
        IN_4_Write(0);   
                
        CyDelay(speed);
                 
        IN_1_Write(0);
        IN_2_Write(1);
        IN_3_Write(0);
        IN_4_Write(1);

        CyDelay(speed);
                
        IN_1_Write(1);
        IN_2_Write(0);
        IN_3_Write(0);
        IN_4_Write(1);
          
        CyDelay(speed);
                
        IN_1_Write(1);
        IN_2_Write(0);
        IN_3_Write(1);
        IN_4_Write(0);
               
        CyDelay(speed);
    } 
    UART_1_PutString("door is open, waiting 10 sec\r\n");
    CyDelay(10000);
    UART_1_PutString("closing door\r\n");
    motor_close(); //We try to close the door again
}


void motor_stop()
{
    IN_1_Write(0);
    IN_2_Write(0);
    IN_3_Write(0);
    IN_4_Write(0);   
}



/* [] END OF FILE */
