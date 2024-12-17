#define MAX_BRIGHTNESS 256
#define BRIGHTNESS_STEP 16

// Global variables to store brightness of LEDs
uint8_t brightnessPta1 = MAX_BRIGHTNESS; // Max brightness for left LED
uint8_t brightnessPta2 = 0;              // Min brightness for right LED

void SetLEDBrightness(uint32_t pin, uint8_t brightness) {
    // Simulate brightness control by varying on/off state based on the brightness level
    for (uint8_t i = 0; i < MAX_BRIGHTNESS; i++) {
        GPIO_PinWrite(pin, (i < brightness) ? 1 : 0);
        vTaskDelay(1); // Delay to create the effect of brightness
    }
}

// This task adjusts brightness of PTAx LEDs using simple time division
void task_led_pta_brightness(void *t_arg) {
    while (1) {
        SetLEDBrightness(LED_PTA1_PIN, brightnessPta1);
        SetLEDBrightness(LED_PTA2_PIN, brightnessPta2);
        vTaskDelay(200);
    }
}

// Modified task to handle new buttons
void task_switches(void *t_arg) {
    TaskHandle_t l_handle_led_bright = xTaskGetHandle(TASK_NAME_LED_PTA);

    while (1) {
        // test PTC9 switch - increase left LED brightness
        if (GPIO_PinRead(SW_PTC9_PIN) == 0) {
            brightnessPta1 = (brightnessPta1 + BRIGHTNESS_STEP) % (MAX_BRIGHTNESS + 1);
            brightnessPta2 = MAX_BRIGHTNESS - brightnessPta1;
            vTaskResume(l_handle_led_bright);
        }

        // test PTC10 switch - decrease left LED brightness
        if (GPIO_PinRead(SW_PTC10_PIN) == 0) {
            brightnessPta1 = (brightnessPta1 - BRIGHTNESS_STEP + (MAX_BRIGHTNESS + 1)) % (MAX_BRIGHTNESS + 1);
            brightnessPta2 = MAX_BRIGHTNESS - brightnessPta1;
            vTaskResume(l_handle_led_bright);
        }

        // test PTC11 switch to suspend LED task
        if (GPIO_PinRead(SW_PTC11_PIN) == 0) {
            if (l_handle_led_bright) vTaskSuspend(l_handle_led_bright);
        }

        // test PTC12 switch to resume LED task
        if (GPIO_PinRead(SW_PTC12_PIN) == 0) {
            if (l_handle_led_bright) vTaskResume(l_handle_led_bright);
        }

        vTaskDelay(1);
    }
}

int main(void) {
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();

    PRINTF("FreeRTOS task demo program.\r\n");

    if (xTaskCreate(task_led_pta_brightness, TASK_NAME_LED_PTA, configMINIMAL_STACK_SIZE + 100, NULL, NORMAL_TASK_PRIORITY, NULL) != pdPASS) {
        PRINTF("Unable to create task '%s'!\r\n", TASK_NAME_LED_PTA);
    }

    if (xTaskCreate(task_snake_left, TASK_NAME_LED_SNAKE_L, configMINIMAL_STACK_SIZE + 100, NULL, NORMAL_TASK_PRIORITY, NULL) != pdPASS) {
        PRINTF("Unable to create task '%s'!\r\n", TASK_NAME_LED_SNAKE_L);
    }

    if (xTaskCreate(task_snake_right, TASK_NAME_LED_SNAKE_R, configMINIMAL_STACK_SIZE + 100, NULL, NORMAL_TASK_PRIORITY, NULL) != pdPASS) {
        PRINTF("Unable to create task '%s'!\r\n", TASK_NAME_LED_SNAKE_R);
    }

    if (xTaskCreate(task_switches, TASK_NAME_SWITCHES, configMINIMAL_STACK_SIZE + 100, NULL, NORMAL_TASK_PRIORITY, NULL) != pdPASS) {
        PRINTF("Unable to create task '%s'!\r\n", TASK_NAME_SWITCHES);
    }

    vTaskStartScheduler();

    while (1);

    return 0;
}