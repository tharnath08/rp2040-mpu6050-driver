#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "mpu6050.h"

int main() {
    stdio_init_all();
    mpu6050_init();
    uint8_t chipId = 0;
    float temp = 0;
    int16_t accel[3];
    while (true) {
        // mpu6050_get_chip_id(&chipId);
        // mpu6050_read_temp(&temp);
        // printf("MPU6050 Chip ID: 0x%x \t Temp: %f c\n",chipId,temp);
        
        mpu6050_read_accel(&accel);
        mpu6050_print_accel_in_g(accel);


        // sleep_ms(1000);
    }
}
