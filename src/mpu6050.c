#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "mpu6050.h"
#include "mpu6050_reg.h"

#define MPU6050_I2C_PORT i2c1
#define MPU6050_I2C_SDA 14
#define MPU6050_I2C_SCL 15

#define MPU6050_ADDRESS 0x69

#define MPU6050_WHO_AM_I_REG 0x75



mpu6050_hal_status mpu6050_init(){
    gpio_set_function(MPU6050_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(MPU6050_I2C_SCL, GPIO_FUNC_I2C);

    i2c_init(MPU6050_I2C_PORT, 100*1000 );

    gpio_pull_up(MPU6050_I2C_SDA);
    gpio_pull_up(MPU6050_I2C_SDA);

    return MPU6050_STATUS_OK;
}

mpu6050_hal_status mpu6050_get_chip_id(uint8_t* buffer){
    uint8_t reg = MPU6050_WHO_AM_I_REG;
    if(i2c_write_blocking(MPU6050_I2C_PORT, MPU6050_ADDRESS, &reg,1,true) <= 0){
        return MPU6050_STATUS_FAILED;
    }
    if(i2c_read_blocking(MPU6050_I2C_PORT, MPU6050_ADDRESS, buffer,1, true) <= 0){
        return MPU6050_STATUS_FAILED;
    }
    return MPU6050_STATUS_OK;
}




