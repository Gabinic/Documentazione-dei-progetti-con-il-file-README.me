#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"   
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "AppRullo.h"
#include "timers.h"                     // ARM.FreeRTOS::RTOS:Timers
#include "LCD.h"
#include "Arduino.h"
#include <stdio.h>
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups

void ServoMotoreInit(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	GPIOE->MODER &= ~GPIO_MODER_MODE11_Msk;
	GPIOE->MODER |= GPIO_MODER_MODE11_1;
	GPIOE->AFR[0] &= ~GPIO_AFRH_AFSEL11_Msk;
	GPIOE->AFR[0] |= GPIO_AFRH_AFSEL11_1;
}

void TriggerInit(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &= ~GPIO_MODER_MODE3_Msk;
	GPIOB->MODER |= GPIO_MODER_MODE3_1;
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL3_Msk ;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL3_0;
}

void EchoInit(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
	GPIOA->MODER |= GPIO_MODER_MODE5_1;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL5_Msk;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_0;
}

void MotoreInit(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	GPIOE->MODER &= ~GPIO_MODER_MODE14_Msk;
	GPIOE->MODER |= GPIO_MODER_MODE14_1;
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL14_Msk;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL14_0;
}
