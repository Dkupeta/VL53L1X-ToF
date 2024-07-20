/*
 * vl53l1x_platform_user_data.h
 *
 *  Created on: Jul 20, 2024
 *      Author: dkupe
 */

#ifndef VL53L1X_PLATFORM_USER_DATA_H_
#define VL53L1X_PLATFORM_USER_DATA_H_

// #include "stm32xxx_hal.h"
#include "vl53l1x_def.h"
#ifdef __cplusplus
extern "C"
{
#endif


typedef struct {
    uint32_t dummy;
} I2C_HandleTypeDef;

typedef struct {

	VL53L1_DevData_t   Data;

	uint8_t   I2cDevAddr;
	uint8_t   comms_type;
	uint16_t  comms_speed_khz;
	uint32_t  new_data_ready_poll_duration_ms;
	I2C_HandleTypeDef *I2cHandle;

} VL53L1_Dev_t;

typedef VL53L1_Dev_t *VL53L1_DEV;

#define VL53L1DevDataGet(Dev, field) (Dev->Data.field)
#define VL53L1DevDataSet(Dev, field, VL53L1_PRM_00005) ((Dev->Data.field) = (VL53L1_PRM_00005))
#define VL53L1DevStructGetLLDriverHandle(Dev) (&Dev->Data.LLData)
#define VL53L1DevStructGetLLResultsHandle(Dev) (&Dev->Data.llresults)
#ifdef __cplusplus
}
#endif


#endif /* VL53L1X_PLATFORM_USER_DATA_H_ */
