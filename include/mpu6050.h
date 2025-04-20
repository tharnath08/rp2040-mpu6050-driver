#ifndef MPU_6050
#define MPU6050

typedef enum {
    MPU6050_STATUS_OK,
    MPU6050_STATUS_FAILED,
    MPU6050_STATUS_BUSY,
} mpu6050_hal_status;

typedef struct{
    struct accel{
        float x,y,z;
    };
    struct gyro{
        float x,y,z;
    };
    float temp;
    uint8_t chip_id;
} mpu605_data_buff;

mpu6050_hal_status mpu6050_init(void);
mpu6050_hal_status mpu6050_reset(void);
mpu6050_hal_status mpu6050_get_chip_id(uint8_t*);

mpu6050_hal_status mpu6050_read_temp(float*);
mpu6050_hal_status mpu6050_read_accel(float[3]);
mpu6050_hal_status mpu6050_read_gyro(float[3]);


mpu6050_hal_status mpu6050_print_accel_in_g(float[3]);
mpu6050_hal_status mpu6050_print_angular_velocity(float[3]);


#endif