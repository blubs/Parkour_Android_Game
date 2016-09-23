//
// Created by F1 on 4/29/2016.
//

#include "Player.hpp"

int Player::render(Mat4 vp)
{
	if(!mat)
		return 1;

	//TODO: render all playermodels
	mat->bind_material();
	skel->update_frame();
	player_model->render(Mat4::IDENTITY(),vp,mat);
	return 1;
}

//Update method that is ran every frame
int Player::update()
{
	return 1;
}