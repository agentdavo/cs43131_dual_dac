#include "CS43131_driver.h"
#include <stdint.h>
#include "board.h"
#include "fsl_i2c.h"

#define CS43131_ADDR0                0x30
#define CS43131_ADDR1                0x40

/** function to write I2C bytes to the device with address set in SLAVE_DEVICE_ADDR constant **/
/** Parameters:
        data -> array of bytes to be send via I2C
        len  -> length/number of bytes to be sent
**/
uint32_t write_i2c_data(uint8_t * data, uint8_t len)
{
    uint8_t  buffer[10];

    /* Initialize buffer with packet */
    uint8_t i = 0;
    if(len > 0)
    {
        for(i = 0; i < len; i++)
        {
            buffer[i] = data[i];
        }
    }    


    /* Send master blocking data to slave */
    if (kStatus_Success == I2C_MasterStart(I2C1, CS43131_ADDR0, kI2C_Write))
    {
        /* subAddress = 0x01, data = g_master_txBuff - write to slave.
          start + slaveaddress(w) + subAddress + length of data buffer + data buffer + stop*/
        
        if(kStatus_Success != I2C_MasterWriteBlocking(I2C1, buffer, len, kI2C_TransferDefaultFlag))
        {
            return -1;
        }

        if (kStatus_Success != I2C_MasterStop(I2C1))
        {
            return -1;
        }
    }

    return 0;
}


/** function to read I2C bytes from the device with address set in SLAVE_DEVICE_ADDR constant **/
/** Parameters:
        rec_data -> array which will hold bytes received via I2C
        len      -> length/number of bytes to be received
**/
uint32_t read_i2c_data(uint8_t *command, uint8_t * rec_data, uint8_t len)
{


    if (kStatus_Success == I2C_MasterStart(I2C1, CS43131_ADDR0, kI2C_Write))
    {
        if (kStatus_Success != I2C_MasterWriteBlocking(I2C1, command, 4, kI2C_TransferNoStopFlag))
        {
            return -1;
        }

        if (kStatus_Success !=  I2C_MasterRepeatedStart(I2C1, CS43131_ADDR0, kI2C_Read))
        {
            return -1;
        }

        
        if (kStatus_Success != I2C_MasterReadBlocking(I2C1, rec_data, len, kI2C_TransferDefaultFlag))
        {
            return -1;
        }

        
        if (kStatus_Success != I2C_MasterStop(I2C1))
        {
            return -1;
        }
    }


    return 0;
}

/**************************************** Code for DAC Functions **********************************************/


uint8_t CS43131_Read(uint32_t reg) {
    uint8_t tx_payload[4];
    uint8_t rx_val; 
    tx_payload[0] = (reg >> 16) & 0xff;                         // Register address
    tx_payload[1] = (reg >> 8) & 0xff;
    tx_payload[2] = (reg) & 0xff;
    tx_payload[3] = 0x00;                                       // Control byte
    // write_i2c_data(tx_payload, 4);                           //write the register from which data need to be read
    read_i2c_data(tx_payload,&rx_val, 1);
    return rx_val;
}

void CS43131_Write(uint32_t reg, uint8_t val) {
    uint8_t tx_payload[5];
    tx_payload[0] = (reg >> 16) & 0xff;                         // Register address
    tx_payload[1] = (reg >> 8) & 0xff;
    tx_payload[2] = (reg) & 0xff;
    tx_payload[3] = 0x00;                                       // Control byte
    tx_payload[4] = val;                                        // Register value
    write_i2c_data(tx_payload, 5);
    
}

void CS43131_PCM_PowerUp() {
    CS43131_Write(0x10010,   0x99);                             //  Pop-free power-up settings
    CS43131_Write(0x80032,   0x20);
    CS43131_Write(0x20000,   CS43131_Read(0x20000) & 0xBF);     //  Power up ASP
    CS43131_Write(0x20000,   CS43131_Read(0x20000) & 0xEF);     //  Power up HP
    // insert wait 12ms
    CS43131_Write(0x80032, 0x00);                               //  Restore default settings
    CS43131_Write(0x10010, 0x00); 
}

void CS43131_PCM_PowerDown() {
    CS43131_Write(0x20000, CS43131_Read(0x20000) | 0x10);   //  Enable PDN_DONE interrupt
    while (!(CS43131_Read(0xF0000) & 0x01));                //  Read Interrupt Status 1 register 
    CS43131_Write(0x20000, CS43131_Read(0x20000) | 0x40);   //  Power down ASP
}

void CS43131_Reset() {
   // assert DAC_REST_PIN C3 for 50ms
}

void CS43131_Init() {

    // PLL setup

    CS43131_Write(0x20000,   0xF2);   //  Power up PLL
    CS43131_Write(0x40002,   0x02);   //  Set PLL_REF_PREDIV to 4
    CS43131_Write(0x30008,   0x08);   //  Set PLL_OUT_DIV to 8
    CS43131_Write(0x30002,   0x01);   //  Set PLL_DIV_FRAC_0 
    CS43131_Write(0x30003,   0x00);   //  Set PLL_DIV_FRAC_1
    CS43131_Write(0x30004,   0x00);   //  Set PLL_DIV_FRAC_3
    CS43131_Write(0x30005,   0x40);   //  Set PLL_DIV_INT
    CS43131_Write(0x3001B,   0x13);   //  Set PLL_MODE
    CS43131_Write(0x3000A,   0x80);   //  Set PLL_CAL_RATIO
    CS43131_Read( 0xF0000);           //  Read Interrupt Status 1 register to clear any pending interrupts 
    CS43131_Write(0xF0010,   0xE1);   //  Enable PLL Interrupts : PLL_READY and PLL_ERROR
    CS43131_Write(0x30001,   0x01);   //  Start PLL

    // ASP setup

    CS43131_Write(0x1000A,   0x04);   //  Set ASP Sample Rate to 96kHz
    CS43131_Write(0x1000C,   0x04);   //  Set ASP Sample Bit Size to 32bits
    CS43131_Write(0x40010,   0x28);   //  Set ASP Numerator LSB to 40
    CS43131_Write(0x40011,   0x00);   //  Set ASP Numerator MSB to 0
    CS43131_Write(0x40012,   0x93);   //  Set ASP Denominator LSB to 147
    CS43131_Write(0x40013,   0x00);   //  Set ASP Denominator MSB to 0 
    CS43131_Write(0x40014,   0x1F);   //  Set ASP LRCK High Time LSB to 31
    CS43131_Write(0x40015,   0x00);   //  Set ASP LRCK High Time MSB to 0
    CS43131_Write(0x40016,   0x3F);   //  Set ASP LRCK Period LSB to 63
    CS43131_Write(0x40017,   0x00);   //  Set ASP LRCK Period MSB to 0 
    CS43131_Write(0x40018,   0x1C);   //  Set ASP Clock Configuration
    CS43131_Write(0x40019,   0x0A);   //  Set ASP Frame Configuration
    CS43131_Write(0x50000,   0x00);   //  Set ASP Channel 1 Location
    CS43131_Write(0x50001,   0x00);   //  Set ASP Channel 2 Location
    CS43131_Write(0x5000A,   0x0F);   //  Set ASP Channel 1 Size and Enable
    CS43131_Write(0x5000B,   0x0F);   //  Set ASP Channel 1 Size and Enable

    // PCM Setup

    CS43131_Write(0x90000,   0x02);   //  Configure PCM Filter Option to select High Pass Filter
    CS43131_Write(0x90001,   0x00);   //  Set PCM Volume for Channel B to 0dB
    CS43131_Write(0x90002,   0x00);   //  Set PCM Volume for Channel A to 0dB
    CS43131_Write(0x90003,   0xEC);   //  Configure PCM Path Signal Control1
    CS43131_Write(0x90004,   0x00);   //  Configure PCM Path Signal Control2

    // HP Setup
    
    CS43131_Write(0xB0000,   0x1E);   //  Configure Class-H control
    CS43131_Write(0x80000,   0x30);   //  Set HP output to 2.0V
    CS43131_Write(0xD0000,   0x04);   //  Configure HPDETECT parameters
    CS43131_Write(0xF0011,   0x07);   //  Enable HPDETECT 

    // Wait for PLL to be ready
    while (!(CS43131_Read(0xF0000) & 0x10)) {
    }

    // Mono Mode

    CS43131_Write(0x180009,   0x2F);
    CS43131_Write(0x18000A,   0xB4);
    CS43131_Write(0x18000B,   0x25);
    CS43131_Write(0x18000C,   0x80);
    CS43131_Write(0x18000F,   0x55);
    CS43131_Write(0x180010,   0xFA);
    CS43131_Write(0x180019,   0x2F);
    CS43131_Write(0x18001A,   0xB4);
    CS43131_Write(0x18001B,   0x25);
    CS43131_Write(0x18001C,   0x80);
    CS43131_Write(0x18001F,   0x4E);
    CS43131_Write(0x180020,   0xFD);
    CS43131_Write(0x180029,   0x2F);
    CS43131_Write(0x18002A,   0xB4);
    CS43131_Write(0x18002B,   0x25);
    CS43131_Write(0x18002C,   0x80);
    CS43131_Write(0x18002F,   0x7C);
    CS43131_Write(0x180030,   0xFD);
    CS43131_Write(0x180039,   0x2F);
    CS43131_Write(0x18003A,   0xB4);
    CS43131_Write(0x18003B,   0x25);
    CS43131_Write(0x18003C,   0x80);
    CS43131_Write(0x18003F,   0x52);
    CS43131_Write(0x180040,   0xFE);


    // Filters

    CS43131_Write(0x9000A,   0x00);    //  Programmable Filter Control 1
    CS43131_Write(0x9000B,   0x00);    //  Programmable Filter Control 2

    CS43131_Write(0x9000C,   0x00);    //  SOS1_COEFF_B0_LSBYTE
    CS43131_Write(0x9000D,   0x00);    //  SOS1_COEFF_B0_MSBYTE
    CS43131_Write(0x9000E,   0x00);    //  SOS1_COEFF_B0_SIGN
    CS43131_Write(0x9000F,   0x00);    //  SOS1_COEFF_B1_LSBYTE
    CS43131_Write(0x90010,   0x00);    //  SOS1_COEFF_B1_MSBYTE
    CS43131_Write(0x90011,   0x00);    //  SOS1_COEFF_B1_SIGN
    CS43131_Write(0x90012,   0x00);    //  SOS1_COEFF_B2_LSBYTE
    CS43131_Write(0x90013,   0x00);    //  SOS1_COEFF_B2_MSBYTE
    CS43131_Write(0x90014,   0x00);    //  SOS1_COEFF_B2_SIGN
    CS43131_Write(0x90015,   0x00);    //  SOS1_COEFF_A1_LSBYTE
    CS43131_Write(0x90016,   0x00);    //  SOS1_COEFF_A1_MSBYTE
    CS43131_Write(0x90017,   0x00);    //  SOS1_COEFF_A1_SIGN
    CS43131_Write(0x90018,   0x00);    //  SOS1_COEFF_A2_LSBYTE
    CS43131_Write(0x90019,   0x00);    //  SOS1_COEFF_A2_MSBYTE
    CS43131_Write(0x9001A,   0x00);    //  SOS1_COEFF_A2_SIGN

    CS43131_Write(0x9001B,   0x00);    //  SOS2_COEFF_B0_LSBYTE
    CS43131_Write(0x9001C,   0x00);    //  SOS2_COEFF_B0_MSBYTE
    CS43131_Write(0x9001D,   0x00);    //  SOS2_COEFF_B0_SIGN
    CS43131_Write(0x9001E,   0x00);    //  SOS2_COEFF_B1_LSBYTE
    CS43131_Write(0x9001F,   0x00);    //  SOS2_COEFF_B1_MSBYTE
    CS43131_Write(0x90020,   0x00);    //  SOS2_COEFF_B1_SIGN
    CS43131_Write(0x90021,   0x00);    //  SOS2_COEFF_B2_LSBYTE
    CS43131_Write(0x90022,   0x00);    //  SOS2_COEFF_B2_MSBYTE
    CS43131_Write(0x90023,   0x00);    //  SOS2_COEFF_B2_SIGN
    CS43131_Write(0x90024,   0x00);    //  SOS2_COEFF_A1_LSBYTE
    CS43131_Write(0x90025,   0x00);    //  SOS2_COEFF_A1_MSBYTE
    CS43131_Write(0x90026,   0x00);    //  SOS2_COEFF_A1_SIGN
    CS43131_Write(0x90027,   0x00);    //  SOS2_COEFF_A2_LSBYTE
    CS43131_Write(0x90028,   0x00);    //  SOS2_COEFF_A2_MSBYTE
    CS43131_Write(0x90029,   0x00);    //  SOS2_COEFF_A2_SIGN

    CS43131_Write(0x9002A,   0x00);    //  SOS3_COEFF_B0_LSBYTE
    CS43131_Write(0x9002B,   0x00);    //  SOS3_COEFF_B0_MSBYTE
    CS43131_Write(0x9002C,   0x00);    //  SOS3_COEFF_B0_SIGN
    CS43131_Write(0x9002D,   0x00);    //  SOS3_COEFF_B1_LSBYTE
    CS43131_Write(0x9002E,   0x00);    //  SOS3_COEFF_B1_MSBYTE
    CS43131_Write(0x9002F,   0x00);    //  SOS3_COEFF_B1_SIGN
    CS43131_Write(0x90030,   0x00);    //  SOS3_COEFF_B2_LSBYTE
    CS43131_Write(0x90031,   0x00);    //  SOS3_COEFF_B2_MSBYTE
    CS43131_Write(0x90032,   0x00);    //  SOS3_COEFF_B2_SIGN
    CS43131_Write(0x90033,   0x00);    //  SOS3_COEFF_A1_LSBYTE
    CS43131_Write(0x90034,   0x00);    //  SOS3_COEFF_A1_MSBYTE
    CS43131_Write(0x90035,   0x00);    //  SOS3_COEFF_A1_SIGN
    CS43131_Write(0x90036,   0x00);    //  SOS3_COEFF_A2_LSBYTE
    CS43131_Write(0x90037,   0x00);    //  SOS3_COEFF_A2_MSBYTE
    CS43131_Write(0x90038,   0x00);    //  SOS3_COEFF_A2_SIGN

    CS43131_Write(0x90039,   0x00);    //  FOS_COEFF_B0_LSBYTE
    CS43131_Write(0x9003A,   0x00);    //  FOS_COEFF_B0_MSBYTE
    CS43131_Write(0x9003B,   0x00);    //  FOS_COEFF_B0_SIGN
    CS43131_Write(0x9003C,   0x00);    //  FOS_COEFF_B1_LSBYTE
    CS43131_Write(0x9003D,   0x00);    //  FOS_COEFF_B1_MSBYTE
    CS43131_Write(0x9003E,   0x00);    //  FOS_COEFF_B1_SIGN
    CS43131_Write(0x9003F,   0x00);    //  FOS_COEFF_A1_LSBYTE
    CS43131_Write(0x90040,   0x00);    //  FOS_COEFF_A1_MSBYTE
    CS43131_Write(0x90041,   0x00);    //  FOS_COEFF_A1_SIGN


    // Enable system

    CS43131_Write(0x10006,   0x01);    //  MCLK Source is PLL, Frequency = 24.576MHz
    CS43131_Write(0x20000,   0xF4);
    CS43131_Write(0x1000D,   0x02);    //  Enable Audio clock output 
    CS43131_PCM_PowerUp();
}

void CS43131_HostUpdate()
{
    uint8_t buffer[5];
    uint32_t reg=0;
    uint8_t val = 0;
    memset(buffer, 0, sizeof(buffer));

    /* Start accepting I2C transfers on the I2C slave peripheral */
    
    if (kStatus_Success != I2C_SlaveReadBlocking(I2C0, buffer, 5))
    {
        val = buffer[4];
        reg = (buffer[0] << (8 * 2)) | (buffer[1] << (8*1)) | (buffer[2] <<(8*0));
        CS43131_Write(reg, val);
    }

}

