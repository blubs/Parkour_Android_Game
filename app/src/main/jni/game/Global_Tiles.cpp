//
// Created by F1 on 9/3/2016.
//

#include "Global_Tiles.hpp"
#include "../engine/graphics/Static_Model.hpp"

class Collision_Map
{
	char tile[12][12];
	Collision_Map()
	{
	}
	~Collision_Map()
	{}
};

class Tile_Variant
{
	Static_Model* model;
	Collision_Map* collision_map;
};

class Tile_Type
{
	//TODO: tile type const identifiers
	Tile_Variant type[1];
};

class Tile_Style
{
	Tile_Type type[1];
};

class Global_Tiles
{
	Tile_Style style[1];
};