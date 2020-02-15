/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : blinkt.c
  * @brief          : Blinkt function definitons
  *****************************************************************************/

/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "blinkt.h"
// #include "main.h"
#define APA_SOF 0b11100000

#define RED_MAX 255
#define RED_MIN 220
#define GREEN_MAX 200
#define GREEN_MIN 30
#define BLUE_MAX 12
#define BLUE_MIN 0

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t spi_data;
extern SPI_HandleTypeDef hspi1;
/* USER CODE END PV */

/* Private function defines -----------------------------------------------*/
/* USER CODE BEGIN PFP */
#define DEFAULT_BRIGHTNESS 30
#define NUM_LEDS 8

// #define MOSI 23
// #define SCLK 24

#ifdef TEST
volatile int running = 0;
#endif

int x;

uint32_t leds[NUM_LEDS] = {};

// #ifdef TEST
// void sigint_handler(int dummy){
// 	running = 0;
// 	return;
// }
// #endif

void clear_blinkt(){
	for(x = 0; x < NUM_LEDS; x++){
		leds[x] = DEFAULT_BRIGHTNESS;
	}	
}

void set_pixel_blinkt(uint8_t led, uint8_t r, uint8_t g, uint8_t b){
	if(led >= NUM_LEDS) return;

	leds[led] = rgbb_blinkt(r,g,b,leds[led] & 0b11111);
}

void set_pixel_brightness_blinkt(uint8_t led, uint8_t brightness){
	if(led >= NUM_LEDS) return;
	
	leds[led] = (leds[led] & 0xFFFFFF00) | (brightness & 0b11111);
}

void set_pixel_uint32_blinkt(uint8_t led, uint32_t color){
	if(led >= NUM_LEDS) return;

	leds[led] = color;
}

uint32_t rgbb_blinkt(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness){
	uint32_t result = 0;
	result = (brightness & 0b11111);
	result |= ((uint32_t)r << 24);
	result |= ((uint32_t)g << 16);
	result |= ((uint16_t)b << 8);
	return result;
}

uint32_t rgb_blinkt(uint8_t r, uint8_t g, uint8_t b){
	return rgbb(r, g, b, DEFAULT_BRIGHTNESS);
}

void write_byte_blinkt(uint8_t byte){
	uint8_t send_data[1];

  send_data[0] = byte;

  HAL_SPI_Transmit(&hspi1, send_data, 1, 10);
  // Use the below 6 lines instead of the above 3, if you want to use any GPIO pins for controlling the blinkt module.
  // Currently this function uses the SPI functionality. 

  // for(int n = 0; n < 8; n++){
  //   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, (byte & (1 << (7-n))) > 0);
  //   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
  //   HAL_Delay(1);
  //   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
  // }
}

void show_blinkt(void){
	write_byte_blinkt(0);
	write_byte_blinkt(0);
	write_byte_blinkt(0);
	write_byte_blinkt(0);
	for(x = 0; x < NUM_LEDS; x++){
		write_byte_blinkt(APA_SOF | (leds[x] & 0b11111));
		write_byte_blinkt((leds[x] >> 8 ) & 0xFF);
		write_byte_blinkt((leds[x] >> 16) & 0xFF);
		write_byte_blinkt((leds[x] >> 24) & 0xFF);
	}
	write_byte_blinkt(0xff);
	write_byte_blinkt(0xff);
	write_byte_blinkt(0xff);
	write_byte_blinkt(0xff);
}

/* Candle Simulation Functions */
void candle_brightness_blinkt() {
  set_pixel_brightness_blinkt(0,1);
  set_pixel_brightness_blinkt(1,2);
  set_pixel_brightness_blinkt(2,3);
  set_pixel_brightness_blinkt(3,4);
  set_pixel_brightness_blinkt(4,5);
  set_pixel_brightness_blinkt(5,6);
  set_pixel_brightness_blinkt(6,7);
  set_pixel_brightness_blinkt(7,6);
}

void candle_color_shift() {
  uint8_t r,g,b,c_rng[3];
  uint32_t rng;
  for(int i=0; i<NUM_LEDS-1; i++){
    r = ((uint8_t)((leds[i+1] >> 24) & 0b11111111));
    g = ((uint8_t)((leds[i+1] >> 16) & 0b11111111));
    b = ((uint8_t)((leds[i+1] >> 8) & 0b11111111));
    set_pixel_blinkt(i,r,g,b);
  }
  rng = HAL_GetTick();
  rng = (uint8_t)(rng & 0b11111111);
  r += (rng >> 4)-7;
  g += (rng >> 5)-5;
  b += (rng >> 6)-2;

  // for(int i=0; i<3; i++) {
  //   if(c_rng[i] <= 0) {
  //     c_rng[i]-=1
  //   }
  // }

  // r = rng & 0b11111111;
  // if(r < 126) {
  //   r+=126;
  // }

  // g = rng & 0b01111111;

  // b = rng & 0b00001111;

  if(r > RED_MAX){
    r=RED_MAX;
  }
  else if (r < RED_MIN)
  {
    r=RED_MIN;
  }
  if(g > GREEN_MAX){
    g=GREEN_MAX;
  }
  else if (g < GREEN_MIN)
  {
    g=GREEN_MIN;
  }
  if(b > BLUE_MAX){
    b=BLUE_MAX;
  }
  else if (b < BLUE_MIN){
    b=BLUE_MIN;
  }

  set_pixel_blinkt(NUM_LEDS-1,r,g,b);
}

/* End Candle Simulation Functions */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */


/***************************************************************END OF FILE****/
