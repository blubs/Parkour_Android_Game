//
// Created by F1 on 11/21/2016.
//

#ifndef PARKOUR_WINDOW_MESH_HOLDER_HPP
#define PARKOUR_WINDOW_MESH_HOLDER_HPP

#include "../engine/graphics/Static_Model.hpp"
#include "game_defs.hpp"

class Window_Model_Holder
{
public:
	Static_Model* tile_model = NULL;
	Static_Model* m2x2_model = NULL;
	Static_Model* m4x4_model = NULL;
	Static_Model* m8x8_model = NULL;
	Static_Model* m16x16_model = NULL;
	Static_Model* m32x32_model = NULL;

	//Horizontal strips
	Static_Model* m1x2_model = NULL;
	Static_Model* m1x4_model = NULL;
	Static_Model* m1x8_model = NULL;
	Static_Model* m1x16_model = NULL;
	Static_Model* m1x32_model = NULL;

	//Vertical strips
	Static_Model* m2x1_model = NULL;
	Static_Model* m4x1_model = NULL;
	Static_Model* m8x1_model = NULL;
	Static_Model* m16x1_model = NULL;
	Static_Model* m32x1_model = NULL;

	Window_Model_Holder(const char* filepath)
	{
		tile_model = new Static_Model(filepath);
		if(!tile_model)
		{
			LOGE("Window Model Holder Error: model failed to load, aborting mesh matrix calculation");
			return;
		}

		Mat4 ident = Mat4::IDENTITY();

		//================== Making the matrices =================

		//Making a 1x2 strip
		m1x2_model = new Static_Model(tile_model,ident,tile_model,Mat4::TRANSLATE(Vec3(TILE_SIZE,0,0)));
		//Making 2x2 model
		m2x2_model = new Static_Model(m1x2_model,ident,m1x2_model,Mat4::TRANSLATE(Vec3(0,0,WINDOW_TILE_SIZE)));

		//Making a temp 2x4 strip
		Static_Model temp_2x4 = Static_Model(m2x2_model,ident,m2x2_model,Mat4::TRANSLATE(Vec3(TILE_SIZE*2,0,0)));;
		//Making 4x4 model
		m4x4_model = new Static_Model(&temp_2x4,ident,&temp_2x4,Mat4::TRANSLATE(Vec3(0,0,2*WINDOW_TILE_SIZE)));

		//Making a temp 4x8 strip
		Static_Model temp_4x8 = Static_Model(m4x4_model,ident,m4x4_model,Mat4::TRANSLATE(Vec3(TILE_SIZE*4,0,0)));;
		//Making 8x8 model
		m8x8_model = new Static_Model(&temp_4x8,ident,&temp_4x8,Mat4::TRANSLATE(Vec3(0,0,4*WINDOW_TILE_SIZE)));

		//Making a temp 8x16 strip
		Static_Model temp_8x16 = Static_Model(m8x8_model,ident,m8x8_model,Mat4::TRANSLATE(Vec3(TILE_SIZE*8,0,0)));;
		//Making 16x16 model
		m16x16_model = new Static_Model(&temp_8x16,ident,&temp_8x16,Mat4::TRANSLATE(Vec3(0,0,8*WINDOW_TILE_SIZE)));

		//Making a temp 16x32 strip
		Static_Model temp_16x32 = Static_Model(m16x16_model,ident,m16x16_model,Mat4::TRANSLATE(Vec3(TILE_SIZE*16,0,0)));;
		//Making 16x16 model
		m32x32_model = new Static_Model(&temp_16x32,ident,&temp_16x32,Mat4::TRANSLATE(Vec3(0,0,16*WINDOW_TILE_SIZE)));


		//=================== Making the horizontal strips ==================
		//1x2 strip is already made above.
		m1x4_model = new Static_Model(m1x2_model,ident,m1x2_model,Mat4::TRANSLATE(Vec3(TILE_SIZE*2,0,0)));
		m1x8_model = new Static_Model(m1x4_model,ident,m1x4_model,Mat4::TRANSLATE(Vec3(TILE_SIZE*4,0,0)));
		m1x16_model = new Static_Model(m1x8_model,ident,m1x8_model,Mat4::TRANSLATE(Vec3(TILE_SIZE*8,0,0)));
		m1x32_model = new Static_Model(m1x16_model,ident,m1x16_model,Mat4::TRANSLATE(Vec3(TILE_SIZE*16,0,0)));


		//=================== Making the vertical strips ==================
		m2x1_model = new Static_Model(tile_model,ident,tile_model,Mat4::TRANSLATE(Vec3(0,0,WINDOW_TILE_SIZE)));
		m4x1_model = new Static_Model(m2x1_model,ident,m2x1_model,Mat4::TRANSLATE(Vec3(0,0,2*WINDOW_TILE_SIZE)));
		m8x1_model = new Static_Model(m4x1_model,ident,m4x1_model,Mat4::TRANSLATE(Vec3(0,0,4*WINDOW_TILE_SIZE)));
		m16x1_model = new Static_Model(m8x1_model,ident,m8x1_model,Mat4::TRANSLATE(Vec3(0,0,8*WINDOW_TILE_SIZE)));
		m32x1_model = new Static_Model(m16x1_model,ident,m16x1_model,Mat4::TRANSLATE(Vec3(0,0,16*WINDOW_TILE_SIZE)));
	}

	~Window_Model_Holder ()
	{
		delete tile_model;
		delete m2x2_model;
		delete m4x4_model;
		delete m8x8_model;
		delete m16x16_model;
		delete m32x32_model;

		//Horizontal strips
		delete m1x2_model;
		delete m1x4_model;
		delete m1x8_model;
		delete m1x16_model;
		delete m1x32_model;

		//Vertical strips
		delete m2x1_model;
		delete m4x1_model;
		delete m8x1_model;
		delete m16x1_model;
		delete m32x1_model;
	}
};

//TODO: a version of the above, but only does horizontal strips for interior windows
#endif //PARKOUR_WINDOW_MESH_HOLDER_HPP
