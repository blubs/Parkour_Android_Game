//
// Created by F1 on 12/31/2016.
//

#include "Dynamic_Model.hpp"

int Dynamic_Model::render(Mat4 m,Mat4 vp,Material* mat)
{
	if(!gl_initialized)
	{
		LOGW("Warning: dynamic model not drawn, gl not initialized");
		return 0;
	}
	if(!mat)
	{
		LOGW("Warning: tried rendering a static model without assigning material\n");
		return 0;
	}

	mat->bind_value(Shader::PARAM_VERTICES, (void*) verts);

	mat->bind_value(Shader::PARAM_VERT_UV1, (void*) uv_coords_1);
	mat->bind_value(Shader::PARAM_VERT_UV2, (void*) uv_coords_2);

	mat->bind_value(Shader::PARAM_VERT_NORMALS, (void*) normals);
	mat->bind_value(Shader::PARAM_VERT_TANGENTS, (void*) tangents);
	mat->bind_value(Shader::PARAM_VERT_BINORMALS, (void*) binormals);

	Mat4 mvp = vp * m;
	mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

	Mat3 m_it = m.inverted_then_transposed().get_mat3();
	mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri_verts_buffer);
	glDrawElements(GL_TRIANGLES, tri_vert_count, GL_UNSIGNED_INT, (void *) 0);

	return 1;
}

//Binds all data except MVP matrix
int Dynamic_Model::bind_mesh_data(Material* mat)
{
//	if(!gl_initialized)
//	{
//		LOGW("Warning: dynamic model data not bound, gl not initialized");
//		return 0;
//	}
	if(mat == NULL)
	{
		LOGW("Warning: tried rendering a static model without a material\n");
		return 0;
	}

	//test code:
	const float test_vertices[] =
	{
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	};
	mat->bind_value(Shader::PARAM_VERTICES,(void*) test_vertices);


	//mat->bind_value(Shader::PARAM_VERTICES, (void*) &verts[0]);

	mat->bind_value(Shader::PARAM_VERT_UV1, (void*) &uv_coords_1[0]);
	mat->bind_value(Shader::PARAM_VERT_UV2, (void*) &uv_coords_2[0]);

	mat->bind_value(Shader::PARAM_VERT_NORMALS, (void*) &normals[0]);
	mat->bind_value(Shader::PARAM_VERT_TANGENTS, (void*) &tangents[0]);
	mat->bind_value(Shader::PARAM_VERT_BINORMALS, (void*) &binormals[0]);

	//Mat4 mvp = vp * m;
	//mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

	//Mat3 m_it = m.inverted_then_transposed().get_mat3();
	//mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri_verts_buffer);
	return 1;
}

//Binds all data except MVP matrix and second uv coordinates
int Dynamic_Model::bind_mesh_data2(Material* mat)
{
	if(!gl_initialized)
	{
		LOGW("Warning: dynamic model data2 not bound, gl not initialized");
		return 0;
	}
	if(!mat)
	{
		LOGW("Warning: tried rendering a static model without assigning material\n");
		return 0;
	}

	//mat->bind_value(Shader::PARAM_VERTICES, (void*) verts);

	mat->bind_value(Shader::PARAM_VERT_UV1, (void*) uv_coords_1);

	mat->bind_value(Shader::PARAM_VERT_NORMALS, (void*) normals);
	mat->bind_value(Shader::PARAM_VERT_TANGENTS, (void*) tangents);
	mat->bind_value(Shader::PARAM_VERT_BINORMALS, (void*) binormals);

	//Mat4 mvp = vp * m;
	//mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

	//Mat3 m_it = m.inverted_then_transposed().get_mat3();
	//mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri_verts_buffer);
	return 1;
}
//Assumes all data is already bound
int Dynamic_Model::render_without_bind()
{
//	if(!gl_initialized)
//	{
//		LOGW("Warning: dynamic model not drawn without bind, gl not initialized");
//		return 0;
//	}
	glDrawElements(GL_TRIANGLES, tri_vert_count, GL_UNSIGNED_INT, (void *) 0);
	return 1;
}

int Dynamic_Model::init_gl()
{
	LOGE("model init gl: model set: %d, gl initialized: %d",model_set,gl_initialized);
	LOGE("Vert count: %d, tri vert count: %d",vertex_count,tri_vert_count);
	//if(gl_initialized || !model_set)
	//{
	//	LOGE("Abort model init gl because model was not set or gl was already on");
	//	return 1;
	//}

	//test code:
	tri_vert_count = 36;

	gl_initialized = true;
	glGenBuffers(1, &tri_verts_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri_verts_buffer);

	unsigned int test_tri_verts[] =
	{
	//Front quad
	0, 2, 1, 2, 0, 3,
	//Back quad
	4, 6, 5, 6, 4, 7,
	//Right quad
	1, 7, 4, 7, 1, 2,
	//Left quad
	0, 6, 3, 6, 0, 5,
	//Top quad
	4, 0, 1, 0, 4, 5,
	//Bottom quad
	6, 2, 3, 2, 6, 7,
	};
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(tri_vert_count * sizeof(unsigned int)), test_tri_verts, GL_STATIC_DRAW);


	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(tri_vert_count * sizeof(unsigned int)), &tri_verts[0], GL_STATIC_DRAW);
	LOGE("finished gl initializing the model");
	return 1;
}

void Dynamic_Model::term_gl()
{
	LOGE("model term gl: model set: %d, gl initialized: %d",model_set,gl_initialized);
//	if(!gl_initialized)
//	{
//		LOGE("Abort model term gl because gl was not on");
//		return;
//	}
//	gl_initialized = false;
	glDeleteBuffers(1,&tri_verts_buffer);
	LOGE("finished gl terminating the model");
}

//Adds a list of models together using model transforms (returns false if we ran out of room)
bool Dynamic_Model::populate_model (Static_Model **models, Mat4 *transforms, int model_count)
{
	//test code
	model_set = true;
	return true;





	//end test code

	LOGE("population of model began");
	if(gl_initialized)
	{
		LOGW("Warning: tried populating a dynamic model that was currently gl initialized");
		return true;
	}
	if(model_set)
	{
		clear_model();
	}

	vertex_count = 0;
	tri_vert_count = 0;
	LOGE("post gl check");

	model_set = true;
	Vec3 vert;

	int model_verts = 0;
	int model_tri_verts = 0;
	for(int i = 0; i < model_count; i++)
	{
		LOGE("--- copying model: %d",i);
		if(models[i] == NULL)
		{
			LOGW("Warning: null model in dynamic model list");
			continue;
		}

		model_verts = models[i]->vertex_count;
		model_tri_verts = models[i]->tri_vert_count;

		if(vertex_count + model_verts >= DYNAMIC_MODEL_ALLOCED_VERTS)
		{
			LOGE("Warning: ran out of vertices in dynamic model. (Used: %d / %d, needed: %d) Finished %d / %d models.",vertex_count,DYNAMIC_MODEL_ALLOCED_VERTS,model_verts,i,model_count-1);
			init_gl();
			return false;
		}
		if(tri_vert_count + model_tri_verts >= DYNAMIC_MODEL_ALLOCED_TRIS)
		{
			LOGE("Warning: ran out of tri vertices in dynamic model. (Used: %d / %d, needed: %d) Finished %d / %d models.",tri_vert_count,DYNAMIC_MODEL_ALLOCED_TRIS,model_tri_verts,i,model_count-1);
			init_gl();
			return false;
		}

		int ofs_vert_index = vertex_count;
		LOGE("Iterating through model vertices:");
		for(int j = 0; j < model_verts; j++)
		{
			LOGE("Copying vertex: %d / %d",j,model_verts);
			//Copying vertex positions
			vert = Vec3(models[i]->verts[3*j],models[i]->verts[3*j+1],models[i]->verts[3*j+2]);
			vert = transforms[i] * vert;
			verts[3*vertex_count] = vert.x;
			verts[3*vertex_count + 1] = vert.y;
			verts[3*vertex_count + 2] = vert.z;

			//Copying uv coords 1
			uv_coords_1[2*vertex_count] = models[i]->uv_coords_1[2*j];
			uv_coords_1[2*vertex_count + 1] = models[i]->uv_coords_1[2*j+1];
			//Copying uv coords 2
			uv_coords_2[2*vertex_count] = models[i]->uv_coords_2[2*j];
			uv_coords_2[2*vertex_count + 1] = models[i]->uv_coords_2[2*j+1];

			//I only plan on using translational transform matrices, so normals, tangents, and binormals can simply be copied over

			//Copying vertex normals
			normals[3*vertex_count] = models[i]->normals[3*j];
			normals[3*vertex_count + 1] = models[i]->normals[3*j+1];
			normals[3*vertex_count + 2] = models[i]->normals[3*j+2];
			//Copying vertex tangents
			tangents[3*vertex_count] = models[i]->tangents[3*j];
			tangents[3*vertex_count + 1] = models[i]->tangents[3*j+1];
			tangents[3*vertex_count + 2] = models[i]->tangents[3*j+2];
			//Copying vertex binormals
			binormals[3*vertex_count] = models[i]->binormals[3*j];
			binormals[3*vertex_count + 1] = models[i]->binormals[3*j+1];
			binormals[3*vertex_count + 2] = models[i]->binormals[3*j+2];

			vertex_count++;
		}
		LOGE("Copying tri verts");
		for(int j = 0; j < model_tri_verts; j++)
		{
			tri_verts[tri_vert_count] = models[i]->tri_verts[j] + ofs_vert_index;
			LOGE("Copying triangle vert: %d / %d, val = %d + %d = %d",j,model_tri_verts,models[i]->tri_verts[j],ofs_vert_index,tri_verts[tri_vert_count]);
			tri_vert_count++;
		}
		LOGE("Finished copying model");
	}
	LOGE("printing model:");
	for(int i = 0; i < vertex_count; i++)
	{
		LOGE("Vert[%d]: (%.2f, %.2f, %.2f), uv1: (%.2f, %.2f), uv2: (%.2f, %.2f), normal: (%.2f, %.2f, %.2f), tagent: (%.2f, %.2f, %.2f), binormal: (%.2f, %.2f, %.2f)",i,
		verts[3*i],verts[3*i+1],verts[3*i+2],
		uv_coords_1[2*i], uv_coords_1[2*i + 1],
		uv_coords_2[2*i], uv_coords_2[2*i + 1],
		normals[3*i], normals[3*i+1], normals[3*i + 2],
		tangents[3*i], tangents[3*i+1], tangents[3*i + 2],
		binormals[3*i], binormals[3*i+1], binormals[3*i + 2]);
	}
	for(int i = 0; i < tri_vert_count; i++)
	{
		LOGE("Tri Vert[%d] = %d)",i,tri_verts[i]);
	}
	LOGE("population of model ended, verts buffer: %d, vert count: %d, tri vert count: %d",tri_verts_buffer,vertex_count,tri_vert_count);
	//==============================================================================================================
	init_gl();
	LOGE("post init gl, verts buffer: %d",tri_verts_buffer);
	return true;
}
void Dynamic_Model::clear_model()
{
	return;




	LOGE("model being cleared");
	if(gl_initialized)
	{
		LOGE("Model GL terminated while being cleared");
		term_gl();
	}

	model_set = false;
	vertex_count = 0;
	tri_vert_count = 0;
	LOGE("model finished clearing");
}