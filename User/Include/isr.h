#ifndef ISR_H
#define ISR_H

/* Standard library API */
#include <stdint.h>

/* CMSIS Device API */
#include "stm32l476xx.h"

/* CMSIS Core API */
#include "core_cm4.h"


void SysTick_Handler() __attribute__ ((naked));

void SVC_Handler() __attribute__ ((naked));

#endif /* ISR_H */
