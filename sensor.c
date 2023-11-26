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

// sensor.c
#include "sensor.h"
#include "project.h" // Include project specific dependencies
#include <stdio.h>
#include <math.h>

// Define calibration constants
static const double calibrationFactor = 446.0;
static const double offset = 527.0;
static const double weightThreshold = 0.500; // in grams

bool CheckWeight() {
    ADC_SAR_1_Start();
    ADC_SAR_1_StartConvert();

    if (ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT)) {
        uint16_t result = ADC_SAR_1_GetResult16();
        double weight = (result - offset) / calibrationFactor;
       
        
        
   
//        CyDelay(2000);
//        char debugStr[64];
//        sprintf(debugStr, "Raw ADC: %u, Weight: %lf", result, weight);
//        UART_1_PutString(debugStr);
//        UART_1_PutString("\r\n");
        //
        if ((weight) >= weightThreshold) {
            return true; // Weight is more than 500g
        }
    }

    return false; // Weight is less than 500g or conversion not complete
}




/* [] END OF FILE */
