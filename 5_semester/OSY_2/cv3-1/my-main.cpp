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
#define TASK_NAME_LED_PTA			"led_pta"
#define TASK_NAME_LED_SNAKE_L	"led_snake_l"
#define TASK_NAME_LED_SNAKE_R	"led_snake_r"
#define TASK_NAME_WATCH_BRIGHTNESS_PTC "watch_ptc"
#define TASK_NAME_WATCH_BRIGHTNESS_PTA "watch_pta"

#define LED_PTA_NUM 	2
#define LED_PTC_NUM		8
#define LED_PTB_NUM		9

#define PWM_PERIOD_MS    1
#define PWM_DUTY_100     100 
#define PWM_DUTY_5       5
#define PWM_GRANULARITY  100 

// pair of GPIO port and LED pin.
struct LED_Data
{
	uint32_t pin;
	GPIO_Type *gpio;
  float brightness;
};

struct Train{
	bool arrived;
	bool goRight;
	bool moving;
};

bool g_canGo = false;

Train g_train_right { false, false, false};
Train g_train_left { false, true, false};

// all PTAx LEDs in array
LED_Data g_pta[ LED_PTA_NUM ] =
{
		{ LED_PTA1_PIN, LED_PTA1_GPIO, 0.0f },
		{ LED_PTA2_PIN, LED_PTA2_GPIO, 0.0f },
};

// all PTCx LEDs in array
LED_Data g_ptc[ LED_PTC_NUM ] =
{
		{ LED_PTC0_PIN, LED_PTC0_GPIO, 0.0f },
		{ LED_PTC1_PIN, LED_PTC1_GPIO, 0.0f },
		{ LED_PTC2_PIN, LED_PTC2_GPIO, 0.0f },
		{ LED_PTC3_PIN, LED_PTC3_GPIO, 0.0f },
		{ LED_PTC4_PIN, LED_PTC4_GPIO, 0.0f },
		{ LED_PTC5_PIN, LED_PTC5_GPIO, 0.0f },
		{ LED_PTC7_PIN, LED_PTC7_GPIO, 0.0f },
		{ LED_PTC8_PIN, LED_PTC8_GPIO, 0.0f },
};



void task_watch_brightness_ptc(void *t_args)
{
    const int pwm_resolution = 20;
    int pwm_step = 0;
    
    while (1)
    {
        for (int led_index = 0; led_index < LED_PTC_NUM; led_index++)
        {
            int on_cycles = (int)(g_ptc[led_index].brightness * pwm_resolution);
            int led_state = (on_cycles > pwm_step) && (g_ptc[led_index].brightness > 0.0f);
            
            GPIO_PinWrite(g_ptc[led_index].gpio, g_ptc[led_index].pin, led_state);
        }
        
        pwm_step = (pwm_step + 1) % pwm_resolution;
        vTaskDelay(1);
    }
}

void task_watch_brightness_pta(void *t_args)
{
    const int pwm_resolution = 20;
    int pwm_step = 0;
    
    while (1)
    {
        for (int led_index = 0; led_index < LED_PTA_NUM; led_index++)
        {
            int on_cycles = (int)(g_pta[led_index].brightness * pwm_resolution);
            int led_state = (on_cycles > pwm_step) && (g_pta[led_index].brightness > 0.0f);
            
            GPIO_PinWrite(g_pta[led_index].gpio, g_pta[led_index].pin, led_state);
        }
        
        pwm_step = (pwm_step + 1) % pwm_resolution;
        vTaskDelay(1);
    }
}

// This task blink alternatively both PTAx LEDs
void task_led_pta_blink( void *t_arg )
{
    vTaskSuspend( 0 );
    uint32_t i = 0;

    while ( 1 )
    {
        g_pta[ i ].brightness = 1.0f;
        vTaskDelay( 200 );
        g_pta[ i ].brightness = 0.0f;

        i++;
        
        if ( !g_canGo ) { 
            if ( i == LED_PTA_NUM ) {
								i = 0;
                vTaskSuspend( NULL );
            }
        } else {
            i %= LED_PTA_NUM;
        }
    }
}

// This task is snake animation from left side on red LEDs
void task_snake_left( void *t_arg )
{
  while ( 1 )
  {
    vTaskSuspend( 0 );

    g_train_left.moving = true;

    if (g_train_left.arrived){
      for ( int i = 0; i < LED_PTC_NUM; i++ )
      {
            g_ptc[ i ].brightness = 0.0f;
            vTaskDelay( 200 );
      }
      g_train_left.arrived = false;
    } else {
      for ( int i = 0; i < LED_PTC_NUM; i++ )
      {
            g_ptc[ i ].brightness = 1.0f;
            if (i > 0) {
              g_ptc[ i - 1 ].brightness = 0.1f;
            }
            vTaskDelay( 200 );
      }
      g_train_left.arrived = true;
    }

    g_train_left.moving = false;
  }
}

// This task is snake animation from right side on red LEDs
void task_snake_right( void *t_arg )
{
  while ( 1 )
  {
    vTaskSuspend( 0 );

    g_train_right.moving = true;

    if (g_train_right.arrived){
      for ( int i = LED_PTC_NUM - 1; i >= 0; i-- )
      {
        g_ptc[ i ].brightness = 0.0f;
        vTaskDelay( 200 );
      }
      g_train_right.arrived = false;
    } else {
      for ( int i = LED_PTC_NUM - 1; i >= 0; i-- )
      {
        g_ptc[ i ].brightness = 1.0f;
        if (i < LED_PTC_NUM - 1) {
          g_ptc[ i + 1 ].brightness = 0.1f;
        }
        vTaskDelay( 200 );
      }
      g_train_right.arrived = true;
    }

    g_train_right.moving = false;
  }
}

// This task monitors switches and control others led_* tasks
void task_switches( void *t_arg )
{
	// Get task handles for task names
	TaskHandle_t l_handle_led_pta = xTaskGetHandle( TASK_NAME_LED_PTA );
	TaskHandle_t l_handle_led_snake_l = xTaskGetHandle( TASK_NAME_LED_SNAKE_L );
	TaskHandle_t l_handle_led_snake_r = xTaskGetHandle( TASK_NAME_LED_SNAKE_R );

	while ( 1 )
	{
		// test PTC9 switch
		if ( GPIO_PinRead( SW_PTC9_GPIO, SW_PTC9_PIN ) == 0 )
		{
			if ( !g_train_left.moving && !g_train_right.moving )
      {
        if (g_canGo){
					g_canGo = false; 
					if ( l_handle_led_pta )
						vTaskResume( l_handle_led_pta );
				}
      }
		}

		// test PTC10 switch
		if ( GPIO_PinRead( SW_PTC10_GPIO, SW_PTC10_PIN ) == 0 )
		{
			if ( !g_canGo ) {
				g_canGo = true;
				if ( l_handle_led_pta )
					vTaskResume( l_handle_led_pta );
			}
		}

		// test PTC11 switch
		if ( GPIO_PinRead( SW_PTC11_GPIO, SW_PTC11_PIN ) == 0 )
		{
			if ( g_canGo && l_handle_led_snake_l && !g_train_right.moving && !g_train_right.arrived)
				vTaskResume( l_handle_led_snake_l );
		}

		// test PTC12 switch
		if ( GPIO_PinRead( SW_PTC12_GPIO, SW_PTC12_PIN ) == 0 )
		{
			if ( g_canGo && l_handle_led_snake_r && !g_train_left.moving && !g_train_left.arrived )
				vTaskResume( l_handle_led_snake_r );
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

    // Create tasks
    if ( xTaskCreate(
    		task_led_pta_blink,
    		TASK_NAME_LED_PTA,
			configMINIMAL_STACK_SIZE + 100,
			NULL,
			NORMAL_TASK_PRIORITY,
			NULL ) != pdPASS )
    {
        PRINTF( "Unable to create task '%s'!\r\n", TASK_NAME_LED_PTA );
    }

    if ( xTaskCreate( task_snake_left, TASK_NAME_LED_SNAKE_L, configMINIMAL_STACK_SIZE + 100, NULL, NORMAL_TASK_PRIORITY, NULL ) != pdPASS )
    {
        PRINTF( "Unable to create task '%s'!\r\n", TASK_NAME_LED_SNAKE_L );
    }

    if ( xTaskCreate( task_snake_right, TASK_NAME_LED_SNAKE_R, configMINIMAL_STACK_SIZE + 100, NULL, NORMAL_TASK_PRIORITY, NULL ) != pdPASS)
    {
        PRINTF( "Unable to create task '%s'!\r\n", TASK_NAME_LED_SNAKE_R );
    }

    if ( xTaskCreate( task_switches, TASK_NAME_SWITCHES, configMINIMAL_STACK_SIZE + 100, NULL, NORMAL_TASK_PRIORITY, NULL) != pdPASS )
    {
        PRINTF( "Unable to create task '%s'!\r\n", TASK_NAME_SWITCHES );
    }
    if ( xTaskCreate( task_watch_brightness_ptc, TASK_NAME_WATCH_BRIGHTNESS_PTC, configMINIMAL_STACK_SIZE + 100, NULL, NORMAL_TASK_PRIORITY, NULL) != pdPASS )
    {
        PRINTF( "Unable to create task '%s'!\r\n", TASK_NAME_WATCH_BRIGHTNESS_PTC );
    }
    if ( xTaskCreate( task_watch_brightness_pta, TASK_NAME_WATCH_BRIGHTNESS_PTA, configMINIMAL_STACK_SIZE + 100, NULL, NORMAL_TASK_PRIORITY, NULL) != pdPASS )
    {
        PRINTF( "Unable to create task '%s'!\r\n", TASK_NAME_WATCH_BRIGHTNESS_PTA );
    }

    vTaskStartScheduler();

    while ( 1 );

    return 0 ;
}

