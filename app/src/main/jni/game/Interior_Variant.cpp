//
// Created by F1 on 9/12/2016.
//

#include "Interior_Variant.hpp"

//Interior Variant Static Vars
Shader* Interior_Variant::shader = NULL;
bool Interior_Variant::shader_gl_inited = false;


//Exterior Variant Static Vars
//Shader for outer windows
Shader* Exterior_Variant::ext_shader = NULL;
//Shader for inner windows
Shader* Exterior_Variant::int_shader = NULL;
bool Exterior_Variant::shader_gl_inited = false;

