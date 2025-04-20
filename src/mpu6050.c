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

    mpu6050_reset();

    return MPU6050_STATUS_OK;
}

mpu6050_hal_status mpu6050_reset(){

    uint8_t reg[] = {MPU6050_PWR_MGMT_1_REG, 0x80};

    if(i2c_write_blocking(MPU6050_I2C_PORT, MPU6050_ADDRESS, reg,2,true) <= 0){
        return MPU6050_STATUS_FAILED;
    }
    sleep_ms(100);

    reg[1] = 0x00;
    if(i2c_write_blocking(MPU6050_I2C_PORT, MPU6050_ADDRESS, reg,2,false) <= 0){
        return MPU6050_STATUS_FAILED;
    }

    return MPU6050_STATUS_OK;
}

mpu6050_hal_status mpu6050_get_chip_id(uint8_t* buffer){
    uint8_t reg[] = {MPU6050_WHO_AM_I_REG};
    if(i2c_write_blocking(MPU6050_I2C_PORT, MPU6050_ADDRESS, reg,1,true) <= 0){
        return MPU6050_STATUS_FAILED;
    }
    if(i2c_read_blocking(MPU6050_I2C_PORT, MPU6050_ADDRESS, buffer,1, false) <= 0){
        return MPU6050_STATUS_FAILED;
    }
    return MPU6050_STATUS_OK;
}

mpu6050_hal_status mpu6050_read_temp(float* temp){
    uint8_t reg[] = {TEMP_OUT_H};
    uint8_t buffer[2];
    if(i2c_write_blocking(MPU6050_I2C_PORT, MPU6050_ADDRESS, reg,1,true) <= 0){
        return MPU6050_STATUS_FAILED;
    }
    if(i2c_read_blocking(MPU6050_I2C_PORT, MPU6050_ADDRESS, buffer,2, false) <= 0){
        return MPU6050_STATUS_FAILED;
    }

    *temp = buffer[0] << 8 | buffer[1];

    *temp = ((*temp) / 340)+36.53;

    return MPU6050_STATUS_OK;
}



mpu6050_hal_status mpu6050_read_accel(int16_t accel[3]){

    uint8_t buffer[6];
    uint8_t reg[] = {ACCEL_XOUT_H};

    if(i2c_write_blocking(MPU6050_I2C_PORT, MPU6050_ADDRESS, reg,1,true) <= 0){
        return MPU6050_STATUS_FAILED;
    }
    if(i2c_read_blocking(MPU6050_I2C_PORT, MPU6050_ADDRESS, buffer,6, false) <= 0){
        return MPU6050_STATUS_FAILED;
    }

    for(int i=0; i<3; i++){
        accel[i] = buffer[i*2]<<8 | buffer[(i*2)+1];
    }

    return MPU6050_STATUS_OK;
}



mpu6050_hal_status mpu6050_print_accel_in_g(int16_t accel[3]){
    printf("Accel x: %f \t ", accel[0]/16384.0f);
    printf("y: %f \t ", accel[1]/16384.0f);
    printf("z: %f \n ", accel[2]/16384.0f);
    return MPU6050_STATUS_OK;
}

