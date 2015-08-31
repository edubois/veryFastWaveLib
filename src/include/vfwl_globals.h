#include <unistd.h>

#ifndef VFWL_GLOBALS_H
#define VFWL_GLOBALS_H

#define WAVT_16

#define INT_SIZE            4

#ifdef WAVT_16
   #define WAVT_BYTE_SIZE   2
   #define WB_PER_128b      8
#else
   #define WAVT_BYTE_SIZE   4
   #define WB_PER_128b      4
#endif

#endif  /* VFWL_GLOBALS_H */
