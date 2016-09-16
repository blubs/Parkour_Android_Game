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
	//All variants use the same shader, store as static within the class
	static Shader* shader;
	static bool shader_gl_inited;

	Material* mat;

	Texture* diffuse_map;
	Texture* normal_map;
	Texture* light_map;


	//Three components to misc map:
	//R: cubemap reflectiveness
	//G: specularity (try using lightmap value as specularity instead to free this for palette colors)
	//B: transparency
	Texture* misc_map;


	static int init_static_data(const char *vsrc, const char *fsrc,const GLuint *ptypes, const char **pnames, uint pcount)
	{
		if(!shader)
		{
			shader = new Shader(vsrc,fsrc,ptypes,pnames,pcount);
			//Shader(const char *vshader_name, const char *fshader_name, const GLuint* params, const char** pnames, uint pcount);

			//Destroys and unloads shader
		}
		return 1;
	}
	static void term_static_data()
	{
		delete shader;
		shader = NULL;
	}


	Interior_Variant()
	{
		mat = new Material();
		mat->set_shader(shader);
	}

	~Interior_Variant()
	{
		delete diffuse_map;
		delete normal_map;
		delete light_map;
		delete mat;
	}


	//Binds the material
	int bind_variant()
	{
		mat->bind_material();

		if(diffuse_map)
			mat->bind_value(Shader::PARAM_TEXTURE_DIFFUSE,(void*) diffuse_map);
		if(normal_map)
			mat->bind_value(Shader::PARAM_TEXTURE_NORMAL,(void*) normal_map);
		if(light_map)
			mat->bind_value(Shader::PARAM_TEXTURE_LIGHTMAP,(void*) light_map);
		if(misc_map)
			mat->bind_value(Shader::PARAM_TEXTURE_MISC,(void*) misc_map);

		//TODO: cubemaps

		//TODO: pass in all material data here (not including any mesh data)
		//this includes generated color palettes and cubemaps
	};

	//TODO: generate variant.
	//This method makes a new interior color palette, ready to be bound by the bind_variant method

	int init_gl()
	{
		if(!shader_gl_inited)
		{
			shader->init_gl();
			shader_gl_inited = false;
		}

		if(diffuse_map)
			diffuse_map->init_gl();
		if(normal_map)
			normal_map->init_gl();
		if(light_map)
			light_map->init_gl();
		if(misc_map)
			misc_map->init_gl();
		return 1;
	}
	void term_gl()
	{
		if(shader && shader_gl_inited)
		{
			shader_gl_inited = false;
			shader->term_gl();
		}

		if(diffuse_map)
			diffuse_map->term_gl();
		if(normal_map)
			normal_map->term_gl();
		if(light_map)
			light_map->term_gl();
		if(misc_map)
			misc_map->term_gl();
	}

};

#endif //PARKOUR_INTERIOR_VARIANT_HPP
