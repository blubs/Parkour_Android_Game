#include "engine_main.hpp"

#include "jni.h"


void android_main(struct android_app *app)
{
	//Making sure glue is not stripped
	app_dummy();

	Engine engine(app);
	//We never leave this scope anyways
	app->userData = &engine;

	File_Utils::asset_mgr = app->activity->assetManager;

	//Setting start time as now (a reference point)
	Time::set_start_time();

	//====================================

#ifdef DEBUG_MODE
	LOGI("LIFECYCLE: ANDROID_MAIN RAN\n");
#endif


	//Reads saved data and writes saved data
	const char* data = File_Utils::read_savedata("test.dat");
	LOGI("Read file: %s.\n",data);
	free((char*)data);
	File_Utils::write_savedata("test.dat");

	//run the engine loop
	while(1)
	{
		//Reading all pending events
		int ident;
		int events;
		struct android_poll_source *source;

		//When not animating: block waiting for events
		//When animating, handle all events then draw frame

		while((ident = ALooper_pollAll(engine.animating ? 0 : -1,NULL, &events,(void**)  &source))>=0)
		{
			//Process event
			if(source != NULL)
			{
				source->process(app,source);
			}
			//Unused accelerometer update handling
			//If sensor has data, process it
			//if(ident == LOOPER_ID_USER)
			//{
			//	//if(engine.accelerometer_sensor != NULL)
			//	//{
			//		ASensorEvent event;
			//		while(ASensorEventQueue_getEvents(engine.sensor_event_queue,&event,1) > 0)
			//		{
			//			//do nothing
			//			app_dummy();
			//			//LOGI("accelerometer: x=%f y=%f z=%f", event.acceleration.x,
			//			//	event.acceleration.y, event.acceleration.z);
			//		}
			//	//}
			//}
			//Check if exiting
			if(app->destroyRequested != 0)
			{
#ifdef DEBUG_MODE
				LOGI("LIFECYCLE: Exiting application.\n");
#endif
				engine.last_frame();
				return;
			}
		}

		if(engine.animating)
		{
			//TODO: decouple draw_frame from update
			//TODO: when ready, call the following function from the right update timing code
			//engine.update();
			engine.draw_frame();

			//No guarantees that the we're actually drawing until gl_initialized is 1
			if(engine.gl_initialized)
			{
				//Drawing throttled by screen update rate, no timing code needed here
				static long frame = 0;


				static float frame_count_start_time = Time::time();
				static int frame_count = 0;
				static float fps = 0.0f;

				//Count average fps over 60 frames
				if(frame_count >= 60)
				{
					fps = frame_count / Time::time() - frame_count_start_time;
					frame_count = 0;
				}
				frame_count++;


				//Drawing FPS
				char fps_str[20];
				snprintf(fps_str,20,"FPS: %.2f",fps);

				UI_Text::draw_text(fps_str,
					Vec3(engine.width * 0.4f, engine.height * 0.4f,0.5),
					Vec3::ZERO(),100,Vec3(1,1,1),Vec3::ZERO(),1,false,
					engine.game->camera->ortho_proj_m);

				//if(frame % 60 == 0)
				//	LOGE("60 frames passed\n");
				//LOGE("Frame: %ld, frame mod 60 = %ld\n",frame,(frame % 60));
				frame++;
				//LOGE("delta_time = %f,  last_frame_time = %f, avg fps = %f\n",delta_time, last_frame_time,frame/time());
			}
		}
	}
}