#include "hal_bsp_ap3216c.h"
#include <hi_i2c.h>
#include <hi_gpio.h>
#include <unistd.h>

// I2C 0
#define I2C_IDX HI_I2C_IDX_0

// I2C写1字节
static uint8_t I2C_WriteReg(uint8_t devAddr, uint8_t reg, uint8_t data)
{
    hi_i2c_data i2cData;
    uint8_t buf[2] = {reg, data};
    i2cData.send_buf = buf;
    i2cData.send_len = 2;
    return hi_i2c_write(I2C_IDX, devAddr, &i2cData);
}

// I2C读多字节
static uint8_t I2C_ReadRegs(uint8_t devAddr, uint8_t reg, uint8_t *buf, uint8_t len)
{
    hi_i2c_data i2cData;
    i2cData.send_buf = &reg;
    i2cData.send_len = 1;
    i2cData.receive_buf = buf;
    i2cData.receive_len = len;
    // 修复：hi_i2c_writeread，不要中间下划线
    return hi_i2c_writeread(I2C_IDX, devAddr, &i2cData);
}

uint8_t AP3216C_Init(void)
{
    hi_i2c_init(I2C_IDX, 400000);
    usleep(50000);
    // 模式0x03：ALS+PS开启
    if(I2C_WriteReg(AP3216C_ADDR, AP3216C_SYSTEM, 0x03) != HI_ERR_SUCCESS)
    {
        return 1;
    }
    usleep(100000);
    return 0;
}

// 读取光照ALS
uint16_t AP3216C_Read_ALS(void)
{
    uint8_t tmp[2];
    I2C_ReadRegs(AP3216C_ADDR, AP3216C_ALS, tmp, 2);
    return (tmp[1] << 8) | tmp[0];
}

// 读取接近PS
uint16_t AP3216C_Read_PS(void)
{
    uint8_t tmp[2];
    I2C_ReadRegs(AP3216C_ADDR, AP3216C_PS, tmp, 2);
    return (tmp[1] << 8) | tmp[0];
}

