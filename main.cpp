// main.cpp
#include <hip/hip_runtime.h>
#include "diffusion.h"
#include "diffusion_kernel.h"
#include "gpu_utils.h"

int main() {
    // Host arrays
    float* h_u = new float[NX * NY];
    float* h_u_old = new float[NX * NY];

    // Initialize grid
    initialize(h_u);

    // Device arrays
    float *d_u, *d_u_new;
    GPU_CHECK( hipMalloc(&d_u, NX * NY * sizeof(float)) );
    GPU_CHECK( hipMalloc(&d_u_new, NX * NY * sizeof(float)) );

    // Copy initial data to device
    GPU_CHECK( hipMemcpy(d_u, h_u, NX * NY * sizeof(float), hipMemcpyHostToDevice) );

    // Define block and grid sizes
    dim3 blockSize(16, 16);
    dim3 gridSize((NX + blockSize.x - 1) / blockSize.x,
                  (NY + blockSize.y - 1) / blockSize.y);

    int iter = 0;
    float max_diff = 0.0f;

    do {
        // Save old u
        GPU_CHECK( hipMemcpy(h_u_old, d_u, NX * NY * sizeof(float), hipMemcpyDeviceToHost) );

        // Launch kernel
        diffusionStep<<<gridSize, blockSize, 0, 0>>>(d_u, d_u_new);

        // Swap pointers
        float* temp = d_u;
        d_u = d_u_new;
        d_u_new = temp;

        // Copy new u back to host
        GPU_CHECK( hipMemcpy(h_u, d_u, NX * NY * sizeof(float), hipMemcpyDeviceToHost) );

        // Compute maximum difference
        max_diff = computeMaxDifference(h_u, h_u_old);

        // Print maximum difference
        printMaxDifference(iter, max_diff);

        iter++;

    } while (max_diff > TOL && iter < MAX_ITER);

    // Clean up
    delete[] h_u;
    delete[] h_u_old;
    GPU_CHECK( hipFree(d_u) );
    GPU_CHECK( hipFree(d_u_new) );

    return 0;
}

