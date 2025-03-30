#include "adc.h"
#include "usart.h"
#include "sensor_test.h"

int sensor_test(){

  uint16_t apps1 = 0;
  uint16_t apps2 = 0;
  uint16_t bse_rear = 0;
  double battery_soc = 0;
  double current_to_motor_controller_A = 0;
  int steering_wheel_button_1 = 0;
  int steering_wheel_button_2 = 0;
  int steering_wheel_button_3 = 0;
  int steering_wheel_button_4 = 0;
  int velx = 0;
  int vely = 0;
  int velz = 0;


  char msg[512];
  
  sprintf(msg, "%s\n--------------\nAuthor: Malcolm Boyes\nCompiler Version: %s\nCompiled On: %s at %s\n--------------\n", "logo", __VERSION__, __DATE__, __TIME__);
  HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);

  HAL_Delay(2000);

  while(1){
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 1);
    apps1 = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Start(&hadc2);
    HAL_ADC_PollForConversion(&hadc2, 1);
    apps2 = HAL_ADC_GetValue(&hadc2);
  
    sprintf(msg,
      "\033[2J\n\n--------  Dashboard --------\n\n"
      "ADC Value 1: %d\n"
      "ADC Value 2: %d\n"
      "BSE Rear Value: %d\n"
      "Battery SoC: %f\n"
      "Current to Motor Controller (A): %f\n"
      "Steering Wheel Button 1: %d\n"
      "Steering Wheel Button 2: %d\n"
      "Steering Wheel Button 3: %d\n"
      "Steering Wheel Button 4: %d\n"
      "Vehicle Velocity <x,y,z>: <%f, %f, %f>\n"
      "\n\n----------------------------\n\n"
    , apps1, apps2, bse_rear, battery_soc, current_to_motor_controller_A, steering_wheel_button_1, steering_wheel_button_2, steering_wheel_button_3, steering_wheel_button_4, velx, vely, velz
    );
    HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);

    sprintf(msg, "\033[;F");
    HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), HAL_MAX_DELAY);
    
    HAL_Delay(100);
  }

  return 0;
}