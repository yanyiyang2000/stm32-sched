/* CMSIS Device API */
#include "stm32l476xx.h"
#include "system_stm32l4xx.h"

/* CMSIS Core API */
#include "core_cm4.h"

/* User API */
#include "msi_config.h"


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
