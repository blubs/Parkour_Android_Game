//
// Created by F1 on 3/29/2016.
//

#include "misc.hpp"


float Time::fdelta_time = 0.0f;
float Time::udelta_time = 0.0f;

float Time::last_frame_time = 0.0f;
float Time::last_update_time = 0.0f;

float Time::time_scale = 1.0f;
double Time::start_time = 0.0;

//Returns nanoseconds (from some arbitrary reference point, doesn't seem to be epoch time) as an unsigned long long
//sample printing code:
//uint64_t t1 = nano_time();
//LOGE("time in nano: %llu\n",t1);
/*uint64_t nano_time()
{
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);
//	return (uint64_t) (now.tv_sec*1000000000LL + now.tv_nsec);
	return now.tv_sec * 1000.0 + (double) now.tv_nsec / 1e6;
	//return (uint64_t) (now.tv_sec*1000000000LL + now.tv_nsec);
}*/

//Prints the elements of a Mat4 matrix
void print_mat4(float* mat)
{
	LOGI("[ %.2f , %.2f , %.2f , %.2f ]\n[ %.2f , %.2f , %.2f , %.2f ]\n[ %.2f , %.2f , %.2f , %.2f ]\n[ %.2f , %.2f , %.2f , %.2f ]\n",
		mat[0],mat[4],mat[8],mat[12],
		mat[1],mat[5],mat[9],mat[13],
		mat[2],mat[6],mat[10],mat[14],
		mat[3],mat[7],mat[11],mat[15]);
}
//Prints the elements of a Mat3 matrix
void print_mat3(float* mat)
{
	LOGI("[ %.2f , %.2f , %.2f ]\n[ %.2f , %.2f , %.2f ]\n[ %.2f , %.2f , %.2f ]\n",
		mat[0],mat[3],mat[6],
		mat[1],mat[4],mat[7],
		mat[2],mat[5],mat[8]);
}

//Default Random values
//Seed must be non-zero
unsigned long Random::seed = 1;
int Random::base = 0xFFFE;
int Random::factor = 18782;

//Fast inverse square root function (as seen in Q3 src code)
//profiling revealed math.h's 1/sqrt() function to be faster, however...
//Keeping it in this project for sentimental value.
/*
float fast_inv_sqrt(float num)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;
	x2 = num * 0.5F;
	y = num;
	i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*) &i;
	y = y*(threehalfs - (x2 * y * y));
	//y = y*(threehalfs - (x2 * y * y));//2nd iteration

	return y;
}
*/