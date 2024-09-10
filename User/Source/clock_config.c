/* CMSIS Device API */
#include "stm32l476xx.h"
#include "system_stm32l4xx.h"

/* CMSIS Core API */
#include "core_cm4.h"

/* User API */
#include "clock_config.h"


/**
 * This function does the following:
 *   1. Sets LSE oscillator drive capability to higher driving capability.
 *   2. Enables MSI PLL mode.
 *   3. Sets HCLK period time to the flash access time to 2 wait states.
 *   4. Sets MSI clock range to around 48 MHz.
 *
 * Before the function call, the clock configuration is as follows:
 *   - SYSCLK source:    MSI oscillator
 *   - SYSCLK frequency: 4 MHz (MSI clock is 4 MHz [RM0351, p.213])
 *   - HCLK frequency:   4 MHz (AHB PRESC = 1)
 *   - PCLK1 frequency:  4 MHz (APB1 PRESC = 1)
 *   - PCLK2 frequency:  4 MHz (APB2 PRESC = 1)
 *
 * After the function call, the clock configuration is as follows:
 *   - SYSCLK source:    MSI oscillator calibrated by LSE oscillator
 *   - SYSCLK frequency: 48 MHz (MSI clock is 48 MHz)
 *   - HCLK frequency:   48 MHz (AHB PRESC = 1)
 *   - PCLK1 frequency:  48 MHz (APB1 PRESC = 1)
 *   - PCLK2 frequency:  48 MHz (APB2 PRESC = 1)
 *
 * Note: The function may fail setting the MSI clock range to around 48 MHz
 * silently.
 * 
 * Reference: RM0351, p.100; p.213; p.225
 */
void MSI_config() {
    // Enable the PWR APB1 interface clock
    RCC->APB1ENR1 |= 1 << RCC_APB1ENR1_PWREN_Pos;

    // Disable backup domain write protection
    PWR->CR1 |= 1 << PWR_CR1_DBP_Pos;

    // Disable LSE oscillator
    RCC->BDCR &= ~RCC_BDCR_LSEON_Msk;

    // Set LSE oscillator drive capability to higher driving capability (0b11)
    RCC->BDCR &= ~RCC_BDCR_LSEDRV_Msk;
    RCC->BDCR |= 0b11 << RCC_BDCR_LSEDRV_Pos;

    // Enable LSE oscillator
    RCC->BDCR |= 1 << RCC_BDCR_LSEON_Pos;

    // Wait until LSE oscillator is ready
    while (RCC->BDCR && RCC_BDCR_LSERDY_Msk == 0);
        
    /*
     * MSI PLL mode must be enabled after LSE is enabled (LSEON=1) and ready 
     * (LSERDY=1). [RM0351, p.225]
     */
    RCC->CR |= 1 << RCC_CR_MSIPLLEN_Pos;

    /*
     * To correctly read data from Flash memory, the number of wait states 
     * (LATENCY) must be correctly programmed in the Flash access control 
     * register (FLASH_ACR) according to the frequency of the AHB clock (HCLK) 
     * and the internal voltage range of the device (VCORE). [RM0351, p.100]
     */

    // Set HCLK period time to the Flash access time to 2 wait states
    FLASH->ACR &= ~FLASH_ACR_LATENCY_Msk;
    FLASH->ACR |= FLASH_ACR_LATENCY_2WS;

    /*
     * MSIRANGE can only be modified when MSI is OFF (MSION=0) or when MSI is 
     * READY (MSIRDY=1). [RM0351, p.225]
     */
    if ( !(RCC->CR & RCC_CR_MSION_Msk) || (RCC->CR & RCC_CR_MSIRDY_Msk) ) {
        // Set MSI clock range to around 48 MHz (0b1011)
        RCC->CR &= ~RCC_CR_MSIRANGE_Msk;
        RCC->CR |= 0b1011 << RCC_CR_MSIRANGE_Pos;
    }

    // Select the MSI clock range from MSIRANGE
    RCC->CR |= 1 << RCC_CR_MSIRGSEL_Pos;

    // Update the SystemCoreClock variable
    SystemCoreClockUpdate();
}


/**
 * This function configures system clock as follows:
 *   - Clock frequency 1 kHz
 *   - SysTick interrupt enabled
 * 
 * Note: SysTick interrupt is generated every 1 ms.
 * 
 * Reference: ARMv7-M Architecture Reference Manual B3.3
 */
// void SysTick_config() {
//     // Set SysTick interrupt handler priority
//     NVIC_SetPriority(SysTick_IRQn, 0x80);
    
//     // Disable SysTick counter
//     SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    
//     // Set SysTick clock source to the AHB clock (HCLK)
//     SysTick->CTRL |= 1 << SysTick_CTRL_CLKSOURCE_Pos;
    
//     // Set SysTick reload value
//     SysTick->LOAD = (SystemCoreClock/1000 - 1) << SysTick_LOAD_RELOAD_Pos;
    
//     // Clear SysTick current value
//     SysTick->VAL &= ~SysTick_VAL_CURRENT_Msk;
    
//     // Enable SysTick interrupt
//     SysTick->CTRL |= 1 << SysTick_CTRL_TICKINT_Pos;
    
//     // Enable SysTick counter
//     SysTick->CTRL |= 1 << SysTick_CTRL_ENABLE_Pos;
// }
