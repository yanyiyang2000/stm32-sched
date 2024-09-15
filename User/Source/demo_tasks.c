/* CMSIS Device API */
#include "stm32l476xx.h"

/* CMSIS Core API */
#include "cmsis_gcc.h"

/* User API */
#include "demo_tasks.h"


uint32_t demo_task_1_stack[DEMO_TASK_1_STACK_SIZE] = {0};

uint32_t demo_task_2_stack[DEMO_TASK_2_STACK_SIZE] = {0};

void demo_task_1_enter() {
    while (1) {
        __ASM volatile ("mov r0,  0x10101010");
        __ASM volatile ("mov r1,  0x11111111");
        __ASM volatile ("mov r2,  0x12121212");
        __ASM volatile ("mov r3,  0x13131313");
        __ASM volatile ("mov r4,  0x14141414");
        __ASM volatile ("mov r5,  0x15151515");
        __ASM volatile ("mov r6,  0x16161616");
        __ASM volatile ("mov r7,  0x17171717");
        __ASM volatile ("mov r8,  0x18181818");
        __ASM volatile ("mov r9,  0x19191919");
        __ASM volatile ("mov r10, 0x1A1A1A1A");
        __ASM volatile ("mov r11, 0x1B1B1B1B");
        __ASM volatile ("mov r12, 0x1C1C1C1C");
    }
}

void demo_task_2_enter() {
    while (1) {
        __ASM volatile ("mov r0,  0x20202020");
        __ASM volatile ("mov r1,  0x21212121");
        __ASM volatile ("mov r2,  0x22222222");
        __ASM volatile ("mov r3,  0x23232323");
        __ASM volatile ("mov r4,  0x24242424");
        __ASM volatile ("mov r5,  0x25252525");
        __ASM volatile ("mov r6,  0x26262626");
        __ASM volatile ("mov r7,  0x27272727");
        __ASM volatile ("mov r8,  0x28282828");
        __ASM volatile ("mov r9,  0x29292929");
        __ASM volatile ("mov r10, 0x2A2A2A2A");
        __ASM volatile ("mov r11, 0x2B2B2B2B");
        __ASM volatile ("mov r12, 0x2C2C2C2C");
    }
}