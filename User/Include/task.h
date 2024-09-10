#ifndef TASK_H
#define TASK_H

/* Standard library API */
#include <stdint.h>


/* Task Struct Definition */
struct __attribute__((packed)) tcb {
    uint32_t stack_top;
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;
};

/* Task Stacks */
extern uint32_t task_1_stack[];
extern uint32_t task_2_stack[];

/* Task Routines */
void task_1_enter();
void task_2_enter();

#endif /* TASK_H */
