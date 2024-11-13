// diffusion.h
#ifndef DIFFUSION_H
#define DIFFUSION_H

#include <iostream>
#include <cmath>

// Grid dimensions
const int NX = 2 * 1024;
const int NY = 2 * 1024;

// Diffusion coefficient
const float D = 1.0f;

// Time step
const float DT = 0.1f;

// Space step
const float DX = 1.0f;
const float DY = 1.0f;

// Maximum number of iterations
const int MAX_ITER = 10000;

// Convergence threshold
const float TOL = 1e-5f;

// Function prototypes
void initialize(float* h_u);
void printMaxDifference(int iter, float max_diff);
float computeMaxDifference(float* h_u, float* h_u_old);

#endif // DIFFUSION_H

