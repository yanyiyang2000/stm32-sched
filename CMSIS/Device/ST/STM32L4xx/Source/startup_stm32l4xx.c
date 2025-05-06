/******************************************************************************
 * @file     startup_stm32l4xx.c
 * @brief    CMSIS-Core(M) Device Startup File for STM32L4xx
 * @version  V1.0.0
 * @date     20. January 2021
 ******************************************************************************/
/*
 * Copyright (c) 2009-2021 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "stm32l4xx.h"

/*---------------------------------------------------------------------------
  External References
 *---------------------------------------------------------------------------*/
extern uint32_t __INITIAL_SP;
extern uint32_t __STACK_LIMIT;
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
extern uint32_t __STACK_SEAL;
#endif

extern __NO_RETURN void __PROGRAM_START(void);

/*---------------------------------------------------------------------------
  Internal References
 *---------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler  (void);
__NO_RETURN void Default_Handler(void);

/*---------------------------------------------------------------------------
  Exception / Interrupt Handler,
 *---------------------------------------------------------------------------*/
/* Exceptions */
void NMI_Handler            		(void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler      		(void) __attribute__ ((weak));
void MemManage_Handler      		(void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler       		(void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler     		(void) __attribute__ ((weak, alias("Default_Handler")));
void SecureFault_Handler    		(void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler            		(void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler       		(void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler         		(void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler        		(void) __attribute__ ((weak, alias("Default_Handler")));

/* Interrupts */
void WWDG_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_PVM_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void RCC_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI3_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel2_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel3_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel4_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel5_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel6_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel7_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC1_2_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_TX_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX0_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX1_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_SCE_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_TIM15_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_UP_TIM16_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM17_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM3_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM4_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void USART1_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void USART3_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void DFSDM1_FLT3_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_BRK_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_UP_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_TRG_COM_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC3_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void FMC_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void SDMMC1_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM5_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void UART4_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void UART5_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM6_DAC_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM7_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel1_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel2_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel3_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel4_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel5_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DFSDM1_FLT0_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void DFSDM1_FLT1_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void DFSDM1_FLT2_IRQHandler         (void) __attribute__ ((weak, alias("Default_Handler")));
void COMP_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void LPTIM1_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void LPTIM2_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel6_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel7_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void LPUART1_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void QUADSPI_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void SAI1_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void SAI2_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void SWPMI1_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void TSC_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void LCD_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void RNG_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));

/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

extern const void * __VECTOR_TABLE[];

const void * __VECTOR_TABLE[] __VECTOR_TABLE_ATTRIBUTE = {
  (&__INITIAL_SP),          /*     Initial Stack Pointer */
  Reset_Handler,            /*     Reset Handler */
  NMI_Handler,              /* -14 NMI Handler */
  HardFault_Handler,        /* -13 Hard Fault Handler */
  MemManage_Handler,        /* -12 MPU Fault Handler */
  BusFault_Handler,         /* -11 Bus Fault Handler */
  UsageFault_Handler,       /* -10 Usage Fault Handler */
  SecureFault_Handler,      /*  -9 Secure Fault Handler */
  0,                        /*     Reserved */
  0,                        /*     Reserved */
  0,                        /*     Reserved */
  SVC_Handler,              /*  -5 SVCall Handler */
  DebugMon_Handler,         /*  -4 Debug Monitor Handler */
  0,                        /*     Reserved */
  PendSV_Handler,           /*  -2 PendSV Handler */
  SysTick_Handler,          /*  -1 SysTick Handler */

  /* Interrupts */
  WWDG_IRQHandler,
  PVD_PVM_IRQHandler,
  TAMP_STAMP_IRQHandler,
  RTC_WKUP_IRQHandler,
  FLASH_IRQHandler,
  RCC_IRQHandler,
  EXTI0_IRQHandler,
  EXTI1_IRQHandler,
  EXTI2_IRQHandler,
  EXTI3_IRQHandler,
  EXTI4_IRQHandler,
  DMA1_Channel1_IRQHandler,
  DMA1_Channel2_IRQHandler,
  DMA1_Channel3_IRQHandler,
  DMA1_Channel4_IRQHandler,
  DMA1_Channel5_IRQHandler,
  DMA1_Channel6_IRQHandler,
  DMA1_Channel7_IRQHandler,
  ADC1_2_IRQHandler,
  CAN1_TX_IRQHandler,
  CAN1_RX0_IRQHandler,
  CAN1_RX1_IRQHandler,
  CAN1_SCE_IRQHandler,
  EXTI9_5_IRQHandler,
  TIM1_BRK_TIM15_IRQHandler,
  TIM1_UP_TIM16_IRQHandler,
  TIM1_TRG_COM_TIM17_IRQHandler,
  TIM1_CC_IRQHandler,
  TIM2_IRQHandler,
  TIM3_IRQHandler,
  TIM4_IRQHandler,
  I2C1_EV_IRQHandler,
  I2C1_ER_IRQHandler,
  I2C2_EV_IRQHandler,
  I2C2_ER_IRQHandler,
  SPI1_IRQHandler,
  SPI2_IRQHandler,
  USART1_IRQHandler,
  USART2_IRQHandler,
  USART3_IRQHandler,
  EXTI15_10_IRQHandler,
  RTC_Alarm_IRQHandler,
  DFSDM1_FLT3_IRQHandler,
  TIM8_BRK_IRQHandler,
  TIM8_UP_IRQHandler,
  TIM8_TRG_COM_IRQHandler,
  TIM8_CC_IRQHandler,
  ADC3_IRQHandler,
  FMC_IRQHandler,
  SDMMC1_IRQHandler,
  TIM5_IRQHandler,
  SPI3_IRQHandler,
  UART4_IRQHandler,
  UART5_IRQHandler,
  TIM6_DAC_IRQHandler,
  TIM7_IRQHandler,
  DMA2_Channel1_IRQHandler,
  DMA2_Channel2_IRQHandler,
  DMA2_Channel3_IRQHandler,
  DMA2_Channel4_IRQHandler,
  DMA2_Channel5_IRQHandler,
  DFSDM1_FLT0_IRQHandler,
  DFSDM1_FLT1_IRQHandler,
  DFSDM1_FLT2_IRQHandler,
  COMP_IRQHandler,
  LPTIM1_IRQHandler,
  LPTIM2_IRQHandler,
  OTG_FS_IRQHandler,
  DMA2_Channel6_IRQHandler,
  DMA2_Channel7_IRQHandler,
  LPUART1_IRQHandler,
  QUADSPI_IRQHandler,
  I2C3_EV_IRQHandler,
  I2C3_ER_IRQHandler,
  SAI1_IRQHandler,
  SAI2_IRQHandler,
  SWPMI1_IRQHandler,
  TSC_IRQHandler,
  LCD_IRQHandler,
  0,
  RNG_IRQHandler,
  FPU_IRQHandler,
};

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

/*---------------------------------------------------------------------------
  Reset Handler called on controller reset
 *---------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler(void)
{
  __set_PSP((uint32_t)(&__INITIAL_SP));

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  __TZ_set_STACKSEAL_S((uint32_t *)(&__STACK_SEAL));
#endif

  SystemInit();                    /* CMSIS System Initialization */
  __PROGRAM_START();               /* Enter PreMain (C library entry point) */
}


#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

/*---------------------------------------------------------------------------
  Hard Fault Handler
 *---------------------------------------------------------------------------*/
void HardFault_Handler(void)
{
  while(1);
}

/*---------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *---------------------------------------------------------------------------*/
void Default_Handler(void)
{
  while(1);
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#endif
