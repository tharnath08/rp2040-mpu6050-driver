#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "mpu6050.h"

int main() {
    stdio_init_all();
    mpu6050_init();
    uint8_t chipId = 0;

    while (true) {
        mpu6050_get_chip_id(&chipId);
        printf("MPU6050 Chip ID: 0x%x\n",chipId);
        sleep_ms(1000);
    }
}
