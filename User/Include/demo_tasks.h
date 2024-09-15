#ifndef DEMO_TASKS_H
#define DEMO_TASKS_H

/* Standard library API */
#include <stdint.h>


#define DEMO_TASK_1_STACK_SIZE 100  // The stack size of Task 1 in words (4 bytes) (must be greater than `TM_NUM_REGS`)
#define DEMO_TASK_2_STACK_SIZE 200  // The stack size of Task 2 in words (4 bytes) (must be greater than `TM_NUM_REGS`)

/* Task Stack for Task 1 */
extern uint32_t demo_task_1_stack[DEMO_TASK_1_STACK_SIZE];

/* Task Stack for Task 2 */
extern uint32_t demo_task_2_stack[DEMO_TASK_2_STACK_SIZE];

/* Task Routine for Task 1 */
void demo_task_1_enter();

/* Task Routine for Task 2 */
void demo_task_2_enter();

#endif /* DEMO_TASKS_H */
