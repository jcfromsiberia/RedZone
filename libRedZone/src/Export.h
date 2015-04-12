/*
 * Export.h
 *
 *  Created on: 2014
 *      Author: jc
 */
#pragma once

#if defined( RZ_STATIC )
#   define RZ_API
#elif defined( __GNUC__ ) && __GNUC__ >= 4 && defined( RZ_EXPORTS )
#   define RZ_API __attribute__ ( ( visibility( "default" ) ) )
#elif defined( _MSC_VER )
#   if defined( RZ_EXPORTS )
#		define RZ_API __declspec( dllexport )
#   else
#       define RZ_API __declspec( dllimport )
#   endif defined( RZ_EXPORTS )
#else
   #define RZ_API
#endif // defined( RZ_STATIC )
