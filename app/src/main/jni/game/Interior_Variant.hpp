//
// Created by F1 on 9/12/2016.
//

#ifndef PARKOUR_INTERIOR_VARIANT_HPP
#define PARKOUR_INTERIOR_VARIANT_HPP

#include "../engine/graphics/Material.hpp"
#include "../engine/graphics/Texture.hpp"

//This class is responsible for handling the materials / textures of each variety of interior tile style
class Interior_Variant
{
public:
	Material* mat;
	//TODO: hold shader as well, hold parameters

	//All variants use the same shader, store as static within the class
	static Shader* shader;
	static bool shader_gl_initialed;

	Texture* diffuse_map;
	Texture* normal_map;
	Texture* light_map;

	//Three components to misc map:
	//R: cubemap reflectiveness
	//G: specularity (try using lightmap value as specularity instead to free this for palette colors)
	//B: transparency
	Texture* misc_map;


	static int init_static_data(const char *vsrc, const char *fsrc)
	{
		if(!shader)
		{
			shader = new Shader(vsrc,fsrc);
		}
		return 1;
	}
	static void term_static_data()
	{
		if(shader)
			delete shader;
	}


	Interior_Variant()
	{
		mat = new Material();
	}

	~Interior_Variant()
	{
		delete mat;
		delete shader;
	}


	//Binds the material
	int bind_variant()
	{
		mat->bind_material();
		//TODO: pass in all material data here (not including any mesh data)
	};

	//TODO: generate variant.
	//This method makes a new interior color palette, ready to be bound by the bind_variant method


	static int init_gl()
	{
		GLuint mesh_params[] =
		{
			Shader::PARAM_VERTICES,
			Shader::PARAM_VERT_UV1,
			Shader::PARAM_VERT_UV2,
			Shader::PARAM_VERT_NORMALS,
			Shader::PARAM_MVP_MATRIX,
			Shader::PARAM_M_IT_MATRIX
			//,Shader::PARAM_COLOR_MULT
		};
		const char *mesh_param_names[] =
		{
			"vert_pos",
			"vert_uv_1",
			"vert_uv_2",
			"vert_nor",
			"mvp",
			"m_IT"
			//,"color"
		};
		shader->init_gl(mesh_params, mesh_param_names, 6);

		//TODO: load textures
		return 1;
	}

	static void term_gl()
	{
		if(shader)
			shader->term_gl();
	}
};

#endif //PARKOUR_INTERIOR_VARIANT_HPP
