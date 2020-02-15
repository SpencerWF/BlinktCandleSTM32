/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : blinkt.h
  * @brief          : Header for blinkt.c file.
  *                   This file contains definitions for blinkt functions.
  *****************************************************************************/
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BLINKT_H
#define __BLINKT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/

/* USER CODE BEGIN EFP */
void set_brightness_blinkt(uint8_t brightness);
void clear_blinkt();
void set_pixel_blinkt(uint8_t led, uint8_t r, uint8_t g, uint8_t b);
void set_pixel_brightness_blinkt(uint8_t led, uint8_t brightness);
void set_pixel_uint32_blinkt(uint8_t led, uint32_t color);
uint32_t rgbb_blinkt(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness);
uint32_t rgb_blinkt(uint8_t r, uint8_t g, uint8_t b);
void write_byte_blinkt(uint8_t byte);
void show_blinkt();
void set_all_blinkt();
void candle_brightness_blinkt();
void candle_color_shift();
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#endif /* __BLINKT_H */

/***************************************************************END OF FILE****/
