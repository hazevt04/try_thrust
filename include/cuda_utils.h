#ifndef _CUDA_UTILS_H_
#define _CUDA_UTILS_H_

// Utility Macros for CUDA

#include <cuda_runtime.h>
#include "utils.h"

#define check_cuda_error(cerror,loc) { \
  if ( cerror != cudaSuccess ) { \
    printf( "%s(): "#loc " ERROR: %s (%d)\n", __func__, \
      cudaGetErrorString( cerror ), cerror ); \
    exit(EXIT_FAILURE); \
  } \
}

#define check_cuda_error_flag(cerror,loc) { \
  if ( cerror != cudaSuccess ) { \
    printf( "%s(): "#loc " ERROR: %s (%d)\n", __func__, \
      cudaGetErrorString( cerror ), cerror ); \
    error_flag = true; \
    return FAILURE; \
  } \
}

#define check_cuda_error_return(cerror,loc) { \
  if ( cerror != cudaSuccess ) { \
    printf( "%s(): "#loc " ERROR: %s (%d)\n", __func__, \
      cudaGetErrorString( cerror ), cerror ); \
    return; \
  } \
}

#define check_cuda_error_return_failure(cerror,loc) { \
  if ( cerror != cudaSuccess ) { \
    printf( "%s(): "#loc " ERROR: %s (%d)\n", __func__, \
      cudaGetErrorString( cerror ), cerror ); \
    return FAILURE; \
  } \
}

#define check_cuda_error_throw(cerror,loc) { \
  if ( cerror != cudaSuccess ) { \
    throw std::runtime_error(cudaGetErrorString( cerror )); \
  } \
}


#define try_cuda_func(cerror, func) { \
  cerror = func; \
  check_cuda_error( cerror, func ); \
}

#define try_cuda_func_error_flag(cerror, func) { \
  cerror = func; \
  check_cuda_error_flag( cerror, func ); \
}

#define try_cuda_func_return(cerror, func) { \
  cerror = func; \
  check_cuda_error_return( cerror, func ); \
}

#define try_cuda_func_return_failure(cerror, func) { \
  cerror = func; \
  check_cuda_error_return_failure( cerror, func ); \
}

#define try_cuda_func_throw(cerror, func) { \
  cerror = func; \
  check_cuda_error_throw( cerror, func ); \
}


#define try_cuda_free( cerror, ptr ) { \
  if ((ptr)) { \
    try_cuda_func( (cerror), cudaFree((ptr))); \
    (ptr) = nullptr; \
  } \
}

#define try_cuda_free_host( cerror, ptr ) { \
  if ((ptr)) { \
    try_cuda_func( (cerror), cudaFreeHost((ptr))); \
    (ptr) = nullptr; \
  } \
}

#define try_cuda_free_return( cerror, ptr ) { \
  if (ptr) { \
    try_cuda_func_return( (cerror), cudaFree((ptr)) ); \
  } \
}

#define try_cuda_free_throw( cerror, ptr ) { \
  if (ptr) { \
    try_cuda_func_throw( (cerror), cudaFree((ptr)) ); \
    (ptr) = nullptr; \
  } \
}

#ifdef TRY_FAST_MATH

  #define DIVIDE(quotient, numerator,divisor) { \
    (quotient) = __fdividef((numerator),(divisor)); \
  }
  
  #define DIVIDE_COMPLEX_BY_SCALAR( quotient, numerator, divisor ) { \
     (quotient).x = __fdividef((numerator).x, (divisor)); \
     (quotient).y = __fdividef((numerator).y, (divisor)); \
  }
   
#else

  #define DIVIDE( quotient, numerator, divisor ) { \
    (quotient) = (numerator)/(divisor); \
  }

  #define DIVIDE_COMPLEX_BY_SCALAR( quotient, numerator, divisor ) { \
     (quotient).x = (numerator).x/(divisor); \
     (quotient).y = (numerator).y/(divisor); \
  }

#endif


inline std::string decode_cache_pref( enum cudaFuncCache cache_pref ) {
   std::vector<std::string> cache_pref_strings{
      "Default function cache configuration, no preference",
      "Prefer larger shared memory and smaller L1 cache",
      "Prefer larger L1 cache and smaller shared memory"
   };
     
   int cache_pref_index = static_cast<int>(cache_pref);
   return cache_pref_strings.at(cache_pref_index);
}

#endif // ifndef _CUDA_UTILS_H_
