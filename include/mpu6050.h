#ifndef MPU_6050
#define MPU6050

typedef enum {
    MPU6050_STATUS_OK,
    MPU6050_STATUS_FAILED,
    MPU6050_STATUS_BUSY,
} mpu6050_hal_status;


mpu6050_hal_status mpu6050_init(void);
mpu6050_hal_status mpu6050_reset(void);
mpu6050_hal_status mpu6050_get_chip_id(uint8_t*);

mpu6050_hal_status mpu6050_read_temp(float*);
mpu6050_hal_status mpu6050_read_accel(int16_t[3]);


mpu6050_hal_status mpu6050_print_accel_in_g(int16_t[3]);


#endif