//
// Created by F1 on 10/12/2016.
//

#ifndef PARKOUR_ENGINE_DEFS_HPP
#define PARKOUR_ENGINE_DEFS_HPP

//This is the internal data value for opengl to recognize ETC1 compressed textures
#define ETC1_RGB8 0x8D64

#define SND_AUDIO_CHANNELS 8
#define SND_AUDIO_BUFFER_SIZE 512
#define SND_AUDIO_SAMPLE_RATE 44100

#define ASPECT_16_9_LANDSCAPE 1.7778f
#define ASPECT_16_9_PORTRAIT 0.5625f

//============ Skeletal Animation Defs ==========
#define ANIM_END_TYPE_ROOT_POSE 0
#define ANIM_END_TYPE_FREEZE 1
#define ANIM_END_TYPE_LOOP 2
#define ANIM_END_TYPE_DEFAULT_ANIM 3

#define ANIM_FPS_60 1/60.0f

//============ Sound Engine Defs ==============
#define MAX_SOUND_SOURCES 32

#define SOUND_PRIORITY_AMBIENCE 0
#define SOUND_PRIORITY_PLAYER 1
#define SOUND_PRIORITY_PHYSICS 2
#define SOUND_PRIORITY_MISC 3

#endif //PARKOUR_ENGINE_DEFS_HPP
