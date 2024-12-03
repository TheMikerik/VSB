// **************************************************************************
//
//               Demo program for OSY labs
//
// Subject:      Operating systems
// Author:       Petr Olivka, petr.olivka@vsb.cz, 02/2022
// Organization: Department of Computer Science, FEECS,
//               VSB-Technical University of Ostrava, CZ
//
// File:         Task control demo program.
//
// **************************************************************************
//
// All mapped LEDs and switches and their PINs and GPIOs:
// See schema in APPS syllabus.
//
// Switches:
// Name		PIN				GPIO
// PTC9		SW_PTC9_PIN		SW_PTC9_GPIO
// PTC10	SW_PTC10_PIN	SW_PTC10_GPIO
// PTC11	SW_PTC11_PIN	SW_PTC11_GPIO
// PTC12	SW_PTC12_PIN	SW_PTC12_GPIO
//
// LEDs:
// Name		PIN				GPIO
// PTA1		LED_PTA1_PIN   LED_PTA1_GPIO
// PTA2		LED_PTA2_PIN   LED_PTA2_GPIO
//
// PTC0		LED_PTC0_PIN   LED_PTC0_GPIO
// PTC1		LED_PTC1_PIN   LED_PTC1_GPIO
// PTC2		LED_PTC2_PIN   LED_PTC2_GPIO
// PTC3		LED_PTC3_PIN   LED_PTC3_GPIO
// PTC4		LED_PTC4_PIN   LED_PTC4_GPIO
// PTC5		LED_PTC5_PIN   LED_PTC5_GPIO
// PTC7		LED_PTC7_PIN   LED_PTC7_GPIO
// PTC8		LED_PTC8_PIN   LED_PTC8_GPIO
//
// PTB2		LED_PTB2_PIN   LED_PTB2_GPIO
// PTB3		LED_PTB3_PIN   LED_PTB3_GPIO
// PTB9		LED_PTB9_PIN   LED_PTB9_GPIO
// PTB10	LED_PTB10_PIN  LED_PTB10_GPIO
// PTB11	LED_PTB11_PIN  LED_PTB11_GPIO
// PTB18	LED_PTB18_PIN  LED_PTB18_GPIO
// PTB19	LED_PTB19_PIN  LED_PTB19_GPIO
// PTB20	LED_PTB20_PIN  LED_PTB20_GPIO
// PTB23	LED_PTB23_PIN  LED_PTB23_GPIO


// FreeRTOS kernel includes.
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

// System includes.
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"

// Task priorities.
#define LOW_TASK_PRIORITY 		(configMAX_PRIORITIES - 2)
#define NORMAL_TASK_PRIORITY 	(configMAX_PRIORITIES - 1)
#define HIGH_TASK_PRIORITY 		(configMAX_PRIORITIES)

#define TASK_NAME_SWITCHES		"switches"
#define TASK_NAME_LED_PTA		"led_pta"
#define TASK_NAME_LED_SNAKE_L	"led_snake_l"
#define TASK_NAME_LED_SNAKE_R	"led_snake_r"


#define TASK_NAME_HANDLE_LEFT_LED "handle_left_led"
#define TASK_NAME_HANDLE_RIGHT_LED "handle_right_led"


#define TASK_NAME_FOUR_LEDS "four_leds"
#define TASK_NAME_CLICK_CLICK "click_click"
#define TASK_NAME_DOUBLE_CLICK "double_click"

#define LED_PTA_NUM 	2
#define LED_PTC_NUM		8
#define LED_PTB_NUM		9

#define PWM_PERIOD 25

// pair of GPIO port and LED pin.
struct LED_Data
{
	uint32_t m_led_pin;
	GPIO_Type *m_led_gpio;
};

// all PTAx LEDs in array
LED_Data g_led_pta[ LED_PTA_NUM ] =
{
		{ LED_PTA1_PIN, LED_PTA1_GPIO },
		{ LED_PTA2_PIN, LED_PTA2_GPIO },
};

// all PTCx LEDs in array
LED_Data g_led_ptc[ LED_PTC_NUM ] =
{
		{ LED_PTC0_PIN, LED_PTC0_GPIO },
		{ LED_PTC1_PIN, LED_PTC1_GPIO },
		{ LED_PTC2_PIN, LED_PTC2_GPIO },
		{ LED_PTC3_PIN, LED_PTC3_GPIO },
		{ LED_PTC4_PIN, LED_PTC4_GPIO },
		{ LED_PTC5_PIN, LED_PTC5_GPIO },
		{ LED_PTC7_PIN, LED_PTC7_GPIO },
		{ LED_PTC8_PIN, LED_PTC8_GPIO },
};

enum SNAKE_STATE {
	SNAKE_STATE_UNKNOWN,
	SNAKE_STATE_LEFT,
	SNAKE_STATE_RIGHT
};
enum LEDS_DIR {
	LEDS_DIR_RIGHT,
	LEDS_DIR_LEFT
};
SNAKE_STATE g_in_state = SNAKE_STATE_UNKNOWN;
uint8_t g_should_bounce = false;
uint8_t g_force_continue = false;

uint8_t g_led_val = 0;

uint8_t four_leds_on = false;
uint8_t click_click_on = false;
uint8_t double_on = false;


void task_handle_double_click(void *_arg) {
	while(1) {
		if(double_on) {
			GPIO_PinWrite( g_led_pta[ 1 ].m_led_gpio, g_led_pta[ 1 ].m_led_pin, 1 );
		} else {
			GPIO_PinWrite( g_led_pta[ 1 ].m_led_gpio, g_led_pta[ 1 ].m_led_pin, 0 );
		}
		vTaskSuspend( 0 );
	}
}

// This task monitors switches and control others led_* tasks
void task_switches( void *t_arg )
{
#define CHANGE_LEVEL 1


	TaskHandle_t l_handle_four_leds_l = xTaskGetHandle( TASK_NAME_FOUR_LEDS );
	TaskHandle_t l_handle_click_click_l = xTaskGetHandle( TASK_NAME_CLICK_CLICK );
	TaskHandle_t l_handle_double_click_l = xTaskGetHandle( TASK_NAME_DOUBLE_CLICK );

	uint16_t delay_me = 0;
	uint8_t was_on_down = false;
	uint8_t was_on_up = false;
	uint8_t was_on_double = false;

	uint16_t double_timeout = 0;
	while(1) {

		if ( GPIO_PinRead( SW_PTC9_GPIO, SW_PTC9_PIN ) == 0 && delay_me > 2000 )
		{
			delay_me = 0;
			four_leds_on = four_leds_on ? false : true;
			vTaskResume( l_handle_four_leds_l );
		} else if (GPIO_PinRead( SW_PTC9_GPIO, SW_PTC9_PIN ) != 0) {
			delay_me = 0;
		}
		delay_me++;




		if ( GPIO_PinRead( SW_PTC10_GPIO, SW_PTC10_PIN ) == 1 )
		{
			was_on_down = true;
		}

		if ( GPIO_PinRead( SW_PTC10_GPIO, SW_PTC10_PIN ) == 0 && was_on_down )
		{
			was_on_down = false;
			click_click_on = click_click_on ? false : true;
			vTaskResume( l_handle_click_click_l );
		}

		if ( GPIO_PinRead( SW_PTC11_GPIO, SW_PTC11_PIN ) == 0 )
		{
			was_on_up = true;
		}

		if ( GPIO_PinRead( SW_PTC11_GPIO, SW_PTC11_PIN ) == 1 && was_on_up )
		{
			was_on_up = false;
			click_click_on = click_click_on ? false : true;
			vTaskResume( l_handle_click_click_l );
		}



		if ( GPIO_PinRead( SW_PTC12_GPIO, SW_PTC12_PIN ) == 0 )
		{
			if(double_timeout == 0 && was_on_double) {
				double_timeout++;
				was_on_double = false;
			}
			if(double_timeout < 5000 && was_on_double) {
				double_on = double_on ? false : true;
				double_timeout = 0;
				vTaskResume( l_handle_double_click_l );
			}
			was_on_double = false;
		}
		if ( GPIO_PinRead( SW_PTC12_GPIO, SW_PTC12_PIN ) == 1 )
		{
			was_on_double = true;
		}
		if(double_timeout > 0) {
			double_timeout++;
			if(double_timeout >= 5000) {
				double_timeout = 0;
			}
		}

		vTaskDelay( 1 );
	}

}

// Start application
int main(void) {

    // Init board hardware.
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();

    PRINTF( "FreeRTOS task demo program.\r\n" );
    PRINTF( "Switches PTC9 and PTC10 will stop and run PTAx LEDs blinking.\r\n" );
    PRINTF( "Switches PTC11 and PTC12 will start snake on red LEDS from the left and right side.\r\n");

    if ( xTaskCreate( task_handle_four_leds, TASK_NAME_FOUR_LEDS, configMINIMAL_STACK_SIZE + 100, NULL, NORMAL_TASK_PRIORITY, NULL ) != pdPASS )
	{
		PRINTF( "Unable to create task '%s'!\r\n", TASK_NAME_FOUR_LEDS );
	}

    if ( xTaskCreate( task_handle_click_click, TASK_NAME_CLICK_CLICK, configMINIMAL_STACK_SIZE + 100, NULL, NORMAL_TASK_PRIORITY, NULL ) != pdPASS )
	{
		PRINTF( "Unable to create task '%s'!\r\n", TASK_NAME_CLICK_CLICK );
	}

    if ( xTaskCreate( task_handle_double_click, TASK_NAME_DOUBLE_CLICK, configMINIMAL_STACK_SIZE + 100, NULL, NORMAL_TASK_PRIORITY, NULL ) != pdPASS )
	{
		PRINTF( "Unable to create task '%s'!\r\n", TASK_NAME_DOUBLE_CLICK );
	}

    if ( xTaskCreate( task_switches, TASK_NAME_SWITCHES, configMINIMAL_STACK_SIZE + 100, NULL, NORMAL_TASK_PRIORITY, NULL) != pdPASS )
    {
        PRINTF( "Unable to create task '%s'!\r\n", TASK_NAME_SWITCHES );
    }

    vTaskStartScheduler();

    while ( 1 );

    return 0 ;
}