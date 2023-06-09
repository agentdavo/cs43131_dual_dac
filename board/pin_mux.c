/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v13.1
processor: LPC804
package_id: LPC804UK
mcu_data: ksdk2_0
processor_version: 13.0.1
pin_labels:
- {pin_num: B1, pin_signal: SWCLK/PIO0_3, label: swclk, identifier: swclk}
- {pin_num: B2, pin_signal: SWDIO/PIO0_2, label: swdio, identifier: swdio}
- {pin_num: D3, pin_signal: PIO0_0/ACMP_I1, label: i2c0_scl_host, identifier: i2c0_scl_host}
- {pin_num: A4, pin_signal: PIO0_1/ADC_0/ACMP_I2/CLKIN, label: i2c0_sda_host, identifier: i2c0_sda_host}
- {pin_num: A2, pin_signal: PIO0_10/ADC_7, label: i2c1_scl_dac, identifier: i2c1_scl_dac}
- {pin_num: A1, pin_signal: PIO0_11/ADC_6/WKTCLKIN, label: i2c1_sda_dac, identifier: i2c1_sda_dac}
- {pin_num: A3, pin_signal: PIO0_15/ADC_8, label: i2c0_scl_host, identifier: i2c0_scl_host}
- {pin_num: E3, pin_signal: PIO0_14/ACMP_I3/ADC_2, label: dac_reset_in, identifier: dac_reset_in}
- {pin_num: E1, pin_signal: PIO0_17/ADC_9, label: dac_reset_out, identifier: dac_reset_out}
- {pin_num: C1, pin_signal: RESETN/PIO0_5, label: resetn, identifier: resetn}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_swm.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true', fullInit: 'true'}
- pin_list:
  - {pin_num: B1, peripheral: SWD, signal: SWCLK, pin_signal: SWCLK/PIO0_3, direction: INPUT, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled}
  - {pin_num: B2, peripheral: SWD, signal: SWDIO, pin_signal: SWDIO/PIO0_2, direction: INPUT, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled}
  - {pin_num: A2, peripheral: I2C1, signal: SCL, pin_signal: PIO0_10/ADC_7, direction: INPUT, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled}
  - {pin_num: A1, peripheral: I2C1, signal: SDA, pin_signal: PIO0_11/ADC_6/WKTCLKIN, direction: INPUT, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled}
  - {pin_num: A4, peripheral: I2C0, signal: SCL, pin_signal: PIO0_1/ADC_0/ACMP_I2/CLKIN, direction: INPUT, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled}
  - {pin_num: A3, peripheral: I2C0, signal: SDA, pin_signal: PIO0_15/ADC_8, direction: INPUT, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled}
  - {pin_num: E3, peripheral: LVLSHFT, signal: 'IN, 0', pin_signal: PIO0_14/ACMP_I3/ADC_2, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled}
  - {pin_num: E1, peripheral: LVLSHFT, signal: 'OUT, 0', pin_signal: PIO0_17/ADC_9, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled}
  - {pin_num: C1, peripheral: SYSCON, signal: RESETN, pin_signal: RESETN/PIO0_5, mode: pullUp, invert: disabled, hysteresis: enabled, opendrain: disabled}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M0P */
void BOARD_InitPins(void)
{
    /* Enables clock for IOCON.: enable */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables clock for switch matrix.: enable */
    CLOCK_EnableClock(kCLOCK_Swm);

    const uint32_t i2c0_sda_host = (/* Selects pull-up function */
                                    IOCON_PIO_MODE_PULLUP |
                                    /* Enable hysteresis */
                                    IOCON_PIO_HYS_EN |
                                    /* Input not invert */
                                    IOCON_PIO_INV_DI |
                                    /* Disables Open-drain function */
                                    IOCON_PIO_OD_DI);
    /* PIO0 PIN1 (coords: A4) is configured as I2C0, SCL. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_1, i2c0_sda_host);

    const uint32_t i2c1_scl_dac = (/* Selects pull-up function */
                                   IOCON_PIO_MODE_PULLUP |
                                   /* Enable hysteresis */
                                   IOCON_PIO_HYS_EN |
                                   /* Input not invert */
                                   IOCON_PIO_INV_DI |
                                   /* Disables Open-drain function */
                                   IOCON_PIO_OD_DI);
    /* PIO0 PIN10 (coords: A2) is configured as I2C1, SCL. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_10, i2c1_scl_dac);

    const uint32_t i2c1_sda_dac = (/* Selects pull-up function */
                                   IOCON_PIO_MODE_PULLUP |
                                   /* Enable hysteresis */
                                   IOCON_PIO_HYS_EN |
                                   /* Input not invert */
                                   IOCON_PIO_INV_DI |
                                   /* Disables Open-drain function */
                                   IOCON_PIO_OD_DI);
    /* PIO0 PIN11 (coords: A1) is configured as I2C1, SDA. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_11, i2c1_sda_dac);

    const uint32_t dac_reset_in = (/* Selects pull-up function */
                                   IOCON_PIO_MODE_PULLUP |
                                   /* Enable hysteresis */
                                   IOCON_PIO_HYS_EN |
                                   /* Input not invert */
                                   IOCON_PIO_INV_DI |
                                   /* Disables Open-drain function */
                                   IOCON_PIO_OD_DI);
    /* PIO0 PIN14 (coords: E3) is configured as LVLSHFT, IN, 0. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_14, dac_reset_in);

    const uint32_t i2c0_scl_host = (/* Selects pull-up function */
                                    IOCON_PIO_MODE_PULLUP |
                                    /* Enable hysteresis */
                                    IOCON_PIO_HYS_EN |
                                    /* Input not invert */
                                    IOCON_PIO_INV_DI |
                                    /* Disables Open-drain function */
                                    IOCON_PIO_OD_DI);
    /* PIO0 PIN15 (coords: A3) is configured as I2C0, SDA. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_15, i2c0_scl_host);

    const uint32_t dac_reset_out = (/* Selects pull-up function */
                                    IOCON_PIO_MODE_PULLUP |
                                    /* Enable hysteresis */
                                    IOCON_PIO_HYS_EN |
                                    /* Input not invert */
                                    IOCON_PIO_INV_DI |
                                    /* Disables Open-drain function */
                                    IOCON_PIO_OD_DI);
    /* PIO0 PIN17 (coords: E1) is configured as LVLSHFT, OUT, 0. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_17, dac_reset_out);

    const uint32_t swdio = (/* Selects pull-up function */
                            IOCON_PIO_MODE_PULLUP |
                            /* Enable hysteresis */
                            IOCON_PIO_HYS_EN |
                            /* Input not invert */
                            IOCON_PIO_INV_DI |
                            /* Disables Open-drain function */
                            IOCON_PIO_OD_DI);
    /* PIO0 PIN2 (coords: B2) is configured as SWD, SWDIO. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_2, swdio);

    const uint32_t swclk = (/* Selects pull-up function */
                            IOCON_PIO_MODE_PULLUP |
                            /* Enable hysteresis */
                            IOCON_PIO_HYS_EN |
                            /* Input not invert */
                            IOCON_PIO_INV_DI |
                            /* Disables Open-drain function */
                            IOCON_PIO_OD_DI);
    /* PIO0 PIN3 (coords: B1) is configured as SWD, SWCLK. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_3, swclk);

    const uint32_t resetn = (/* Selects pull-up function */
                             IOCON_PIO_MODE_PULLUP |
                             /* Enable hysteresis */
                             IOCON_PIO_HYS_EN |
                             /* Input not invert */
                             IOCON_PIO_INV_DI |
                             /* Disables Open-drain function */
                             IOCON_PIO_OD_DI);
    /* PIO0 PIN5 (coords: C1) is configured as SYSCON, RESETN. */
    IOCON_PinMuxSet(IOCON, IOCON_INDEX_PIO0_5, resetn);

    /* I2C0_SDA connect to P0_15 */
    SWM_SetMovablePinSelect(SWM0, kSWM_I2C0_SDA, kSWM_PortPin_P0_15);

    /* I2C0_SCL connect to P0_1 */
    SWM_SetMovablePinSelect(SWM0, kSWM_I2C0_SCL, kSWM_PortPin_P0_1);

    /* LVLSHFT_IN0 connect to P0_14 */
    SWM_SetMovablePinSelect(SWM0, kSWM_LVLSHFT_IN0, kSWM_PortPin_P0_14);

    /* LVLSHFT_OUT0 connect to P0_17 */
    SWM_SetMovablePinSelect(SWM0, kSWM_LVLSHFT_OUT0, kSWM_PortPin_P0_17);

    /* I2C1_SDA connect to P0_11 */
    SWM_SetMovablePinSelect(SWM0, kSWM_I2C1_SDA, kSWM_PortPin_P0_11);

    /* I2C1_SCL connect to P0_10 */
    SWM_SetMovablePinSelect(SWM0, kSWM_I2C1_SCL, kSWM_PortPin_P0_10);

    /* SWCLK connect to P0_3 */
    SWM_SetFixedPinSelect(SWM0, kSWM_SWCLK, true);

    /* SWDIO connect to P0_2 */
    SWM_SetFixedPinSelect(SWM0, kSWM_SWDIO, true);

    /* RESETN connect to P0_5 */
    SWM_SetFixedPinSelect(SWM0, kSWM_RESETN, true);

    /* Disable clock for switch matrix. */
    CLOCK_DisableClock(kCLOCK_Swm);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
