// diffusion.cpp
#include "diffusion.h"

void initialize(float* h_u) {
    // Initialize the grid with zeros
    for (int i = 0; i < NX * NY; ++i) {
        h_u[i] = 0.0f;
    }

    // Set a hotspot in the center
    int cx = NX / 2;
    int cy = NY / 2;
    h_u[cy * NX + cx] = 100.0f; // Hotspot temperature
}

void printMaxDifference(int iter, float max_diff) {
    if ((iter % 100) == 0){
        std::cout << "Iteration: " << iter << ", Max Difference: " << max_diff << std::endl;
    }
}

float computeMaxDifference(float* h_u, float* h_u_old) {
    float max_diff = 0.0f;
    for (int i = 0; i < NX * NY; ++i) {
        float diff = fabs(h_u[i] - h_u_old[i]);
        if (diff > max_diff) {
            max_diff = diff;
        }
    }
    return max_diff;
}

