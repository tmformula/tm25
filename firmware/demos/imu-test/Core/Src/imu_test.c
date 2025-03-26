#include "adc.h"
#include "usart.h"
#include "imu_test.h"


int imu_test(){

  uint16_t adcValue1 = 0;
  uint16_t adcValue2 = 0;
  char msg[512];
  char msg_in[16] = {0};
  char indent[] = "          ";
  sprintf(msg, "%s\n--------------\nAuthor: Malcolm Boyes\nCompiler Version: %s\nCompiled On: %s at %s\n--------------\n", "logo", __VERSION__, __DATE__, __TIME__);
  HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);






  while(1){
    // HAL_ADC_Start(&hadc1);
    // HAL_ADC_PollForConversion(&hadc1, 1);
    // adcValue1 = HAL_ADC_GetValue(&hadc1);
    // HAL_ADC_Start(&hadc2);
    // HAL_ADC_PollForConversion(&hadc2, 1);
    // adcValue2 = HAL_ADC_GetValue(&hadc2);
  
    // sprintf(msg,
    //   "\033[2J\n\n%s--------  Dashboard --------\n\n"
    //   "%sADC Value 1: %d\n"
    //   "%sADC Value 2: %d\n"
    //   "\n\n%s----------------------------\n\n"
    // , indent, indent, adcValue1, indent, adcValue2, indent);
    // HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);

    HAL_UART_Receive(&huart1, msg_in, 16, HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart2, (uint8_t *) msg_in, 16, HAL_MAX_DELAY);
    
    //HAL_Delay(20);
  }

  return 0;
}