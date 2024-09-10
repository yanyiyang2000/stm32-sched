/* Standard library API */
#include <stdint.h>

/* CMSIS Device API */
#include "stm32l476xx.h"

/* CMSIS Core API */
#include "core_cm4.h"

/* User API */
#include "clock_config.h"


int main() {
    // Configure MSI to around 48 MHz
    MSI_config();

    // Configure SysTick to 1 kHz
    SysTick_Config(SystemCoreClock/1000);

    // Start Task Scheduler
    __ASM volatile ("svc 0");

    while (1);
}