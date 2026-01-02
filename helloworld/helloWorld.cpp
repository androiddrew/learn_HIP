#include <hip/hip_runtime.h>

// A GPU kernel must be prefixed with __global__to allow the compiler to generate
// GPU specific code
__global__ void gpuHello() {
	// This print inside a GPU kernel is a special convenience feature. The GPU
	// is actually writing to a shared string buffer.
	//
	// The blockIdx.x and threadIdx.x only exist within the GPU context
	printf("Hello GPU programming! Block: %d, Thread: %d\n", blockIdx.x, threadIdx.x);
}

int main(){
	//<<<1,1>>> here is inserted between the function name and the parameter list.
	//This denotes a Grid number and a block number. Here we are creating
	//a single thread in the kernel by creating one grid with a block with one thread.
	//You could change that to <<<2,6>>> and get 2 blocks each with 6 threads. Each thread
	//executing it's own instance of the kernel.
	gpuHello<<<4,4>>>();
	//
	//gpuHello<<<2,6>>>();
	//Tells the CPU to wait until the GPU is done. At this point ROCm runtime flushes
	// the shared GPU string buffer to stdout
	hipDeviceSynchronize();
}

