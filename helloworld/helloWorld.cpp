#include <hip/hip_runtime.h>
#include <iostream>

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
	// check if a GPU is present
	int deviceCount = 0;
	hipGetDeviceCount(&deviceCount);

	if (deviceCount == 0) {
		std::cout << "No HIP-capable devices found!" << std::endl;
		return 1;
	}
	
	// get HIP device information
	hipDeviceProp_t props;
	int deviceId;

	hipGetDevice(&deviceId);
	hipGetDeviceProperties(&props, deviceId);

	std::cout << "Running on: " << props.name << std::endl;
	std::cout << "Compute Capability: " << props.major << "." << props.minor << std::endl;

	//<<<1,1>>> here is inserted between the function name and the parameter list.
	//This denotes creating a Grid of one block with one thread.
	//You could change that to <<<2,6>>> and get a grid of 2 blocks each with 6 threads. Each thread
	//executing it's own instance of the kernel.
	gpuHello<<<4,4>>>();

	//Tells the CPU to wait until the GPU is done. At this point ROCm runtime flushes
	// the shared GPU string buffer to stdout
	hipError_t err = hipDeviceSynchronize();
	if (err != hipSuccess) {
		printf("HIP Error: %s\n", hipGetErrorString(err));
	} else {
		printf("Kernel executed and synchronized successfully.\n");
	}
}

