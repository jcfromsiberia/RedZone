/*
 * Export.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#ifdef RZ_STATIC
   #define RZ_API
#elif defined(__GNUC__) && __GNUC__ >= 4
   #define RZ_API __attribute__ ((visibility ("default")))
#else
   #define RZ_API
#endif // ISILDUR_STATIC
