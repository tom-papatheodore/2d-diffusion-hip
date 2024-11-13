// gpu_utils.h
#ifndef GPU_UTILS_H
#define GPU_UTILS_H

#include <iostream>
#include <hip/hip_runtime.h>

#define GPU_CHECK(call)                                                         \
do {                                                                            \
    hipError_t err = call;                                                      \
    if (err != hipSuccess) {                                                    \
        std::cerr << "GPU Error: " << hipGetErrorString(err)                    \
                  << " at " << __FILE__ << ":" << __LINE__ << std::endl;        \
        exit(err);                                                              \
    }                                                                           \
} while (0)

#endif // GPU_UTILS_H
