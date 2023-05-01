/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v12.0
processor: LPC804
package_id: LPC804UK
mcu_data: ksdk2_0
processor_version: 13.0.1
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: c875496c-2622-4740-a4a8-22468325e3a6
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system_54b53072540eeeb8f8e9343e71f28176'
- global_system_definitions:
  - user_definitions: ''
  - user_includes: ''
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'uart_cmsis_common'
- type_id: 'uart_cmsis_common_9cb8e302497aa696fdbb5a4fd622c2a8'
- global_USART_CMSIS_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'gpio_adapter_common'
- type_id: 'gpio_adapter_common_57579b9ac814fe26bf95df0a384c36b6'
- global_gpio_adapter_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * I2C0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'I2C0'
- type: 'lpc_i2c'
- mode: 'I2C_Polling'
- custom_name_enabled: 'false'
- type_id: 'lpc_i2c_f5051a0134792729f1007113ec6ddccd'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'I2C0'
- config_sets:
  - fsl_i2c:
    - i2c_mode: 'kI2C_Master'
    - clockSource: 'FunctionClock'
    - clockSourceFreq: 'ClocksTool_DefaultInit'
    - i2c_master_config:
      - enableMaster: 'true'
      - baudRate_Bps: '100000'
      - enableTimeout: 'false'
    - quick_selection: 'QS_I2C_Master'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const i2c_master_config_t I2C0_config = {
  .enableMaster = true,
  .baudRate_Bps = 100000UL,
  .enableTimeout = false
};

static void I2C0_init(void) {
  /* Initialization function */
  I2C_MasterInit(I2C0_PERIPHERAL, &I2C0_config, I2C0_CLOCK_SOURCE);
}

/***********************************************************************************************************************
 * I2C1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'I2C1'
- type: 'lpc_i2c'
- mode: 'I2C_Polling'
- custom_name_enabled: 'false'
- type_id: 'lpc_i2c_f5051a0134792729f1007113ec6ddccd'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'I2C1'
- config_sets:
  - fsl_i2c:
    - i2c_mode: 'kI2C_Master'
    - clockSource: 'FunctionClock'
    - clockSourceFreq: 'ClocksTool_DefaultInit'
    - i2c_master_config:
      - enableMaster: 'true'
      - baudRate_Bps: '100000'
      - enableTimeout: 'false'
    - quick_selection: 'QS_I2C_Master'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const i2c_master_config_t I2C1_config = {
  .enableMaster = true,
  .baudRate_Bps = 100000UL,
  .enableTimeout = false
};

static void I2C1_init(void) {
  /* Initialization function */
  I2C_MasterInit(I2C1_PERIPHERAL, &I2C1_config, I2C1_CLOCK_SOURCE);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Initialize components */
  I2C0_init();
  I2C1_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
