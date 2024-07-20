/*
 * vl53l1x_api_calibration.h
 *
 *  Created on: Jul 20, 2024
 *      Author: dkupe
 */

#ifndef VL53L1X_API_CALIBRATION_H_
#define VL53L1X_API_CALIBRATION_H_

#include "vl53l1x_platform.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Run Reference Array SPAD Characterisation.
 *
 * This function finds the required number of reference SPAD
 * to meet the input required peak reference rate.
 *
 * The algorithm first tries the non apertured reference SPAD's,
 * if the rate is too high for the minimum allowed SPAD count (5)
 * then the algo switches to 5x apertured SPAD's and if the rate
 * is still to high then the 10x apertured SPAD are selected.
 *
 * The function reads the following results from the device and
 * both caches the values in the pdev->customer structure and
 * writes the data into the G02 customer register group.
 *
 * - num_ref_spads
 * - ref_location
 * - DCR SPAD enables for selected reference location
 *
 * Note power force is enabled as the function needs to read
 * data from the Patch RAM.
 *
 * Should only be called once per part with coverglass attached to
 * generate the required num of SPAD, Ref location and DCR SPAD enable
 * data
 *
 * @param[in]   Dev           : Device Handle
 * @param[out]  pcal_status   : Pointer to unfiltered calibration status
 *
 * @return  VL53L1_ERROR_NONE     Success
 * @return  VL53L1_WARNING_REF_SPAD_CHAR_NOT_ENOUGH_SPADS
 *                                Less than 5 Good SPAD available, output not valid
 * @return  VL53L1_WARNING_REF_SPAD_CHAR_RATE_TOO_HIGH
 *                                At end of search reference rate > 40.0 Mcps
 *                                Offset stability may be degraded.
 * @return  VL53L1_WARNING_REF_SPAD_CHAR_RATE_TOO_LOW
 *                                At end of search reference rate < 10.0 Mcps
 *                                Offset stability may be degraded.
 *
 */

#ifndef VL53L1_NOCALIB
VL53L1_Error VL53L1_run_ref_spad_char(VL53L1_DEV Dev, VL53L1_Error *pcal_status);
#endif


/**
 * @brief Runs the input Device Test
 *
 * Calls
 *
 * - VL53L1_enable_powerforce()
 * - VL53L1_start_test()
 * - VL53L1_poll_for_range_completion()
 *
 * @param[in]   Dev                      : Device handle
 * @param[in]   device_test_mode         : Device test mode register value
 *
 * @return  VL53L1_ERROR_NONE     Success
 * @return  "Other error code"    See ::VL53L1_Error
 */

#ifndef VL53L1_NOCALIB
VL53L1_Error VL53L1_run_device_test(
	VL53L1_DEV                 Dev,
	VL53L1_DeviceTestMode      device_test_mode);
#endif


/**
 * @brief Runs SPAD rate map
 *
 * Output structure contains SPAD rate data in SPAD number order
 *
 * @param[in]   Dev                 : Device handle
 * @param[in]   device_test_mode    : Device test mode register value.
 *                                    Valid options: \n
 *                                    - VL53L1_DEVICETESTMODE_LCR_VCSEL_OFF \n
 *                                    - VL53L1_DEVICETESTMODE_LCR_VCSEL_ON
 * @param[in]   array_select          : Device SPAD array select
 *                                      Valid options: \n
 *                                       - VL53L1_DEVICESSCARRAY_RTN \n
 *                                       - VL53L1_DEVICESSCARRAY_REF
 * @param[in]   ssc_config_timeout_us : SSC timeout in [us] e.g 36000us
 * @param[out]  pspad_rate_data       : pointer to output rates structure
 *                                      1.15 format for LCR_VCSEL_OFF
 *                                       9.7  format for LCR_VCSEL_ON
 *
 * @return  VL53L1_ERROR_NONE     Success
 * @return  "Other error code"    See ::VL53L1_Error
 */

#ifndef VL53L1_NOCALIB
VL53L1_Error VL53L1_run_spad_rate_map(
	VL53L1_DEV                 Dev,
	VL53L1_DeviceTestMode      device_test_mode,
	VL53L1_DeviceSscArray      array_select,
	uint32_t                   ssc_config_timeout_us,
	VL53L1_spad_rate_data_t   *pspad_rate_data);
#endif


/**
 * @brief Run offset calibration
 *
 * Runs the standard ranging MM1 and MM2 calibration presets
 * to generate the MM1 and MM2 range offset data
 *
 * The range config timeout is used for both MM1 and MM2 so that
 * the sigma delta settling is the same as for the 'real' range
 *
 * Places results into VL53L1_customer_nvm_managed_t within pdev
 *
 * Use VL53L1_get_part_to_part_data() to get the offset calibration
 * results
 *
 * Current FMT settings:
 *
 * - offset_calibration_mode            = VL53L1_OFFSETCALIBRATIONMODE__STANDARD_RANGING
 * - dss_config__target_total_rate_mcps = 0x0A00 (20.0Mcps) to  0x1400 (40.0Mcps)
 * - phasecal_config_timeout_us         =   1000
 * - range_config_timeout_us            =  13000
 * - pre_num_of_samples                 =     32
 * - mm1_num_of_samples                 =    100
 * - mm2_range_num_of_samples           =     64
 * - target_distance_mm                 =    140 mm
 * - target reflectance                 =      5%
 *
 *  Note: function parms simplified as part of Patch_CalFunctionSimplification_11791
 *
 * @param[in]   Dev                       : Device handle
 * @param[in]   cal_distance_mm           : Distance to target in [mm] - the ground truth
 * @param[out]  pcal_status               : Pointer to unfiltered calibration status
 *
 * @return  VL53L1_ERROR_NONE     Success
 * @return  VL53L1_WARNING_OFFSET_CAL_INSUFFICIENT_MM1_SPADS
 *                                Effective MM1 SPAD count too low (<5.0).
 *                                Out with recommended calibration condition.
 *                                Accuracy of offset calibration may be degraded.
 * @return  VL53L1_WARNING_OFFSET_CAL_PRE_RANGE_RATE_TOO_HIGH
 *                                Pre range too high (>40.0) in pile up region.
 *                                Out with recommended calibration condition.
 *                                Accuracy of offset calibration may be degraded.
 */

#ifndef VL53L1_NOCALIB
VL53L1_Error   VL53L1_run_offset_calibration(
	VL53L1_DEV	                  Dev,
	int16_t                       cal_distance_mm,
	VL53L1_Error                 *pcal_status);
#endif


#ifdef __cplusplus
}
#endif

#endif /* VL53L1X_API_CALIBRATION_H_ */
