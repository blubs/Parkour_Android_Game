//
// Created by F1 on 3/29/2016.
//

#ifndef ENGINE_MISC_H
#define ENGINE_MISC_H

#include "common.hpp"

//Global time variables, set every frame by engine
class Time
{
public:
	//Variable that holds time since last frame
	static float delta_time;
	//Variable that holds the time at the beginning of the last frame
	static float current_time;

	//Set at game start
	//We use double here for more precision then convert down to float once subtracting time from this
	static double start_time;

	//Sets start_time for later usage
	static void set_start_time()
	{
		struct timespec now;
		clock_gettime(CLOCK_MONOTONIC, &now);
		start_time = now.tv_sec + (double) now.tv_nsec / 1e9;
	}

	//Returns time since start_time as a float
	static float time()
	{
		if(start_time == 0.0)
		{
			LOGW("Warning: time() called without first calling set_start_time(), start_time = 0\n");
		}

		struct timespec now;
		clock_gettime(CLOCK_MONOTONIC, &now);
		double current_time = now.tv_sec + (double) now.tv_nsec / 1e9;
		return (float) (current_time - start_time);
	}

};

//Prints the elements of a 4x4 matrix
void print_mat4(float* mat);

//Prints the elements of a 3x3 matrix
void print_mat3(float* mat);


//Unused, refer to function def as to why
//float fast_inv_sqrt(float num);


#endif //ENGINE_MISC_H
