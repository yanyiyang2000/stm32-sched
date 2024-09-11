/* Standard library API */
#include <stdint.h>

/* CMSIS Device API */
#include "stm32l476xx.h"

/* CMSIS Core API */
#include "cmsis_gcc.h"

/* User API */
#include "task.h"


struct tcb task_1_tcb = {
    .stack_top = (uint32_t)(task_1_stack + 8)
};

struct tcb task_2_tcb = {
    .stack_top = (uint32_t)(task_2_stack + 8)
};

struct tcb_node task_1_tcb_node = {
    &task_1_tcb,
    &task_2_tcb_node
    // &task_3_tcb_node
};

struct tcb_node task_2_tcb_node = {
    &task_2_tcb,
    &task_1_tcb_node
    // &task_1_tcb_node
};

struct tcb_node *curr_tcb_node_ptr = &task_1_tcb_node;

struct tcb *curr_tcb_ptr = &task_1_tcb;

uint32_t task_1_stack[] = {
    0x0,                        // for task stack
    0x0,                        // for task stack
    0x0,                        // for task stack
    0x0,                        // for task stack
    0x0,                        // for task stack
    0x0,                        // for task stack
    0x0,                        // for task stack
    0x0,                        // for task stack

    0x1B1B1B1B,                 // intial value for `R11`
    0x1A1A1A1A,                 // intial value for `R10`
    0x19191919,                 // intial value for `R9`
    0x18181818,                 // intial value for `R8`
    0x17171717,                 // intial value for `R7`
    0x16161616,                 // intial value for `R6`
    0x15151515,                 // intial value for `R5`
    0x14141414,                 // intial value for `R4`

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

    0x2B2B2B2B,
    0x2A2A2A2A,
    0x29292929,
    0x28282828,
    0x27272727,
    0x26262626,
    0x25252525,
    0x24242424,

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

void select_next_task() {
    // For now, simply move on to the next TCB node in the list
    curr_tcb_node_ptr = curr_tcb_node_ptr->next_node;
    curr_tcb_ptr = curr_tcb_node_ptr->tcb;
}
