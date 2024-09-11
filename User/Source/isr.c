/* CMSIS Device API */
#include "stm32l476xx.h"

/* CMSIS Core API */
#include "cmsis_gcc.h"
#include "core_cm4.h"

/* User API */
#include "task.h"
#include "isr.h"


/**
 * Upon the entry of SysTick interrupt, the processor (hardware) will do the following:
 * 
 * 1. Push `R0` - `R3`, `R12`, `SP`, `LR`, `PC` and `xPSR` to the main stack
 *    (pointed to by `PSP`) because it is used as `SP` prior to the interrupt.
 * 
 * 2. Enter Handler Mode and use `MSP` as `SP`.
 * 
 * Upon the return of SysTick interrupt, the processor (hardware) will do the following:
 * 
 * 1. Enter Thread Mode and use `PSP` as `SP`.
 * 
 * 2. Pop the values of `R0` - `R3`, `R12`, `SP`, `LR`, `PC` and `xPSR` from the
 *    process stack (pointed to by `PSP`).
 * 
 * @note 
 * - Some registers (i.e., `R0` and `R1`) are used to perform context switch so 
 *   no usage of the said registers should precede the context switch code. 
 *   Hence, attribute `naked` is used to prevent the compiler from adding
 *   prologue and epilogue before and after the function. Prologue and epilogue 
 *   are instead added manually after the context switch code if needed.
 * 
 * - In order to keep the assembly code as little as possible, the task switch 
 *   is performed in function `select_next_task`. Upon the return of the 
 *   function, `LR` would contain the address of the next instruction instead of 
 *   `EXC_RETURN` (`0xFFFFFFFD` in our case). Hence `LR` needs to be pushed onto 
 *   the stack and poped from the stack, before and after the `select_next_task` 
 *   function call, respectively.
 */
void __attribute__ ((naked)) SysTick_Handler() {
    // Save current task's R4 - R11
    __ASM volatile ("mrs    r0, psp");              // r0 <- psp
    __ASM volatile ("stmdb  r0!, {r4-r11}");        // push r4 - r11 onto process stack and decrement r0

    // Save current task's PSP
    __ASM volatile ("ldr    r1, =curr_tcb_ptr");    // r1 <- addr(curr_tcb_ptr)
    __ASM volatile ("ldr    r1, [r1]");             // r1 <- addr(curr_tcb)
    __ASM volatile ("str    r0, [r1]");             // curr_tcb[0:4] <- r0

    // Save ISR's LR
    __ASM volatile ("stmdb  sp!, {lr}");            // push lr onto main stack and decrement sp

    // Switch task
    __ASM volatile ("bl     select_next_task");

    // Restore ISR's LR
    __ASM volatile ("ldmia  sp!, {lr}");            // pop lr from main stack and increment sp

    // Restore next task's PSP
    __ASM volatile ("ldr    r1, =curr_tcb_ptr");    // r1 <- addr(curr_tcb_ptr)
    __ASM volatile ("ldr    r1, [r1]");             // r1 <- addr(curr_tcb)
    __ASM volatile ("ldr    r0, [r1]");             // r0 <- curr_tcb[0:4]
    
    // Restore next task's R4 - R11
    __ASM volatile ("ldmia  r0!, {r4-r11}");        // pop r4 - r11 from process stack and increment r0
    __ASM volatile ("msr    psp, r0");              // psp <- r0

    // Return
    __ASM volatile ("bx    lr");
}

/**
 * Upon the entry of SVC exception, the processor (hardware) will do the following:
 * 
 * 1. Push `R0` - `R3`, `R12`, `SP`, `LR`, `PC` and `xPSR` to the main stack
 *    (pointed to by `MSP`) because it is used as `SP` prior to the exception.
 * 
 * 2. Enter Handler Mode and use `MSP` as `SP`.
 * 
 * Upon the return of SVC exception, the processor (hardware) will do the following:
 * 
 * 1. Enter Thread Mode and use `PSP` as `SP`. (Effect of setting `LR` to `0xFFFFFFFD`)
 * 
 * 2. Set the `SPSEL` bit of `CONTROL` to 1. (Effect of setting `LR` to `0xFFFFFFFD`)
 * 
 * 3. Pop the values of `R0` - `R3`, `R12`, `SP`, `LR`, `PC` and `xPSR` from the
 *    process stack (pointed to by `PSP`).
 * 
 * @note 
 * - Some registers (i.e., `R0` and `R1`) are used to perform context switch so 
 *   no usage of the said registers should precede the context switch code. 
 *   Hence, attribute `naked` is used to prevent the compiler from adding 
 *   prologue and epilogue before and after the function. Prologue and epilogue 
 *   are instead added manually after the context switch code if needed.
 */
void __attribute__ ((naked)) SVC_Handler() {
    // Set task's PSP
    __ASM volatile ("ldr   r1, =curr_tcb_ptr"); // r1 <- addr(curr_tcb_ptr)
    __ASM volatile ("ldr   r1, [r1]");          // r1 <- addr(curr_tcb)
    __ASM volatile ("ldr   r0, [r1]");          // r0 <- curr_tcb[0:4]

    // Set task's R4 - R11
    __ASM volatile ("ldmia r0!, {r4-r11}");     // pop r4 - r11 from process stack and update r0
    __ASM volatile ("msr   psp, r0");           // psp <- r0

    // TODO: Enable SysTick interrupt to delegate task switch to SysTick Handler

    __ASM volatile ("ldr    lr, =0xFFFFFFFD");
    __ASM volatile ("bx     lr");
}
