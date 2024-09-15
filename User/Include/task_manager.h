#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

/* Standard library API */
#include <stdint.h>


#define TM_NUM_TASKS        10      // The number of Tasks
#define TM_NUM_REGS         16      // The number of registers saved on Task Stack

#define TM_STATUS_SUCCESS   0       // Status code for success
#define TM_STATUS_FAILURE   1       // Status code for failure

/* Task Control Block (TCB) Node */
struct __attribute__((packed)) tcb {
    uint32_t   stack_top;   // THe address of the top of the Task Stack
    struct tcb *next_tcb;   // The pointer to the next TCB Node
};

/* The list of initialized TCB Nodes */
extern struct tcb tm_tcb_list[TM_NUM_TASKS];

/* The sentinel TCB Node */
extern struct tcb tm_sentinel_tcb;

/* The pointer to the current TCB Node */
extern struct tcb *tm_curr_tcb;

/**
 * @brief This function initializes a Task List.
 * 
 * @note The Task List is a circular doubly linked list of TCB Nodes.
 */
void tm_initialize();

/**
 * @brief This function creates a new Task and prepends it to the Task List.
 * 
 * @param task_stack      The pointer to the first word of the Task Stack
 * @param task_stack_size The size of the Task Stack in words (4 bytes)
 * @param task            The starting address of the Task Routine
 * 
 * @return `TM_STATUS_SUCCESS` if succeeds and `TM_STATUS_FAILURE` otherwise.
 */
uint8_t tm_create_task(uint32_t *task_stack, uint32_t task_stack_size, uint32_t task);

/**
 * @brief This function selects a new Task from the Task List.
 * 
 * @note The new Task is the next Task of the current Task.
 */
void tm_select_task();

#endif /* TASK_MANAGER_H */
