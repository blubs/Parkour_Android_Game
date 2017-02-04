//
// Created by F1 on 6/17/2016.
//

#ifndef ENGINE_SOUND_SOURCE_H
#define ENGINE_SOUND_SOURCE_H

#include "../Game_Object.hpp"
#include "Sound_Sample.hpp"

//class Sound_Source : public Entity
class Sound_Source : public Entity
{
public:
	bool used = false;
	bool last_used = false;

	int priority = 0;//the lower the priority, the more important TODO: not yet used
	//Consider adding priority constants for standard values

	float volume = 0.0f;
	int sound_pos = 0;

	Sound_Sample* sound = NULL;
	int end_type = SOUND_END_TYPE_STOP;

	//Need duplicate parameters for each audio effect
	float last_falloff_L = 0.0f;
	float last_falloff_R = 0.0f;

	void stop_audio()
	{
		used = false;
		priority = 0;
		sound_pos = 0;
		volume = 0.0f;
		sound = NULL;
		end_type = SOUND_END_TYPE_STOP;
		last_falloff_L = 0.0f;
		last_falloff_R = 0.0f;
	}

};

#endif //ENGINE_SOUND_SOURCE_H
