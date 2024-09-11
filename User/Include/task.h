#ifndef TASK_H
#define TASK_H

/* Standard library API */
#include <stdint.h>


/* Task Control Block (TCB) */
struct __attribute__((packed)) tcb {
    uint32_t stack_top;
};

/* Doubly Linked List Node for TCB */
struct tcb_node {
    struct tcb *tcb;
    // struct tcb_node *prev_node;
    struct tcb_node *next_node;
};

/* Pointer to current TCB Node */
extern struct tcb_node *curr_tcb_node_ptr;

/* Pointer to current TCB */
extern struct tcb *curr_tcb_ptr;

/* TCB for Task 1 */
extern struct tcb task_1_tcb;

/* TCB for Task 2 */
extern struct tcb task_2_tcb;

/* TCB for Task 3 */
// extern struct tcb task_3_tcb;

/* Task Stack for Task 1 */
extern uint32_t task_1_stack[];

/* Task Stack for Task 2 */
extern uint32_t task_2_stack[];

/* Task Stack for Task 3 */
// extern uint32_t task_3_stack[];

/* Task Routines for Task 1 */
void task_1_enter();

/* Task Routines for Task 2 */
void task_2_enter();

/* Task Routines for Task 3 */
// void task_3_enter();

/* TCB Doubly Linked List Node for Task 1 */
extern struct tcb_node task_1_tcb_node;

/* TCB Doubly Linked List Node for Task 2 */
extern struct tcb_node task_2_tcb_node;

/* TCB Doubly Linked List Node for Task 3 */
// extern struct tcb_node task_3_tcb_node;

void select_next_task();

#endif /* TASK_H */
