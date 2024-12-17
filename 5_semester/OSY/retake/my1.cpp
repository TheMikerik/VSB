// **************************************************************************
//
//               Demo program for OSY labs
//
// Subject:      Operating systems
// Author:       Petr Olivka, petr.olivka@vsb.cz, 12/2023
// Organization: Department of Computer Science, FEECS,
//               VSB-Technical University of Ostrava, CZ
//
// File:         FreeRTOS TCP/IP Demo
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


#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "fsl_sysmpu.h"
#include <cstdio>
#include <unistd.h>
#include <ctime>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"

#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"

// Task priorities.
#define LOW_TASK_PRIORITY 		(configMAX_PRIORITIES - 2)
#define NORMAL_TASK_PRIORITY 	(configMAX_PRIORITIES - 1)
#define HIGH_TASK_PRIORITY 		(configMAX_PRIORITIES)

#define TASK_NAME_LED_PTA		"led_pta"
#define TASK_NAME_SOCKET_SRV	"socket_srv"
#define TASK_NAME_SOCKET_CLI	"socket_cli"







// TOTO PRIDAVAM JA
#define TASK_NAME_SET_ONOFF "set_onoff"
#define TASK_NAME_MONITOR_BUTTONS "monitor_buttons"
#define TASK_NAME_PRINT_BUTTONS "print_buttons"


xSocket_t l_sock_client;
//









#define SOCKET_SRV_TOUT			1000
#define SOCKET_SRV_BUF_SIZE		256
#define SOCKET_SRV_PORT			3333

#define SOCKET_CLI_PORT			3333

#define BUT_NUM 	    4
#define LED_PTA_NUM 	2
#define LED_PTC_NUM		8
#define LED_PTB_NUM		9

// pair of GPIO port and LED pin.
struct LED_Data
{
	uint32_t pin;
	GPIO_Type *gpio;
};

// all PTAx LEDs in array
LED_Data pta[ LED_PTA_NUM ] =
{
		{ LED_PTA1_PIN, LED_PTA1_GPIO },
		{ LED_PTA2_PIN, LED_PTA2_GPIO },
};

// all PTCx LEDs in array
LED_Data ptc[ LED_PTC_NUM ] =
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










struct CUSTOM_LED {
  bool state;
  uint32_t pin;
	GPIO_Type *gpio;
};

CUSTOM_LED ptc_bool[ LED_PTC_NUM ] =
{
		{ false, LED_PTC0_PIN, LED_PTC0_GPIO },
		{ false, LED_PTC1_PIN, LED_PTC1_GPIO },
		{ false, LED_PTC2_PIN, LED_PTC2_GPIO },
		{ false, LED_PTC3_PIN, LED_PTC3_GPIO },
		{ false, LED_PTC4_PIN, LED_PTC4_GPIO },
		{ false, LED_PTC5_PIN, LED_PTC5_GPIO },
		{ false, LED_PTC7_PIN, LED_PTC7_GPIO },
		{ false, LED_PTC8_PIN, LED_PTC8_GPIO },
};




struct CUSTOM_BUT {
  bool state;
  bool change;
  bool released;
  unsigned int pin;
	GPIO_Type *gpio;
};

CUSTOM_BUT but_bool[BUT_NUM] = {
    {false, false, false, SW_PTC9_PIN, SW_PTC9_GPIO},
		{false, false, false, SW_PTC10_PIN, SW_PTC10_GPIO},
		{false, false, false, SW_PTC11_PIN, SW_PTC11_GPIO},
		{false, false, false, SW_PTC12_PIN, SW_PTC12_GPIO}
};












// Random number generator for TCP/IP stack
BaseType_t xApplicationGetRandomNumber( uint32_t * tp_pul_number ) { return uxRand(); }


// Some task stack overflow
void vApplicationStackOverflowHook( xTaskHandle *tp_task_handle, signed portCHAR *tp_task_name )
{
	PRINTF( "STACK PROBLEM %s.\r\n", tp_task_name );
}


// This task blink alternatively both PTAx LEDs
void task_led_pta_blink( void *t_arg )
{
	uint32_t l_inx = 0;

    while ( 1 )
    {
    	// switch LED on
        GPIO_PinWrite( pta[ l_inx ].gpio, pta[ l_inx ].pin, 1 );
        vTaskDelay( 200 );
        // switch LED off
        GPIO_PinWrite( pta[ l_inx ].gpio, pta[ l_inx ].pin, 0 );
        // next LED
        l_inx++;
        l_inx %= LED_PTA_NUM;
    }
}


















// PRE SOCKET

struct valid_direction {
	bool fromLeft;
	bool validString;
};

int get_position(int8_t *str){
    int res = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
      if (str[i] >= '0' && str[i] <= '9') {
          res = str[i] - '0';
          break;
      }
  }

  return res;
}


valid_direction read_input_leds(int8_t* input_msg) {
	valid_direction vd_result;
	vd_result.fromLeft = false;
	vd_result.validString = false;

  char led_str_r[] = "LED R";
	char led_str_l[] = "LED L";
  int i = 0;

  while (led_str_r[i] != '\0') {
      if (input_msg[i] == '\0' || input_msg[i] != led_str_r[i]) {
          break;
      }
      i++;
  }
	if (led_str_r[i] == '\0') {
      vd_result.validString = true;
      vd_result.fromLeft = false;
      return vd_result;
  }

	i = 0;

	while (led_str_l[i] != '\0') {
      if (input_msg[i] == '\0' || input_msg[i] != led_str_l[i]) {
          return vd_result;
      }
      i++;
  }
	if (led_str_l[i] == '\0') {
      vd_result.validString = true;
      vd_result.fromLeft = true;
  }
  return vd_result;
}



void snake_left() {
	for (int i = 0; i < LED_PTC_NUM; i++) {
		ptc_bool[i].state = false;
	}

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < LED_PTC_NUM; j++) {
			ptc_bool[j].state = false;
		}
		for(int display = 0; display < 3; display++) {
			if (i - display >= 0 && i - display < LED_PTC_NUM) {
				ptc_bool[i - display].state = true;
			}
		}

		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

void snake_right() {
	for (int i = 0; i < LED_PTC_NUM; i++) {
		ptc_bool[i].state = false;
	}

	for (int i = LED_PTC_NUM - 1; i >= -2; i--) {
		for (int j = 0; j < LED_PTC_NUM; j++) {
			ptc_bool[j].state = false;
		}
		for (int display = 0; display < 3; display++) {
			if (i + display >= 0 && i + display < LED_PTC_NUM) {
				ptc_bool[i + display].state = true;
			}
		}

		vTaskDelay(pdMS_TO_TICKS(500));
	}
}



//


















// task socket server
void task_socket_srv( void *tp_arg )
{
	PRINTF( "Task socket server started.\r\n" );
	TickType_t l_receive_tout = 25000 / portTICK_PERIOD_MS;

	int l_port = ( int ) tp_arg;
	struct freertos_sockaddr l_srv_address;

	// set listening port
	l_srv_address.sin_port = FreeRTOS_htons( l_port );
	l_srv_address.sin_addr = FreeRTOS_inet_addr_quick( 0, 0, 0, 0 );

	xSocket_t l_sock_listen;
	xWinProperties_t l_win_props;
	struct freertos_sockaddr from;
	socklen_t fromSize = sizeof from;
	BaseType_t l_bind_result;
	int8_t l_rx_buf[ SOCKET_SRV_BUF_SIZE ]; /* Make sure the stack is large enough to hold these.  Turn on stack overflow checking during debug to be sure. */

	/* Create a socket. */
	l_sock_listen = FreeRTOS_socket( FREERTOS_AF_INET, FREERTOS_SOCK_STREAM, FREERTOS_IPPROTO_TCP );
	configASSERT( l_sock_listen != FREERTOS_INVALID_SOCKET );

	l_bind_result = FreeRTOS_bind( l_sock_listen, &l_srv_address, sizeof l_srv_address );
	configASSERT( l_bind_result == 0 );

	// Set a time out so a missing reply does not cause the task to block indefinitely.
	FreeRTOS_setsockopt( l_sock_listen, 0, FREERTOS_SO_RCVTIMEO, &l_receive_tout, sizeof( l_receive_tout ) );
	FreeRTOS_setsockopt( l_sock_listen, 0, FREERTOS_SO_SNDTIMEO, &l_receive_tout, sizeof( l_receive_tout ) );

	memset( &l_win_props, '\0', sizeof l_win_props );
	// Size in units of MSS
	l_win_props.lTxBufSize   = SOCKET_SRV_BUF_SIZE;
	l_win_props.lTxWinSize   = 2;
	l_win_props.lRxBufSize   = SOCKET_SRV_BUF_SIZE;
	l_win_props.lRxWinSize   = 2;

	FreeRTOS_setsockopt( l_sock_listen, 0, FREERTOS_SO_WIN_PROPERTIES, ( void * ) &l_win_props, sizeof( l_win_props ) );

	FreeRTOS_listen( l_sock_listen, 2 );

	PRINTF( "Socket servers started, listen port %u.\r\n", FreeRTOS_ntohs( l_srv_address.sin_port ) );
	// go!
	for( ;; )
	{
		uint32_t l_reply_count = 0;
		// wait for client
		do {
			l_sock_client = FreeRTOS_accept( l_sock_listen, &from, &fromSize );
			vTaskDelay( SOCKET_SRV_TOUT );
		} while ( l_sock_client == NULL );

		if ( l_sock_client == FREERTOS_INVALID_SOCKET )
		{
			PRINTF( "Invalid socket from ACCEPT!\r\n" );
			continue;
		}

		vTaskDelay( 100 );

		// Handle echo requests.
		for ( l_reply_count = 0; pdTRUE; l_reply_count++ )
		{
			BaseType_t l_len;

			// receive data
			l_len = FreeRTOS_recv(	l_sock_client, l_rx_buf, sizeof( l_rx_buf ), 0 );
			//
			if( l_len > 0 )
			{
				l_rx_buf[ l_len ] = 0;	// just for printing








      // TADY DOPLNUJU

        int position = get_position(l_rx_buf);
        PRINTF("%s %d\n", l_rx_buf, get_position(l_rx_buf));

				valid_direction vd = read_input_leds(l_rx_buf);

				if( vd.validString ) {
          // ptc_bool[position].state = !ptc_bool[position].state;
          // if (ptc_bool[position].state) {
          //     PRINTF("LED: %d ON\n", position);
          // } else {
          //     PRINTF("LED: %d OFF\n", position);
          // }
					if (vd.fromLeft) {
						for (int i = 0; i < LED_PTC_NUM; i++) {
							if ( i < position){
								ptc_bool[i].state = true;
							} else {
								ptc_bool[i].state = false;
							}
							PRINTF("%d leds from left\n", position);
						}
					}
					else if (!vd.fromLeft) {
						for (int i = LED_PTC_NUM; i > -1; i--) {
							ptc_bool[i].state = !ptc_bool[i].state;
							if ( i > (LED_PTC_NUM - position - 1) ){
								ptc_bool[i].state = true;
							} else {
								ptc_bool[i].state = false;
							}
							PRINTF("%d leds from right\n", position);
						}
					} else {
						printf("Invalid string\n");
					}

				}




      //












				l_len = FreeRTOS_send( l_sock_client, ( void * ) l_rx_buf, l_len, 0 );

				PRINTF( "Server forwarded %d bytes.\r\n", l_len );
			}
			if ( l_len < 0 )
			{
				// FreeRTOS_debug_printf( ( "FreeRTOS_recv: rc = %ld.\n", l_len ) );
				// Probably '-FREERTOS_ERRNO_ENOTCONN', see FreeRTOS_IP.h
				break;
			}
			if ( l_len == 0 )
			{
				PRINTF( "Recv timeout.\r\n" );
				//FreeRTOS_setsockopt( l_sock_listen, 0, FREERTOS_SO_RCVTIMEO, &l_receive_tout, sizeof( l_receive_tout ) );
			}
		}
		PRINTF( "Socket server replied %d times.\r\n", l_reply_count );

		// Pause for a short while to ensure the network is not too	congested.
		vTaskDelay( SOCKET_SRV_TOUT );

		// Close this socket before looping back to create another.
		FreeRTOS_closesocket( l_sock_client );
		l_sock_client = NULL;
	}
}

void task_socket_cli( void *tp_arg )
{
	PRINTF( "Task socket client started. \r\n" );

	vTaskDelay( 500 );

   	Socket_t l_sock_server = FreeRTOS_socket( FREERTOS_AF_INET, FREERTOS_SOCK_STREAM, FREERTOS_IPPROTO_TCP );
	struct freertos_sockaddr *lp_sever_addr = ( freertos_sockaddr * ) tp_arg;
	BaseType_t l_res = FreeRTOS_connect( l_sock_server, lp_sever_addr, sizeof( freertos_sockaddr ) );

	if ( l_res == 0 )
	{
		PRINTF( "Connect to server %d.\r\n", l_res );

		for ( int i = 0; i < 10; i++ )
		{
			l_res = FreeRTOS_send( l_sock_server, "Hello\n", 6, 0 );
			PRINTF( "send %d...\r\n", l_res );
			if ( l_res < 0 ) break;
			vTaskDelay( 500 );
		}
	}
	else
	{
		PRINTF( "Unable to connect server!\r\n" );
	}

	FreeRTOS_closesocket( l_sock_server );

	vTaskDelete( NULL );
}


// Callback from TCP stack - interface state changed
void vApplicationIPNetworkEventHook( eIPCallbackEvent_t t_network_event )
{
	static BaseType_t s_task_already_created = pdFALSE;
	static freertos_sockaddr s_server_addr;
	s_server_addr.sin_port = FreeRTOS_htons( SOCKET_CLI_PORT );
	s_server_addr.sin_addr = FreeRTOS_inet_addr_quick( 10, 0, 0, 1 );

    // Both eNetworkUp and eNetworkDown events can be processed here.
    if ( t_network_event == eNetworkUp )
    {
    	PRINTF( "Network interface UP.\r\n" );
        // Create the tasks that use the TCP/IP stack if they have not already been created.
        if ( s_task_already_created == pdFALSE )
        {
             // For convenience, tasks that use FreeRTOS+TCP can be created here
             // to ensure they are not created before the network is usable.
        	if ( xTaskCreate( task_socket_srv, TASK_NAME_SOCKET_SRV, configMINIMAL_STACK_SIZE + 1024,
        			( void * ) SOCKET_SRV_PORT, configMAX_PRIORITIES - 1, NULL ) != pdPASS )
        	{
        		PRINTF( "Unable to create task %s.\r\n", TASK_NAME_SOCKET_SRV );
        	}
        	// Create task for socket client
        	/*
        	if ( xTaskCreate( task_socket_cli, TASK_NAME_SOCKET_CLI, configMINIMAL_STACK_SIZE + 1024,
        			&s_server_addr, configMAX_PRIORITIES - 1, NULL ) != pdPASS )
        	{
        		PRINTF( "Unable to create task %s.\r\n", TASK_NAME_SOCKET_CLI );
        	}
        	 */
        	s_task_already_created = pdTRUE;
        }
    }
}









// DOPLNUJU FCE Z MAINU





void task_set_onoff( void *tp_arg  ){
  while(1) {
		for(int i = 0; i < LED_PTC_NUM; i++) {
			GPIO_PinWrite( ptc_bool[ i ].gpio, ptc_bool[ i ].pin, ptc_bool[i].state );

		}

		vTaskDelay( 5 );
	}
}


void task_monitor_buttons(void *tp_arg) {
  for (int i = 0; i < BUT_NUM; i++) {
    but_bool[i].change = false;
    but_bool[i].released = true;
    but_bool[i].state = false;
  }

  while (1) {
			for (int i = 0; i < BUT_NUM; i++) {
					bool state = GPIO_PinRead(but_bool[i].gpio, but_bool[i].pin);
					bool prev_state = but_bool[i].state;

					but_bool[i].state = (state == 0);

					if (but_bool[i].state != prev_state) {
							but_bool[i].change = true;
							but_bool[i].released = !but_bool[i].state;
					} else {
							but_bool[i].change = false;
					}


					if (but_bool[0].state && but_bool[0].change) {
						snake_left();
					}

					if (but_bool[3].state && but_bool[3].change) {
						snake_right();
					}
			}

    vTaskDelay(1);
    }
}

void task_print_buttons(void *tp_arg) {
	bool enter = false;
	char msg[64];

	while (true) {
		strcpy(msg, "BTN ");
		for (int i = 0; i < BUT_NUM; ++i) {
			sprintf(msg + strlen(msg), "%d", but_bool[i].state ? 1 : 0);
			if (!enter && but_bool[i].change) {
				enter = true;
			}
			but_bool[i].change = false;
		}
		strcat(msg, "\n");

		if (enter) {
			FreeRTOS_send(l_sock_client, (void *)msg, strlen(msg) + 1, 0);
			enter = false;
		}

		vTaskDelay(1);
	}
}





//














/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    SYSMPU_Enable( SYSMPU, false );

    PRINTF( "FreeRTOS+TCP started.\r\n" );

    // SET CORRECTLY MAC ADDRESS FOR USAGE IN LAB!
    //
    // Computer in lab use IP address 158.196.XXX.YYY.
    // Set MAC to 5A FE C0 DE XXX YYY+21
    // IP address will be configured from DHCP
    //
	uint8_t ucMAC[ ipMAC_ADDRESS_LENGTH_BYTES ] = { 0x5A, 0xFE, 0xC0, 0xDE, 142, 101 };

   	uint8_t ucIPAddress[ ipIP_ADDRESS_LENGTH_BYTES ] = { 10, 0, 0, 10 };
   	uint8_t ucIPMask[ ipIP_ADDRESS_LENGTH_BYTES ] = { 255, 255, 255, 0 };
   	uint8_t ucIPGW[ ipIP_ADDRESS_LENGTH_BYTES ] = { 10, 0, 0, 1 };

	FreeRTOS_IPInit( ucIPAddress,  ucIPMask,  ucIPGW,  NULL,  ucMAC );

	// Create tasks
	if ( xTaskCreate(
	    		task_led_pta_blink,
	    		TASK_NAME_LED_PTA,
				configMINIMAL_STACK_SIZE + 100,
				NULL,
				NORMAL_TASK_PRIORITY,
				NULL ) != pdPASS )
	    {
	        PRINTF( "Unable to create task '%s'.\r\n", TASK_NAME_LED_PTA );
	    }

  if ( xTaskCreate(
	    		task_set_onoff,
	    		TASK_NAME_SET_ONOFF,
				configMINIMAL_STACK_SIZE + 100,
				NULL,
				NORMAL_TASK_PRIORITY,
				NULL ) != pdPASS )
	    {
	        PRINTF( "Unable to create task '%s'.\r\n", TASK_NAME_SET_ONOFF );
	    }
  
  if ( xTaskCreate(
	    		task_monitor_buttons,
	    		TASK_NAME_MONITOR_BUTTONS,
				configMINIMAL_STACK_SIZE + 100,
				NULL,
				NORMAL_TASK_PRIORITY,
				NULL ) != pdPASS )
	    {
	        PRINTF( "Unable to create task '%s'.\r\n", TASK_NAME_MONITOR_BUTTONS );
	    }

  if ( xTaskCreate(
	    		task_print_buttons,
	    		TASK_NAME_PRINT_BUTTONS,
				configMINIMAL_STACK_SIZE + 100,
				NULL,
				NORMAL_TASK_PRIORITY,
				NULL ) != pdPASS )
	    {
	        PRINTF( "Unable to create task '%s'.\r\n", TASK_NAME_PRINT_BUTTONS );
	    }
		
	vTaskStartScheduler();

    while ( 1 );

    return 0 ;
}





