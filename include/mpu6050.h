#ifndef MPU_6050
#define MPU6050

typedef enum {
    MPU6050_STATUS_OK,
    MPU6050_STATUS_FAILED,
    MPU6050_STATUS_BUSY,
} mpu6050_hal_status;

typedef struct{
    float x,y,z;
}mpu6050_accel_gyro_data;


typedef struct{
    mpu6050_accel_gyro_data accel;
    mpu6050_accel_gyro_data gyro;
    float temp;
    uint8_t chip_id;
} mpu6050_data_buff;

mpu6050_hal_status mpu6050_init(void);
mpu6050_hal_status mpu6050_reset(void);
mpu6050_hal_status mpu6050_get_chip_id(uint8_t*);

mpu6050_hal_status mpu6050_read_temp(float*);
mpu6050_hal_status mpu6050_read_accel(mpu6050_accel_gyro_data*);
mpu6050_hal_status mpu6050_read_gyro(mpu6050_accel_gyro_data*);


mpu6050_hal_status mpu6050_print_accel_in_g(mpu6050_accel_gyro_data);
mpu6050_hal_status mpu6050_print_angular_velocity(mpu6050_accel_gyro_data);


#endif