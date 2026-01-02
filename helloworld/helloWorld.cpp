#include <hip/hip_runtime.h>

// A GPU kernel must be prefixed with __global__to allow the compiler to generate
// GPU specific code
__global__ void gpuHello() {
	printf("Hello GPU programming\n");
}

int main(){
	//<<<1,1>>> here is inserted between the function name and the parameter list.
	//this denotes the number of threads within the kernel. Here we are creating
	//a single thread in the kernel
	gpuHello<<<1,1>>>();
	hipDeviceSynchronize();
}

