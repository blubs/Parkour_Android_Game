//
// Created by F1 on 8/22/2016.
//

#ifndef PARKOUR_FLOOR_HPP
#define PARKOUR_FLOOR_HPP

#include "../engine/math/math.hpp"
#include "../engine/Game_Object.hpp"
#include "Tile.hpp"

class Floor : Entity
{
public:
	//height of the floor's ground level
	float altitude;

	Vec3 global_pos;
	Vec3 global_mins;
	Vec3 global_maxs;

	Floor()
	{
		global_pos = Vec3(0,0,0);
		altitude = 0;
	}
	~Floor()
	{
	}

	void generate(Vec3 p, int floor_num, Vec3 mins, Vec3 maxs)
	{
		altitude = p.z + floor_num*GRIDSIZE;
		global_pos = p + Vec3(0,0,altitude);
		global_mins = mins;
		global_maxs = maxs;
	}

	void clear()
	{

	}

	char is_solid_at(Vec3 p)
	{
		//TODO: reach into tile at position
		return false;
	}

	bool is_y_out_of_bounds(Vec3 p)
	{
		if(p.y < global_mins.y || p.y > global_maxs.y)
			return true;
		return false;
	}

	bool is_x_out_of_bounds(Vec3 p)
	{
		if(p.x < global_mins.x || p.x > global_maxs.x)
			return true;
		return false;
	}
};

#endif //PARKOUR_FLOOR_HPP
