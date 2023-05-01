/*
 * How to set up clock using clock driver functions:
 *
 * 1. Setup clock sources.
 *
 * 2. Set up all dividers.
 *
 * 3. Set up all selectors to provide selected clocks.
 */

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Clocks v11.0
processor: LPC804
package_id: LPC804UK
mcu_data: ksdk2_0
processor_version: 13.0.1
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

#include "fsl_power.h"
#include "fsl_clock.h"
#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
    BOARD_BootClockRUN();
}

/*******************************************************************************
 ********************** Configuration BOARD_BootClockRUN ***********************
 ******************************************************************************/
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockRUN
called_from_default_init: true
outputs:
- {id: FROHF_clock.outFreq, value: 30 MHz}
- {id: I2C0_clock.outFreq, value: 15 MHz}
- {id: I2C1_clock.outFreq, value: 15 MHz}
- {id: LowPower_clock.outFreq, value: 1 MHz}
- {id: System_clock.outFreq, value: 15 MHz}
- {id: WWDT_clock.outFreq, value: 1 MHz}
- {id: divto750k_clock.outFreq, value: 750 kHz}
settings:
- {id: SYSCON.I2C0CLKSEL.sel, value: SYSCON.MAINCLKSEL}
- {id: SYSCON.I2C1CLKSEL.sel, value: SYSCON.MAINCLKSEL}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/*******************************************************************************
 * Variables for BOARD_BootClockRUN configuration
 ******************************************************************************/
/*******************************************************************************
 * Code for BOARD_BootClockRUN configuration
 ******************************************************************************/
void BOARD_BootClockRUN(void)
{
    /*!< Set up the clock sources */
    /*!< Set up FRO */
    POWER_DisablePD(kPDRUNCFG_PD_FRO_OUT);                   /*!< Ensure FRO OUT is on  */
    POWER_DisablePD(kPDRUNCFG_PD_FRO);                      /*!< Ensure FRO is on  */
    CLOCK_SetFroOscFreq(kCLOCK_FroOscOut30M);                    /*!< Set up FRO freq */
    POWER_DisablePD(kPDRUNCFG_PD_LPOSC);                  /*!< Ensure LPOSC is on */
    CLOCK_SetMainClkSrc(kCLOCK_MainClkSrcFro);            /*!< select fro for main clock */
    CLOCK_Select(kFRG0_Clk_From_Fro);                     /*!< select fro for frg0 */
    CLOCK_SetFRG0ClkFreq(15000000U);                     /*!< select frg0 freq */
    CLOCK_Select(kCLKOUT_From_Fro);                         /*!< select FRO for CLKOUT */
    CLOCK_Select(kADC_Clk_From_Fro);                       /*!< select FRO for ADC */
    CLOCK_Select(kI2C0_Clk_From_MainClk);                  /*!< select main clk for I2C0 */
    CLOCK_Select(kI2C1_Clk_From_MainClk);                  /*!< select main clk for I2C1 */
    CLOCK_SetCoreSysClkDiv(1U);
    /*!< Set SystemCoreClock variable. */
    SystemCoreClock = BOARD_BOOTCLOCKRUN_CORE_CLOCK;
}

