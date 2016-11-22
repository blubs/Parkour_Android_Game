//
// Created by F1 on 5/5/2016.
//

#include "Static_Model.hpp"
int Static_Model::render(Mat4 m,Mat4 vp,Material* mat)
{
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
int Static_Model::bind_mesh_data(Material* mat)
{
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

	//Mat4 mvp = vp * m;
	//mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

	//Mat3 m_it = m.inverted_then_transposed().get_mat3();
	//mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri_verts_buffer);
}

//Binds all data except MVP matrix and second uv coordinates
int Static_Model::bind_mesh_data2(Material* mat)
{
	if(!mat)
	{
		LOGW("Warning: tried rendering a static model without assigning material\n");
		return 0;
	}

	mat->bind_value(Shader::PARAM_VERTICES, (void*) verts);

	mat->bind_value(Shader::PARAM_VERT_UV1, (void*) uv_coords_1);

	mat->bind_value(Shader::PARAM_VERT_NORMALS, (void*) normals);
	mat->bind_value(Shader::PARAM_VERT_TANGENTS, (void*) tangents);
	mat->bind_value(Shader::PARAM_VERT_BINORMALS, (void*) binormals);

	//Mat4 mvp = vp * m;
	//mat->bind_value(Shader::PARAM_MVP_MATRIX, (void*) mvp.m);

	//Mat3 m_it = m.inverted_then_transposed().get_mat3();
	//mat->bind_value(Shader::PARAM_M_IT_MATRIX, (void*) m_it.m);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri_verts_buffer);
}
//Assumes all data is already bound
int Static_Model::render_without_bind()
{
	glDrawElements(GL_TRIANGLES, tri_vert_count, GL_UNSIGNED_INT, (void *) 0);
	return 1;
}

int Static_Model::load_model(const char* filepath)
{
	raw_data = (unsigned int*) File_Utils::load_raw_asset(filepath);
	if(!raw_data)
	{
		LOGE("Error: failed to load \"%s\"\n",filepath);
		return 0;
	}

	//File Schematics
	//First int is the vertex count
	//Second int is the triangle count * 3
	//List thereafter is the position (3 floats) of all vertices
	//List thereafter is the uv tex coords of the 1st uv map (2 floats) of all vertices
	//List thereafter is the uv tex coords of the 2nd uv map (2 floats) of all vertices
	//List thereafter is the normals (3 floats) of all vertices
	//List thereafter is the tangents (3 floats) of all vertices
	//List thereafter is the binormals (3 floats) of all vertices
	//List thereafter is the indices of vertices that make up the triangles
	vertex_count = raw_data[0];
	tri_vert_count = raw_data[1];

	verts = (float*) (raw_data + 2);

	uv_coords_1 = (float*) raw_data + 2 + (vertex_count*3);
	uv_coords_2 = (float*) raw_data + 2 + (vertex_count*3) + (vertex_count*2);

	normals = (float*) raw_data + 2 + (vertex_count*3) + 2*(vertex_count*2);
	tangents = (float*) raw_data + 2 + 2*(vertex_count*3) + 2*(vertex_count*2);
	binormals = (float*) raw_data + 2 + 3*(vertex_count*3) + 2*(vertex_count*2);

	tri_verts = raw_data + 2 + 4*(vertex_count*3) + 2*(vertex_count*2);

	return 1;
}

int Static_Model::init_gl()
{
	glGenBuffers(1, &tri_verts_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri_verts_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(tri_vert_count * sizeof(unsigned int)), tri_verts, GL_STATIC_DRAW);

	return 1;
}

void Static_Model::term_gl()
{
	glDeleteBuffers(1,&tri_verts_buffer);
}
void Static_Model::unload_model()
{
	if(raw_data)
		free((void*)raw_data);
}
//Loads a static model from file
Static_Model::Static_Model(const char* filepath)
{
	load_model(filepath);
}
//Copies the other static model
Static_Model::Static_Model(Static_Model* other)
{
	int raw_data_size = 2 + (16 * other->vertex_count) + other->tri_vert_count;

	unsigned int* temp_raw_data = NULL;
	temp_raw_data = (unsigned int*) malloc(sizeof(int) * raw_data_size);

	if(!temp_raw_data)
	{
		LOGE("Error: failed to allocate memory for raw data when copying a static model");
		return;
	}

	//Copying this the other model's raw data
	for(int i = 0; i < raw_data_size; i++)
	{
		temp_raw_data[i] = other->raw_data[i];
	}
	raw_data = temp_raw_data;
	//Setting up references to the appropriate indices (just as load_model does)
	//File Schematics
	//First int is the vertex count
	//Second int is the triangle count * 3
	//List thereafter is the position (3 floats) of all vertices
	//List thereafter is the uv tex coords of the 1st uv map (2 floats) of all vertices
	//List thereafter is the uv tex coords of the 2nd uv map (2 floats) of all vertices
	//List thereafter is the normals (3 floats) of all vertices
	//List thereafter is the tangents (3 floats) of all vertices
	//List thereafter is the binormals (3 floats) of all vertices
	//List thereafter is the indices of vertices that make up the triangles
	vertex_count = raw_data[0];
	tri_vert_count = raw_data[1];

	verts = (float*) (raw_data + 2);

	uv_coords_1 = (float*) raw_data + 2 + (vertex_count*3);
	uv_coords_2 = (float*) raw_data + 2 + (vertex_count*3) + (vertex_count*2);

	normals = (float*) raw_data + 2 + (vertex_count*3) + 2*(vertex_count*2);
	tangents = (float*) raw_data + 2 + 2*(vertex_count*3) + 2*(vertex_count*2);
	binormals = (float*) raw_data + 2 + 3*(vertex_count*3) + 2*(vertex_count*2);

	tri_verts = raw_data + 2 + 4*(vertex_count*3) + 2*(vertex_count*2);
}
//Combines two static models together
Static_Model::Static_Model(Static_Model* model1, Mat4 model1_trans, Static_Model* model2, Mat4 model2_trans)
{
	//TODO combine the two meshes
}
Static_Model::~Static_Model()
{
	unload_model();
}