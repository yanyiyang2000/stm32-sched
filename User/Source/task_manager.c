/* Standard library API */
#include <stdint.h>
#include <stddef.h>

/* CMSIS Device API */
#include "stm32l476xx.h"

/* CMSIS Core API */
#include "cmsis_gcc.h"

/* User API */
#include "task_manager.h"


struct tcb tm_tcb_list[TM_NUM_TASKS] = {0};

struct tcb tm_sentinel_tcb = {0};

struct tcb *tm_curr_tcb = NULL;

void tm_initialize() {
    /* Initialize the Task List */
    tm_sentinel_tcb.stack_top = 0;
    tm_sentinel_tcb.next_tcb = &tm_sentinel_tcb;

    /* TODO: probably add a defult Task Stack for the sentinel TCB Node */
    tm_curr_tcb = &tm_sentinel_tcb;
}

uint8_t tm_create_task(uint32_t *task_stack, uint32_t task_stack_size, uint32_t task) {
    struct tcb *new_tcb; // The pointer to the new TCB Node

    /* Initialize the Task Stack */
    task_stack[task_stack_size - 2] = task;
    task_stack[task_stack_size - 1] = 0x01000000;

    for (uint16_t i = 0; i < TM_NUM_TASKS; i++) {
        if (tm_tcb_list[i].stack_top == 0) {
            /* Initialize the new TCB Node */
            new_tcb = &(tm_tcb_list[i]);
            new_tcb->stack_top = (uint32_t)(task_stack + task_stack_size - TM_NUM_REGS);

            /* Prepend the new TCB Node to the Task List */
            new_tcb->next_tcb = tm_sentinel_tcb.next_tcb;
            tm_sentinel_tcb.next_tcb = new_tcb;

            return TM_STATUS_SUCCESS;
        }
    }

    return TM_STATUS_FAILURE;
}

void tm_select_task() {
    /* Select the next TCB Node */
    tm_curr_tcb = tm_curr_tcb->next_tcb;

    /* Skip the sentinel TCB Node once */
    if (tm_curr_tcb == &tm_sentinel_tcb) {
        tm_curr_tcb = tm_curr_tcb->next_tcb;
    }
}
