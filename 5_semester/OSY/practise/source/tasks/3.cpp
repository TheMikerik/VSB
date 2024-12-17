void control_all_leds(bool turn_on)
{
    TaskHandle_t handle_led_pta = xTaskGetHandle(TASK_NAME_LED_PTA);
    TaskHandle_t handle_snake_l = xTaskGetHandle(TASK_NAME_LED_SNAKE_L);
    TaskHandle_t handle_snake_r = xTaskGetHandle(TASK_NAME_LED_SNAKE_R);
    
    if (turn_on)
    {
        if (handle_led_pta)
            vTaskResume(handle_led_pta);
        if (handle_snake_l)
            vTaskResume(handle_snake_l);
        if (handle_snake_r)
            vTaskResume(handle_snake_r);
    }
    else
    {
        if (handle_led_pta)
            vTaskSuspend(handle_led_pta);
        if (handle_snake_l)
            vTaskSuspend(handle_snake_l);
        if (handle_snake_r)
            vTaskSuspend(handle_snake_r);
        
        for (int i = 0; i < LED_PTA_NUM; i++)
        {
            GPIO_PinWrite(g_led_pta[i].m_led_gpio, g_led_pta[i].m_led_pin, 0);
        }
        for (int i = 0; i < LED_PTC_NUM; i++)
        {
            GPIO_PinWrite(g_led_ptc[i].m_led_gpio, g_led_ptc[i].m_led_pin, 0);
        }
    }
}