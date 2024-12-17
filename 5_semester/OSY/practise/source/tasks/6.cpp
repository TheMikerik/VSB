#define PWD 25
int change = 0;

// This task blink alternatively both PTAx LEDs
void task_led_pta_blink( void *t_arg )
{
	uint32_t l_inx = 0;
	
	int ontime = PWD - change;
	int offtime = PWD - ontime;

    while ( 1 )
    {
			
    	// switch LED on
        GPIO_PinWrite( g_led_pta[ l_inx ].m_led_gpio, g_led_pta[ l_inx ].m_led_pin, 1 );
        vTaskDelay( ontime );
        // switch LED off
        GPIO_PinWrite( g_led_pta[ l_inx ].m_led_gpio, g_led_pta[ l_inx ].m_led_pin, 0 );
        // next LED
				vTaskDelay( offtime );

        l_inx++;
        l_inx %= LED_PTA_NUM;
    }
}