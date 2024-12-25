/* Standard library API */
#include <stdint.h>
#include <stddef.h>

/* CMSIS Device API */
#include "stm32l476xx.h"

/* CMSIS Core API */
#include "cmsis_gcc.h"

/* User API */
#include "task_scheduler.h"


struct tcb ts_tcb_list[TS_NUM_TASKS] = {0};

struct tcb ts_sentinel_tcb = {0};

struct tcb *ts_curr_tcb = NULL;

void ts_initialize() {
    /* Initialize the Task List */
    ts_sentinel_tcb.stack_top = 0;
    ts_sentinel_tcb.next_tcb = &ts_sentinel_tcb;

    /* TODO: probably add a defult Task Stack for the sentinel TCB Node */
    ts_curr_tcb = &ts_sentinel_tcb;
}

uint8_t ts_create_task(uint32_t *task_stack, uint32_t task_stack_size, uint32_t task) {
    /**
     * TODO: 
     * 1. It's kinda misleading why `task` is a u32 instead a func ptr.
     * 2. The actual available task stack is (task_stack_size - TS_NUM_REGS) words.
     * 3. This function is not idiot-proof if user provides a smaller task stack. (how to become idiot-proof?)
     */

    struct tcb *new_tcb; // The pointer to the new TCB Node

    /* Initialize the Task Stack */
    task_stack[task_stack_size - 2] = task;         // PC
    task_stack[task_stack_size - 1] = 0x01000000;   // xPSR

    /* Initialize the new TCB Node if the Task List has vacancy */
    for (uint16_t i = 0; i < TS_NUM_TASKS; i++) {
        if (ts_tcb_list[i].stack_top == 0) {
            /* Initialize the new TCB Node */
            new_tcb = &(ts_tcb_list[i]);
            new_tcb->stack_top = (uint32_t)(task_stack + task_stack_size - TS_NUM_REGS);

            /* Prepend the new TCB Node to the Task List */
            new_tcb->next_tcb = ts_sentinel_tcb.next_tcb;
            ts_sentinel_tcb.next_tcb = new_tcb;

            return TS_STATUS_SUCCESS;
        }
    }

    return TS_STATUS_FAILURE;
}

void ts_select_task() {
    /* Select the next TCB Node */
    ts_curr_tcb = ts_curr_tcb->next_tcb;

    /* Skip the sentinel TCB Node once */
    if (ts_curr_tcb == &ts_sentinel_tcb) {
        ts_curr_tcb = ts_curr_tcb->next_tcb;
    }
}
