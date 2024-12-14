# Table of Contents
- [Introduction](#introduction)
- [Registers of Interest](#registers-of-interest)
- [Phase 1: Power On and Reset](#phase-1-power-on-and-reset)
- [Phase 2: Start the First Task](#phase-2-start-the-first-task)
- [Phase 3: Automatic Task Switch](#phase-3-automatic-task-switch)

# Introduction
This is a demonstration of a custom Task Scheduler running on an ARMv7-M processor (Cortex-M4). It is assumed that the FPU of the processor is not enabled for the simplicity.

# Registers of Interest
- `R0` - `R12`
- `R13` (a.k.a. `SP`)
    - Alias to `MSP` if `SPSEL` bit of the `CONTROL` register is 0
    - Alias to `PSP` if `SPSEL` bit of the `CONTROL` register is 1
- `R14` (a.k.a. `LR`)
- `R15` (a.k.a. `PC`)
- `xPSR`
- `CONTROL`

# Phase 1: Power On and Reset
A **Reset exception** is triggered when the processor is powered on. 

Upon the entry of the exception, the processor (hardware) will do the following:
1. Set mode to **Thread Mode**.
2. Set `MSP` to the first value in the **Vector Table** and align it *downward* to the nearest 8-byte boudary.
3. Set `PSP` to an unknown value and align it *downward* to the nearest 8-byte boudary.
4. Use `MSP` as `SP` (i.e., the `SPSEL` bit of `CONTROL` is 0 by default).
5. ... (See *Armv7-M Architecture Reference Manual B1.5.5 Reset behavior*)
6. Branch to **Reset Handler**.

The **Reset Handler** (software, defined in `startup_stm32l4xx.c`) will then do the following:
1. Set `PSP` to the top of the `.stack` section (defined in the linker script). 
2. Call `SystemInit` to remap vector table and set up FPU  (defined in `system_stm32l4xx.c`).
3. Call `cmsis_start` to initialize `.bss` and `.data` section in RAM (defined in `cmsis_gcc_m.h`).
4. Call `_start` to call `main` (defined in `crt0.S`).

Now the processor is in **Thread Mode** and `MSP` is used.


# Phase 2: Start the First Task
An **SVC exception** is triggered by the `svc 0` instruction in `main.c`.

Upon the entry of the exception, the processor (hardware) will do the following:
1. Push the values of `R0` - `R3`, `R12`, `SP`, `LR`, `PC` and `xPSR` onto the stack pointed to by `MSP`.
2. Enter **Handler Mode** and use `MSP` as `SP`
3. ... (See *Armv7-M Architecture Reference Manual B1.5.6 Exception entry behavior*)
4. Branch to **SVC Handler**.

The **SVC Handler** (software, defined in `isr.c`) will then do the following:
1. Select a task.
2. Set `PSP` to the top of the task stack specified by the task's **Task Control Block**.
3. Pop the values of `R4` - `R11` of the task from the stack pointed to by `PSP`.
4. Set `LR` to `0xFFFFFFFD`[^1] to instruct the processor to enter **Thread Mode** and use `PSP` as `SP` upon exception return[^2].
5. Enable **SysTick interrupt** to perform task switch later on.
[^1]: See *Armv7-M Architecture Reference Manual Table B1-8* for the effects of different `LR` values.
[^2]: Setting `LR` to `0xFFFFFFFD` will cause the hardware to set the `SPSEL` bit of `CONTROL` to 1. (*Armv7-M Architecture Reference Manual B1.5.8 Exception return behavior*)

Upon the return of the exception, the processor (hardware) will do the following:
- Enter **Thread Mode** and use `PSP` as `SP`
- Pop the values of `R0` - `R3`, `R12`, `SP`, `LR`, `PC` and `xPSR` of the task from the stack pointed to by `PSP`.
- ... (See *Armv7-M Architecture Reference Manual B1.5.8 Exception return behavior*)

The first instruction of the selected task will be executed next!

Now the processor is in **Thread Mode** and `PSP` is used.


# Phase 3: Automatic Task Switch
An **SysTick interrupt** is triggered when a certain amount of time has elapsed.

Upon the entry of the interrupt, the processor (hardware) will do the following:
1. Push the values of `R0` - `R3`, `R12`, `SP`, `LR`, `PC` and `xPSR` of the current task onto the stack pointed to by `PSP`.
2. Enter **Handler Mode** and use `MSP` as `SP`.
3. ... (See *Armv7-M Architecture Reference Manual B1.5.6 Exception entry behavior*)
4. Branch to **SysTick Handler**.

The **SysTick Handler** (software, defined in `isr.c`) will then do the following:
1. Push the values of `R4` - `R11` of the current task onto the stack pointed to by `PSP`.
2. Save `PSP` of the current task into its TCB.
3. Select a task.
4. Restore `PSP` of the new task from its TCB.
5. Pop the values of `R4` - `R11` of the new task from the stack pointed to by `PSP`.

Upon the return of the interrupt, the processor (hardware) will do the following:
- Enter **Thread Mode** and use `PSP` as `SP`.
- Pop the values of `R0` - `R3`, `R12`, `SP`, `LR`, `PC` and `xPSR` of the new task from the stack pointed to by `PSP`.
- ... (See *Armv7-M Architecture Reference Manual B1.5.8 Exception return behavior*)

Now the processor is in **Thread Mode** and `PSP` is used.

# Implementation
The Task Scheduler adopts round robin task switch: Tasks are stored in a linked-list-like Task List and are selected in the order they present in the Task List.

For the moment, two functions are exposed to users:
- `ts_initialize` for initializing the Task Scheduler
- `ts_create_task` for adding a new Task to the Task List

# Caveats
The `tcb` struct (defined in `task_scheduler.h`) has the data structure embedded, there are both pro and con:
- Pro: A standalone struct for the data structure is not need.
- Con: If in the future we would like to change the way of storing Tasks, there might be a major modification to the code that involves the `tcb` struct.