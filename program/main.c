//#define DEBUG
#include "stm32f4xx_conf.h"
#include "../common/delay.h"
#include "gpio.h"
#include "led.h"
#include "i2c.h"
#include "usart.h"
#include "spi.h"
#include "can.h"
#include "tim.h"
#include "flight_controller.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"

#include "global.h"
#include "communication.h"
#include "system_time.h"
#include "lea6h_ubx.h"
extern uint8_t estimator_trigger_flag;

/* FreeRTOS */
extern xSemaphoreHandle serial_tx_wait_sem;
extern xQueueHandle serial_rx_queue;
extern xQueueHandle gps_serial_queue;
extern xSemaphoreHandle usart3_dma_send_sem;
xTimerHandle xTimers[1];

void vApplicationStackOverflowHook( xTaskHandle xTask, signed char *pcTaskName );
void vApplicationIdleHook(void);
void vApplicationMallocFailedHook(void);
void boot_time_timer(void);
void gpio_rcc_init(void);
void gpio_rcc_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | 
	RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE,  ENABLE);	
}

void vApplicationStackOverflowHook( xTaskHandle Task __attribute__ ((unused)), signed char *pcTaskName __attribute__ ((unused)))
{
	while(1);

}
void vApplicationIdleHook(void)
{

}
void vApplicationMallocFailedHook(void)
{
	while(1);
}

uint8_t buffer1[] = "HelloEveryoneThisIsBuffer1  \r\n";
uint8_t buffer2[] = "OhMyGodICanSwapToTheBuffer2 \r\n";

void dummy_task1(void);
void dummy_task2(void);
void dummy_task3(void);
void dummy_task4(void);

void dummy_task1(void){

 	/* Generate  vTaskDelayUntil parameters */
	portTickType xLastWakeTime;
	const portTickType xFrequency = (uint32_t)25/(1000.0 / configTICK_RATE_HZ);

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
    uint8_t text_dummy[100];
	uint8_t error_capture;
	int32_t success=0,skipped=0;
	uint16_t length=0;
    while(1){

    	length = sprintf((char *)text_dummy,"DUMMY1, s = %d, sk = %d \r\n",success,skipped);
    	error_capture = streaming_dma_tx_append_data_to_buffer(text_dummy,length, ACCESSING_FLAG_TASK_DUMMY1);
    	if(error_capture == NO_ERROR){

    		success++;

    	}else if (error_capture == BUFFER_FULL){

    		skipped++;

    	}
    	LED_TOGGLE(LED1);
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
	
}

void dummy_task2(void){

 	/* Generate  vTaskDelayUntil parameters */
	portTickType xLastWakeTime;
	const portTickType xFrequency = (uint32_t)55/(1000.0 / configTICK_RATE_HZ);

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
    uint8_t text_dummy[100];
	uint8_t error_capture;
	int32_t success=0,skipped=0;
	uint16_t length=0;
    while(1){

    	length = sprintf((char *)text_dummy,"DUMMY2, s = %d, sk = %d \r\n",success,skipped);
    	error_capture = streaming_dma_tx_append_data_to_buffer(text_dummy,length, ACCESSING_FLAG_TASK_DUMMY2);
    	if(error_capture == NO_ERROR){

    		success++;

    	}else if (error_capture == BUFFER_FULL){

    		skipped++;

    	}
    	LED_TOGGLE(LED2);
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
	
}

void dummy_task3(void){
 	/* Generate  vTaskDelayUntil parameters */
	portTickType xLastWakeTime;
	const portTickType xFrequency = (uint32_t)75/(1000.0 / configTICK_RATE_HZ);

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
    uint8_t text_dummy[100];
	uint8_t error_capture;
	int32_t success=0,skipped=0;
	uint16_t length=0;
    while(1){

    	length = sprintf((char *)text_dummy,"DUMMY3, s = %d, sk = %d \r\n",success,skipped);
    	error_capture = streaming_dma_tx_append_data_to_buffer(text_dummy,length, ACCESSING_FLAG_TASK_DUMMY3);
    	if(error_capture == NO_ERROR){

    		success++;

    	}else if (error_capture == BUFFER_FULL){

    		skipped++;

    	}
    	LED_TOGGLE(LED3);
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }

	
}

void dummy_task4(void){

 	/* Generate  vTaskDelayUntil parameters */
	portTickType xLastWakeTime;
	const portTickType xFrequency = (uint32_t)33/(1000.0 / configTICK_RATE_HZ);

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
    uint8_t text_dummy[100];
	uint8_t error_capture;
	int32_t success=0,skipped=0;
	uint16_t length=0;
    while(1){

    	length = sprintf((char *)text_dummy,"DUMMY4, s = %d, sk = %d \r\n",success,skipped);
    	error_capture = streaming_dma_tx_append_data_to_buffer(text_dummy,length, ACCESSING_FLAG_TASK_DUMMY4);
    	if(error_capture == NO_ERROR){

    		success++;

    	}else if (error_capture == BUFFER_FULL){

    		skipped++;

    	}
    	// LED_TOGGLE(LED4);
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
    } 
}

void flight_control_dummy_task(void){

 	/* Generate  vTaskDelayUntil parameters */
	portTickType xLastWakeTime;
	const portTickType xFrequency = (uint32_t)1/(1000.0 / configTICK_RATE_HZ);

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
    uint8_t text_dummy[] = "This is message from DUMMY4\r\n";
	uint8_t error_capture;

    while(1){

		streaming_dma_tx_dma_trigger();
    	LED_TOGGLE(LED4);
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
}


int main(void)
{
	vSemaphoreCreateBinary(serial_tx_wait_sem);
	serial_rx_queue = xQueueCreate(5, sizeof(serial_msg));
	gps_serial_queue = xQueueCreate(5, sizeof(serial_msg));
	vSemaphoreCreateBinary(flight_control_sem);
	vSemaphoreCreateBinary(usart3_dma_send_sem);
	/* Global data initialazition */
	init_global_data();

	/* Hardware initialization */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	gpio_rcc_init();
	led_init();
	usart_init();
	spi_init();
	pwm_input_output_init();
	init_pwm_motor();
	i2c_Init();
	usart2_dma_init();

	CAN2_Config();
	CAN2_NVIC_Config();

	/* 	Starting dma test part */
	LED_OFF(LED1);
	LED_OFF(LED2);
	LED_OFF(LED3);
	LED_OFF(LED4);
	enable_usart2_dma_interrupt();

	uint8_t text_to_test[] = "12345678\r\n123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345";
	uint8_t text_to_test2[] = "1234567890123456\r\n";
	uint8_t error_capture = streaming_dma_tx_append_data_to_buffer(text_to_test,1, ACCESSING_FLAG_TASK_DUMMY1);


	// while(1){
	// 		streaming_dma_tx_append_data_to_buffer(text_to_test,10, ACCESSING_FLAG_TASK_MAIN);
	// 		streaming_dma_tx_append_data_to_buffer(text_to_test,10, ACCESSING_FLAG_TASK_MAIN);
	// 		streaming_dma_tx_append_data_to_buffer(text_to_test2,18, ACCESSING_FLAG_TASK_MAIN);
	// 		Delay_1us(200);
	// 		LED_TOGGLE(LED1);

	// 		// usart2_dma_burst_send(text_to_test,20);
	// 		//usart2_dma_send(text_to_test);
	// }



	/* Register the FreeRTOS task */
	/* Flight control task */
	// xTaskCreate(
	// 	(pdTASK_CODE)flight_control_task,
	// 	(signed portCHAR*)"flight control task",
	// 	4096,
	// 	NULL,
	// 	tskIDLE_PRIORITY + 9,
	// 	NULL
	// );
	/* NEEED CLEAN UP, FOR TEST PURPOSE ONLY */

	xTaskCreate(
		(pdTASK_CODE)flight_control_dummy_task,
		(signed portCHAR*)"fcu_dummy_task",
		512,
		NULL,
		tskIDLE_PRIORITY + 8,
		NULL
	);

	xTaskCreate(
		(pdTASK_CODE)dummy_task1,
		(signed portCHAR*)"dummy_task1",
		512,
		NULL,
		tskIDLE_PRIORITY + 5,
		NULL
	);

	xTaskCreate(
		(pdTASK_CODE)dummy_task2,
		(signed portCHAR*)"dummy_task2",
		512,
		NULL,
		tskIDLE_PRIORITY + 4,
		NULL
	);

	xTaskCreate(
		(pdTASK_CODE)dummy_task3,
		(signed portCHAR*)"dummy_task3",
		512,
		NULL,
		tskIDLE_PRIORITY + 3,
		NULL
	);

	xTaskCreate(
		(pdTASK_CODE)dummy_task4,
		(signed portCHAR*)"dummy_task4",
		512,
		NULL,
		tskIDLE_PRIORITY + 3,
		NULL
	);




#if 0

	/* Navigation task */
	xTaskCreate(
		(pdTASK_CODE)navigation_task,
		(signed portCHAR*)"navigation task",
		512,
		NULL,
		tskIDLE_PRIORITY + 7,
		NULL
	);

	/* Ground station communication task */	
	xTaskCreate(
		(pdTASK_CODE)ground_station_task,
		(signed portCHAR *)"ground station send task",
		2048,
		NULL,
		tskIDLE_PRIORITY + 5,
		NULL
	);

	xTaskCreate(
		(pdTASK_CODE)mavlink_receiver_task,
		(signed portCHAR *) "ground station receive task",
		4096,
		NULL,
		tskIDLE_PRIORITY + 7, NULL
	);

	xTaskCreate(
		(pdTASK_CODE)gps_receive_task,

		(signed portCHAR *) "gps receive task",
		2048,
		NULL,
		tskIDLE_PRIORITY + 8, NULL

	);
#endif

	vTaskStartScheduler();

	return 0;
}


