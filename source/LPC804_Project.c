/**
 * @file    LPC804_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include <string.h>  // Added for memset
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC804.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "CS43131_driver.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
 
#define EXAMPLE_I2C_MASTER_BASE     (I2C1_BASE)
#define I2C_MASTER_CLOCK_FREQUENCY  (12000000)
#define WAIT_TIME                   10U
#define EXAMPLE_I2C_MASTER          ((I2C_Type *)EXAMPLE_I2C_MASTER_BASE)

#define EXAMPLE_I2C_SLAVE_BASE      (I2C0_BASE)
#define I2C_SLAVE_CLOCK_FREQUENCY   (12000000)
#define EXAMPLE_I2C_SLAVE           ((I2C_Type *)EXAMPLE_I2C_SLAVE_BASE)

#define I2C_MASTER_SLAVE_ADDR_7BIT  0x7EU
#define I2C_BAUDRATE                100000U
#define I2C_DATA_LENGTH             33U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t g_master_txBuff[I2C_DATA_LENGTH];
uint8_t g_master_rxBuff[I2C_DATA_LENGTH];

/*******************************************************************************
 * Code
 ******************************************************************************/

/*
 * @brief   Application entry point.
 */
int main(void) {
	
    i2c_master_config_t masterConfig;
    i2c_slave_config_t slaveConfig;

    /* Select the main clock as source clock of I2C0 and I2C1. */
    CLOCK_Select(kI2C0_Clk_From_MainClk);
    CLOCK_Select(kI2C1_Clk_From_MainClk);

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    /* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("Hello World\n");

    /* I2C Master configuration for CS43131 communication */
    I2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Bps = I2C_BAUDRATE;
    I2C_MasterInit(EXAMPLE_I2C_MASTER, &masterConfig, I2C_MASTER_CLOCK_FREQUENCY);

    CS43131_Init();

    /* I2C Slave configuration to accept host updates */
    I2C_SlaveGetDefaultConfig(&slaveConfig);
    slaveConfig.address0.address = I2C_MASTER_SLAVE_ADDR_7BIT;
    I2C_SlaveInit(EXAMPLE_I2C_SLAVE, &slaveConfig, I2C_SLAVE_CLOCK_FREQUENCY);

    /* Enter main loop and continuously check for host updates */
    while(1) {
        CS43131_HostUpdate();
        __asm volatile ("nop");
    }

    return 0;
}
