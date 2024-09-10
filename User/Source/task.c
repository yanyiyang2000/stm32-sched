/* Standard library API */
#include <stdint.h>

/* CMSIS Device API */
#include "stm32l476xx.h"

/* CMSIS Core API */
#include "cmsis_gcc.h"

/* User API */
#include "task.h"


struct tcb task_1 = {
    .stack_top = (uint32_t)(task_1_stack + 8),
    .r4   = 0xF4F4F4F4,
    .r5   = 0xF5F5F5F5,
    .r6   = 0xF6F6F6F6,
    .r7   = 0xF7F7F7F7,
    .r8   = 0xF8F8F8F8,
    .r9   = 0xF9F9F9F9,
    .r10  = 0xFAFAFAFA,
    .r11  = 0xFBFBFBFB
};

struct tcb task_2 = {
    .stack_top = (uint32_t)(task_2_stack + 8),
    .r4   = 0xF4F4F4F4,
    .r5   = 0xF5F5F5F5,
    .r6   = 0xF6F6F6F6,
    .r7   = 0xF7F7F7F7,
    .r8   = 0xF8F8F8F8,
    .r9   = 0xF9F9F9F9,
    .r10  = 0xFAFAFAFA,
    .r11  = 0xFBFBFBFB
};

uint32_t task_1_stack[] = {
    0x0,                        // for task stack
    0x0,                        // for task stack
    0x0,                        // for task stack
    0x0,                        // for task stack
    0x0,                        // for task stack
    0x0,                        // for task stack
    0x0,                        // for task stack
    0x0,                        // for task stack
    0x10101010,                 // intial value for `R0`
    0x11111111,                 // intial value for `R1`
    0x12121212,                 // intial value for `R2`
    0x13131313,                 // intial value for `R3`
    0x1C1C1C1C,                 // intial value for `R12`
    0xFFFFFFFD,                 // intial value for `LR`
    (uint32_t)&(task_1_enter),  // intial value for `PC`
    0x01000000                  // intial value for `xPSR`
};

uint32_t task_2_stack[] = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x20202020,
    0x21212121,
    0x22222222,
    0x23232323,
    0x2C2C2C2C,
    0xFFFFFFFD,
    (uint32_t)&(task_2_enter),
    0x01000000
};

void task_1_enter() {
    while (1) {
        __ASM volatile ("mov r4, 0x14141414");
        __ASM volatile ("mov r5, 0x15151515");
        __ASM volatile ("mov r6, 0x16161616");
    }
}

void task_2_enter() {
    while (1) {
        __ASM volatile ("mov r4, 0x24242424");
        __ASM volatile ("mov r5, 0x25252525");
        __ASM volatile ("mov r6, 0x26262626");
    }
}
