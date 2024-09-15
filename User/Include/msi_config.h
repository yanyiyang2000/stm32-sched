#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

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
void MSI_config();

#endif /* CLOCK_CONFIG_H */
