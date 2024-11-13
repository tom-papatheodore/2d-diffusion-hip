// diffusion_kernel.h
#ifndef DIFFUSION_KERNEL_H
#define DIFFUSION_KERNEL_H

#include <hip/hip_runtime.h>
//#include "diffusion.h"

// Declaration of the kernel function
__global__ void diffusionStep(float* d_u, float* d_u_new);

#endif // DIFFUSION_KERNEL_H

