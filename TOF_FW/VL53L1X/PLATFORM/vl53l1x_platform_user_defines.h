/*
 * vl53l1x_platform_user_defines.h
 *
 *  Created on: Jul 20, 2024
 *      Author: dkupe
 */

#ifndef VL53L1X_PLATFORM_USER_DEFINES_H_
#define VL53L1X_PLATFORM_USER_DEFINES_H_


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @file   vl53l1x_platform_user_defines.h
 *
 * @brief  All end user OS/platform/application definitions
 */


/**
 * @def do_division_u
 * @brief customer supplied division operation - 64-bit unsigned
 *
 * @param dividend      unsigned 64-bit numerator
 * @param divisor       unsigned 64-bit denominator
 */
#define do_division_u(dividend, divisor) (dividend / divisor)


/**
 * @def do_division_s
 * @brief customer supplied division operation - 64-bit signed
 *
 * @param dividend      signed 64-bit numerator
 * @param divisor       signed 64-bit denominator
 */
#define do_division_s(dividend, divisor) (dividend / divisor)


/**
 * @def WARN_OVERRIDE_STATUS
 * @brief customer supplied macro to optionally output info when a specific
	  error has been overridden with success within the EwokPlus driver
 *
 * @param __X__      the macro which enabled the suppression
 */
#define WARN_OVERRIDE_STATUS(__X__)\
	trace_print (VL53L1_TRACE_LEVEL_WARNING, #__X__);


#ifdef _MSC_VER
#define DISABLE_WARNINGS() { \
	__pragma (warning (push)); \
	__pragma (warning (disable:4127)); \
	}
#define ENABLE_WARNINGS() { \
	__pragma (warning (pop)); \
	}
#else
	#define DISABLE_WARNINGS()
	#define ENABLE_WARNINGS()
#endif


#ifdef __cplusplus
}
#endif


#endif /* VL53L1X_PLATFORM_USER_DEFINES_H_ */
