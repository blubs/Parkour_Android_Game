//
// Created by F1 on 4/29/2016.
//

#include "Player.hpp"

int Player::render(Mat4 vp)
{
	//if(!mat)
	//	return 1;

	//TODO: implement more general player model rendering, not so hard-coded
	//mat->bind_material();
	mat1->bind_material();
	player_model1->render(Mat4::IDENTITY(),vp,mat1,skel);
	mat2->bind_material();
	player_model2->render(Mat4::IDENTITY(),vp,mat2,skel);
	mat3->bind_material();
	player_model3->render(Mat4::IDENTITY(),vp,mat3,skel);
	return 1;
}

//Update method that is ran every frame
int Player::update()
{
	LOGE("skeleton update frame");
	skel->update_frame();
	LOGE("end skeleton update frame");
	return 1;
}