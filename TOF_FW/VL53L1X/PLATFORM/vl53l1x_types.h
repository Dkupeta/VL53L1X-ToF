/*
 * vl53l1x_types.h
 *
 *  Created on: Jul 20, 2024
 *      Author: dkupe
 */

#ifndef VL53L1X_TYPES_H_
#define VL53L1X_TYPES_H_

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef NULL
#error "Error NULL definition should be done. Please add required include "
#endif


#if !defined(STDINT_H) && !defined(_STDINT_H) && !defined(_GCC_STDINT_H) && !defined(__STDINT_DECLS) && !defined(_GCC_WRAP_STDINT_H)  && !defined(_STDINT)

 #pragma message("Please review  type definition of STDINT define for your platform and add to list above ")

 /*
  *  target platform do not provide stdint or use a different #define than above
  *  to avoid seeing the message below addapt the #define list above or implement
  *  all type and delete these pragma
  */

/** \ingroup VL53L1_portingType_group
 * @{
 */


typedef unsigned long long uint64_t;


/** @brief Typedef defining 32 bit unsigned int type.\n
 * The developer should modify this to suit the platform being deployed.
 */
typedef unsigned int uint32_t;

/** @brief Typedef defining 32 bit int type.\n
 * The developer should modify this to suit the platform being deployed.
 */
typedef int int32_t;

/** @brief Typedef defining 16 bit unsigned short type.\n
 * The developer should modify this to suit the platform being deployed.
 */
typedef unsigned short uint16_t;

/** @brief Typedef defining 16 bit short type.\n
 * The developer should modify this to suit the platform being deployed.
 */
typedef short int16_t;

/** @brief Typedef defining 8 bit unsigned char type.\n
 * The developer should modify this to suit the platform being deployed.
 */
typedef unsigned char uint8_t;

/** @brief Typedef defining 8 bit char type.\n
 * The developer should modify this to suit the platform being deployed.
 */
typedef signed char int8_t;

/** @}  */
#endif /* _STDINT_H */


/** use where fractional values are expected
 *
 * Given a floating point value f it's .16 bit point is (int)(f*(1<<16))*/
typedef uint32_t FixPoint1616_t;



#endif /* VL53L1X_TYPES_H_ */
