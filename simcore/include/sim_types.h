#ifndef SIM_TYPES_INCLUDED
#define SIM_TYPES_INCLUDED

#if defined(__QNXNTO__) || defined(__QNX__)
#include <stdint.h>
#elif defined(WIN32)
    typedef signed char int8_t;
    typedef unsigned char uint8_t;
    typedef signed short int16_t;
    typedef unsigned short uint16_t;
    typedef signed int int32_t;
    typedef unsigned int uint32_t;
	#if (defined(_MSC_VER) || defined(__BORLANDC__) || defined(__INTEL_COMPILER))
		typedef signed __int64 int64_t;
		typedef unsigned __int64 uint64_t;
	#else
		typedef signed long long int64_t;
		typedef unsigned long long uint64_t;
	#endif
#elif defined(LINUX)
#include <stdint.h>
#elif defined(VXWORKS)
#include <types/vxTypes.h>
#  else
#    error "Unknown platform"
#  endif

#endif
