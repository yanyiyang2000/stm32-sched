/* CMSIS Device API */
#include "stm32l476xx.h"

/* CMSIS Core API */
#include "cmsis_gcc.h"
#include "core_cm4.h"

/* User API */
#include "task.h"
#include "isr.h"

/**
 * TODO: Use linked list to store tasks.
 */

/**
 * Upon the entry of SysTick interrupt, the processor (hardware) will do the following:
 * 
 * 1. Push `R0` - `R3`, `R12`, `SP`, `LR`, `PC` and `xPSR` to the stack pointed 
 *    to by `PSP` because it is used as `SP` prior to the interrupt.
 * 
 * 2. Enter Handler Mode and use `MSP` as `SP`.
 * 
 * Upon the return of SysTick interrupt, the processor (hardware) will do the following:
 * 
 * 1. Enter Thread Mode and use `PSP` as `SP`.
 * 
 * 2. Pop the values of `R0` - `R3`, `R12`, `SP`, `LR`, `PC` and `xPSR` from the stack pointed to by `PSP`.
 * 
 * @note Some registers (i.e., `R0` and `R1`) are used to perform context switch
 *       so no usage of the said registers should precede the context switch 
 *       code. Hence, attribute `naked` is used to prevent the compiler from
 *       adding prologue and epilogue before and after the function. Prologue
 *       and epilogue are instead added manually after the context switch code.
 */
void __attribute__ ((naked)) SysTick_Handler() {
    // Save current task's PSP
    __ASM volatile ("mrs   r0, psp");       // r0 <- psp
    __ASM volatile ("ldr   r1, =task_1");   // r1 <- addr(demo_4_task_1.stack_top)
    __ASM volatile ("str   r0, [r1], #4");  // mem[r1, 4] <- r0
                                            // r1 <- r1 + 4

    // Save current task's R4 - R11
    __ASM volatile ("stmia r1, {r4-r11}");  // mem[r1, 4] <- r4
                                            // r1 <- r1 + 4
                                            // mem[r1, 4] <- r5
                                            // r1 <- r1 + 4
                                            // ...
                                            // mem[r1, 4] <- r11
                                            // r1 <- r1 + 4

    // Restore next task's PSP
    __ASM volatile ("ldr   r1, =task_2");   // r1 <- addr(demo_4_task_2.stack_top)
    __ASM volatile ("ldr   r0, [r1]");      // r0 <- mem[r1, 4]
    __ASM volatile ("msr   psp, r0");       // psp <- r0

    // Prologue
    // __ASM volatile ("push  {r7, lr}");
    // __ASM volatile ("add   r7, sp, #0");

    // Some code here

    // Epilogue
    // __ASM volatile ("mov   sp, r7");
    // __ASM volatile ("pop   {r7, pc}");

    __ASM volatile ("bx    lr");
}

/**
 * Upon the entry of SVC exception, the processor (hardware) will do the following:
 * 
 * 1. Push `R0` - `R3`, `R12`, `SP`, `LR`, `PC` and `xPSR` to the stack pointed 
 *    to by `MSP` because it is used as `SP` prior to the exception.
 * 
 * 2. Enter Handler Mode and use `MSP` as `SP`.
 * 
 * Upon the return of SVC exception, the processor (hardware) will do the following:
 * 
 * 1. Enter Thread Mode and use `PSP` as `SP`. (Effect of setting `LR` to `0xFFFFFFFD`)
 * 
 * 2. Set the `SPSEL` bit of `CONTROL` to 1. (Effect of setting `LR` to `0xFFFFFFFD`)
 * 
 * 3. Pop the values of `R0` - `R3`, `R12`, `SP`, `LR`, `PC` and `xPSR` from the stack pointed to by `PSP`.
 * 
 * @note Some registers (i.e., `R0` and `R1`) are used to perform context switch
 *       so no usage of the said registers should precede the context switch 
 *       code. Hence, attribute `naked` is used to prevent the compiler from
 *       adding prologue and epilogue before and after the function. Prologue
 *       and epilogue are instead added manually after the context switch code.
 */
void __attribute__ ((naked)) SVC_Handler() {
    extern struct tcb task_1;

    // Set task's PSP (TODO: pick the first task (instead of task 1) from the task list)
    __set_PSP(task_1.stack_top);

    // TODO: Restore r4-r11 manually

    // TODO: Enable SysTick interrupt to delegate task switch to SysTick Handler

    __ASM volatile ("ldr    lr, =0xFFFFFFFD");
    __ASM volatile ("bx     lr");
}
