/* Standard library API */
#include <stdint.h>

/* CMSIS Device API */
#include "stm32l476xx.h"

/* CMSIS Core API */
#include "core_cm4.h"

/* User API */
#include "msi_config.h"
#include "task_manager.h"
#include "demo_tasks.h"


int main() {
    // Configure MSI to around 48 MHz
    MSI_config();

    // Configure SysTick to 1 kHz
    SysTick_Config(SystemCoreClock/1000);

    // Initialize Task Manager
    tm_initialize();

    // Create Tasks
    tm_create_task(demo_task_1_stack, DEMO_TASK_1_STACK_SIZE, (uint32_t)&demo_task_1_enter);
    tm_create_task(demo_task_2_stack, DEMO_TASK_2_STACK_SIZE, (uint32_t)&demo_task_2_enter);

    // Start Task Manager
    __ASM volatile ("svc 0");

    while (1);
}