// diffusion_kernel.hip
#include <hip/hip_runtime.h>
#include "diffusion.h"

__global__ void diffusionStep(float* d_u, float* d_u_new) {
    int ix = blockIdx.x * blockDim.x + threadIdx.x;
    int iy = blockIdx.y * blockDim.y + threadIdx.y;

    if (ix > 0 && ix < NX - 1 && iy > 0 && iy < NY - 1) {
        int idx = iy * NX + ix;

        // Compute Laplacian
        float laplacian = (d_u[idx - 1] + d_u[idx + 1] - 2.0f * d_u[idx]) / (DX * DX)
                        + (d_u[idx - NX] + d_u[idx + NX] - 2.0f * d_u[idx]) / (DY * DY);

        // Update temperature
        d_u_new[idx] = d_u[idx] + D * DT * laplacian;
    } else if (ix < NX && iy < NY) {
        int idx = iy * NX + ix;
        d_u_new[idx] = d_u[idx]; // Boundary points remain the same
    }
}

