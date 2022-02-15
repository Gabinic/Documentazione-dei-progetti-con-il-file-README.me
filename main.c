//=== INCLUDES =============================================================================
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"   
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "timer.h"                     // ARM.FreeRTOS::RTOS:Timers
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include <stdio.h>
#include "clock.h"
#include "Arduino.h"
#include "AppRullo.h"
#include "LCD.h"
#include "Puls.h"
#include "Led.h"

#define PIN_INFRAROSSI PE10

#define EVENT_RILEVA_OGGETTO  		 1 << 1 // zero shift for bit0
#define EVENT_RILEVA_COLORE	  		 1 << 2 // zero shift for bit0

void vTaskRilevaOggetto(void * pvParameters);
void vTaskRilevaColore(void * pvParameters);

EventGroupHandle_t xServo;

int main(void){ 
	pllInit(0,10,0);
	pinMode(PB2,OUTPUT);
	pinMode(PE8,OUTPUT);
	pinMode(PIN_INFRAROSSI,INPUT);
	
	xTaskCreate(vTaskRilevaOggetto, /* Pointer to the function that implements the task.              */
		"Task 1 (Toggle Rileva Oggetto)",    /* Text name for the task.  This is to facilitate debugging only. */
		50,   /* Stack depth in words.                */
		NULL,  /* We are not using the task parameter. */
		1,     /* This task will run at priority 1.    */
		NULL); /* We are not using the task handle.    */
	xTaskCreate(vTaskRilevaColore, /* Pointer to the function that implements the task.              */
		"Task 1 (Toggle Rileva Colore)",    /* Text name for the task.  This is to facilitate debugging only. */
		50,   /* Stack depth in words.                */
		NULL,  /* We are not using the task parameter. */
		1,     /* This task will run at priority 1.    */
		NULL); /* We are not using the task handle.    */

	xServo=xEventGroupCreate();
	vTaskStartScheduler();
}

void vTaskRilevaOggetto(void * pvParameters){
	TIM2_CH1_InCapt_SM();
	TIM2_CH2_PWM();	
	while(1){
	}
}

void vTaskRilevaColore(void * pvParameters){
	const EventBits_t xBitsToWaitFor = EVENT_RILEVA_OGGETTO;
	char colore;
	while(1){
		xEventGroupWaitBits(xServo,xBitsToWaitFor,pdTRUE,pdTRUE,portMAX_DELAY);
		vTaskDelay(800);
		colore=digitalRead(PIN_INFRAROSSI);
		if(colore==0){
			xEventGroupSetBits(xServo,EVENT_SMISTASX);
		}
		else{
			xEventGroupSetBits(xServo,EVENT_SMISTADX);
		}
	}
}