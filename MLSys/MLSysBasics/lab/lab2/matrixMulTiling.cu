#include <cuda_runtime.h>
#include <stdio.h>

#define TILE_WIDTH 16  // Tile width for tiling

// Kernel for matrix multiplication using tiling
__global__ void matrixMulTiled(float *A, float *B, float *C, int M, int N, int P) {
    __shared__ float tileA[TILE_WIDTH][TILE_WIDTH];
    __shared__ float tileB[TILE_WIDTH][TILE_WIDTH];

    int row = blockIdx.y * TILE_WIDTH + threadIdx.y;
    int col = blockIdx.x * TILE_WIDTH + threadIdx.x;

    float value = 0.0f;

    for (int t = 0; t < (N - 1) / TILE_WIDTH + 1; ++t) {
        if (row < M && (t * TILE_WIDTH + threadIdx.x) < N)
            tileA[threadIdx.y][threadIdx.x] = A[row * N + t * TILE_WIDTH + threadIdx.x];
        else
            tileA[threadIdx.y][threadIdx.x] = 0.0f;

        if (col < P && (t * TILE_WIDTH + threadIdx.y) < N)
            tileB[threadIdx.y][threadIdx.x] = B[(t * TILE_WIDTH + threadIdx.y) * P + col];
        else
            tileB[threadIdx.y][threadIdx.x] = 0.0f;

        __syncthreads();

        for (int i = 0; i < TILE_WIDTH; ++i)
            value += tileA[threadIdx.y][i] * tileB[i][threadIdx.x];

        __syncthreads();
    }

    if (row < M && col < P)
        C[row * P + col] = value;
}

// Function to print a matrix
void printMatrix(float *matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

// Matrix multiplication with performance monitoring and printing input/output
void matrixMultiplication(float *h_A, float *h_B, float *h_C, int M, int N, int P) {
    float *d_A, *d_B, *d_C;
    size_t size_A = M * N * sizeof(float);
    size_t size_B = N * P * sizeof(float);
    size_t size_C = M * P * sizeof(float);

    // Allocate device memory
    cudaMalloc((void**)&d_A, size_A);
    cudaMalloc((void**)&d_B, size_B);
    cudaMalloc((void**)&d_C, size_C);

    // Copy matrices A and B from host to device
    cudaMemcpy(d_A, h_A, size_A, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size_B, cudaMemcpyHostToDevice);

    // Set grid and block dimensions
    dim3 dimBlock(TILE_WIDTH, TILE_WIDTH, 1);
    dim3 dimGrid((P - 1) / TILE_WIDTH + 1, (M - 1) / TILE_WIDTH + 1, 1);

    // CUDA event variables for timing
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // Start timing
    cudaEventRecord(start);

    // Launch the kernel
    matrixMulTiled<<<dimGrid, dimBlock>>>(d_A, d_B, d_C, M, N, P);

    // Stop timing
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    // Calculate elapsed time
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);
    printf("Matrix multiplication (tiled) execution time: %f ms\n", milliseconds);

    // Copy the result from device to host
    cudaMemcpy(h_C, d_C, size_C, cudaMemcpyDeviceToHost);

    // Free device memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}

int main() {
    // Example matrix sizes
    int M = 4;  // Number of rows in A and C
    int N = 4;  // Number of columns in A and rows in B
    int P = 4;  // Number of columns in B and C

    // Allocate host memory
    float *h_A = (float*)malloc(M * N * sizeof(float));
    float *h_B = (float*)malloc(N * P * sizeof(float));
    float *h_C = (float*)malloc(M * P * sizeof(float));

    // Initialize matrices A and B with some values
    for (int i = 0; i < M * N; i++) {
        h_A[i] = static_cast<float>(rand()) / RAND_MAX;
    }
    for (int i = 0; i < N * P; i++) {
        h_B[i] = static_cast<float>(rand()) / RAND_MAX;
    }

    // Print the input matrices
    printf("Matrix A:\n");
    printMatrix(h_A, M, N);

    printf("Matrix B:\n");
    printMatrix(h_B, N, P);

    // Perform matrix multiplication
    matrixMultiplication(h_A, h_B, h_C, M, N, P);

    // Print the output matrix
    printf("Matrix C (Result):\n");
    printMatrix(h_C, M, P);

    // Free host memory
    free(h_A);
    free(h_B);
    free(h_C);

    return 0;
}
