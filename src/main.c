#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "mpu6050.h"

int main() {
    stdio_init_all();
    mpu6050_init();
    
    mpu6050_data_buff* mpu6050 = malloc(sizeof(mpu6050_data_buff));
    while (true) {
        // mpu6050_get_chip_id(&mpu6050->chip_id);
        // mpu6050_read_temp(&mpu6050->temp);
        // printf("MPU6050 Chip ID: 0x%x \t Temp: %f c\n",mpu6050->chip_id,mpu6050->temp);

        mpu6050_read_accel(&mpu6050->accel);
        mpu6050_print_accel_in_g(mpu6050->accel);
        
        // mpu6050_read_gyro(&mpu6050->gyro);
        // mpu6050_print_angular_velocity(mpu6050->gyro);

        // sleep_ms(1000);
    }
}
