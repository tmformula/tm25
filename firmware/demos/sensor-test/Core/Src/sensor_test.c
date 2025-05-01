#include "adc.h"
#include "usart.h"
#include "sensor_test.h"
#include "can.h"

extern CAN_HandleTypeDef hcan1;

double battery_soc = 0;

int sensor_test(){

  uint16_t apps1 = 0;
  uint16_t apps2 = 0;
  uint16_t bse_rear = 0;

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

  // --- CAN INIT ---
  //HAL_CAN_Start(&hcan1);
  //HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

  CAN_FilterTypeDef filterConfig;
  filterConfig.FilterActivation = CAN_FILTER_ENABLE;
  filterConfig.FilterBank = 0;
  filterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  filterConfig.FilterIdHigh = 0x680 << 5;  // SoC ID (0x680)
  filterConfig.FilterIdLow = 0x0000;
  filterConfig.FilterMaskIdHigh = 0x7FF << 5;
  filterConfig.FilterMaskIdLow = 0x0000;
  filterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  filterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  filterConfig.SlaveStartFilterBank = 14;
  //HAL_CAN_ConfigFilter(&hcan1, &filterConfig);

  if (HAL_CAN_ConfigFilter(&hcan1, &filterConfig) != HAL_OK) {
      sprintf(msg, "CAN Filter Config Error\r\n");
      HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
  }

  if (HAL_CAN_Start(&hcan1) != HAL_OK) {
      sprintf(msg, "CAN Start Error\r\n");
      HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
  }

  if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
      sprintf(msg, "CAN Interrupt Enable Error\r\n");
      HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
  }



  while(1){
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 1);
    apps1 = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Start(&hadc2);
    HAL_ADC_PollForConversion(&hadc2, 1);
    apps2 = HAL_ADC_GetValue(&hadc2);
    HAL_ADC_Start(&hadc3);
	HAL_ADC_PollForConversion(&hadc3, 1);
	bse_rear = HAL_ADC_GetValue(&hadc3);
  
    sprintf(msg,
      "\033[2J\n\n--------  Dashboard --------\n\n"
      "ADC Value 1: %d\n"
      "ADC Value 2: %d\n"
      "BSE Rear Value: %d\n"
      "Battery SoC: % %f\n"
      "Current to Motor Controller (A): %f\n"
      "Steering Wheel Button 1: %d\n"
      "Steering Wheel Button 2: %d\n"
      "Steering Wheel Button 3: %d\n"
      "Steering Wheel Button 4: %d\n"
      "Vehicle Velocity <x,y,z>: <%d, %d, %d>\n"
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

// CAN RX callback — called when a new CAN frame arrives
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t rxData[8];
    char msg[512];

    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxHeader, rxData) != HAL_OK) {
        sprintf(msg, "CAN RX Error\r\n");
        HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
        return;
    }

    if (rxHeader.StdId == 0x680) {
        uuint8_t raw_soc = rxData[6];
        battery_soc = raw_soc / 2;
    }
}

