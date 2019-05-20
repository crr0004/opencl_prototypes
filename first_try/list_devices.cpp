#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include "clext.h"


void printDevicesOnPlatform(cl_platform_id platform){

    cl_uint num_devices, i;
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
	fprintf(stdout, "Found %d devices.\n", num_devices);

    cl_device_id devices[num_devices];
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, num_devices, devices, NULL);

    char buf[128];
    for (i = 0; i < num_devices; i++) {
        clGetDeviceInfo(devices[i], CL_DEVICE_NAME, 128, buf, NULL);
        fprintf(stdout, "Device %s supports ", buf);

        clGetDeviceInfo(devices[i], CL_DEVICE_VERSION, 128, buf, NULL);
        fprintf(stdout, "%s\n", buf);
    }


}

int main(int argc, char* const argv[]) {
	cl_uint num_entries=128, num_platforms, ret;
	cl_platform_id platforms[num_entries];
	ret = clGetPlatformIDs(num_entries, platforms, &num_platforms);
	clCheckError(ret);
	fprintf(stdout, "Found %d platforms.\n", num_platforms);

	char outBuf[256];
	size_t outBufWritten = 0;
	for(cl_uint i = 0; i < num_platforms; i++){
		clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 256, outBuf, &outBufWritten);
		fprintf(stdout, "Platform name %s.\n", outBuf);
		printDevicesOnPlatform(platforms[i]);

	}

}

