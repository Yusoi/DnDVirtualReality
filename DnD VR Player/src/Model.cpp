#include "Model.h"

#define POS_VBO 0 //Vertex Positions in VBO
#define NOR_VBO 1 //Normals in VBO
#define TEX_VBO 2 //Textures in VBO
#define IND_VBO 3 //Indexes in VBO

regex value("[0-9\\.e\\-]+");
regex size_buffer("\\(([0-9]+),([0-9]+)\\)");

Model::Model(char *name, const char *obj_path, const char *tex_path) {
	this->name = name;
	this->obj_path = obj_path;
	this->tex_path = tex_path;

	cout << "Object path: " << obj_path << " Texture path: " << tex_path << endl;

	load_texture(tex_path);
	load_model(obj_path);
}

void Model::load_model(const char* obj_path) {
	ifstream input_file;
	string line;

	input_file.open(obj_path);

	smatch match;

	if (input_file.is_open()) {

		getline(input_file, line);
		regex_search(line, match, size_buffer);

		if (match.size() == 3) {
			int vertex_size = stoi(match[1]);
			int indices_size = stoi(match[2]);

			buffer_size[POS_VBO] = vertex_size * 3;
			buffer_size[NOR_VBO] = vertex_size * 3;
			buffer_size[TEX_VBO] = vertex_size * 2;
			buffer_size[IND_VBO] = indices_size;

			positions_array = (float*)malloc(sizeof(float) * buffer_size[POS_VBO]);
			textures_array = (float*)malloc(sizeof(float) * buffer_size[TEX_VBO]);
			normals_array = (float*)malloc(sizeof(float) * buffer_size[NOR_VBO]);
			indexes_array = (int*)malloc(sizeof(int) * buffer_size[IND_VBO]);

		}

		const sregex_token_iterator end;
		int positions_count = 0;
		int normals_count = 0;
		int textures_count = 0;
		int indexes_count = 0;

		getline(input_file, line);
		for (sregex_token_iterator it(line.begin(), line.end(), value); it != end; it++)
		{
			positions_array[positions_count++] = stof(*it);
		}

		getline(input_file, line);
		for (sregex_token_iterator it(line.begin(), line.end(), value); it != end; it++)
		{
			normals_array[normals_count++] = stof(*it);
		}

		getline(input_file, line);
		for (sregex_token_iterator it(line.begin(), line.end(), value); it != end; it++)
		{
			textures_array[textures_count++] = stof(*it);
		}

		getline(input_file, line);
		for (sregex_token_iterator it(line.begin(), line.end(), value); it != end; it++)
		{
			indexes_array[indexes_count++] = stoi(*it);
		}
	}

	prepare_vao();
}


void Model::prepare_vao() {
	//Provisóriamente o tamanho dos índices é igual ao tamanho de faces
	//unsigned long long vertices_size = faces.size() * 3;

	int pos_index = 0;
	int tex_index = 0;
	int norm_index = 0;
	int index = 0;

	//glGenVertexArrays(1,&m_VAO);
	//glBindVertexArray(m_VAO);

	/**
	* Generates 4 buffers:
	* 1 - Vertex Positions
	* 2 - Vertex Textures
	* 3 - Vertex Normals
	* 4 - Indexes
	*/
	glGenBuffers(4, m_buffers);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[POS_VBO]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_size[POS_VBO], positions_array, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[TEX_VBO]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_size[TEX_VBO], textures_array, GL_STATIC_DRAW);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[NOR_VBO]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_size[NOR_VBO], normals_array, GL_STATIC_DRAW);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[IND_VBO]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * buffer_size[IND_VBO], indexes_array, GL_STATIC_DRAW);

	//Unbind the VAO at the end;
	//glBindVertexArray(0);

	free(positions_array);
	free(normals_array);
	free(textures_array);
	free(indexes_array);

}

void Model::load_texture(const char* tex_path) {
	unsigned int tex, tex_w, tex_h;
	unsigned char* texData;

	char* tex_path_char = strdup(tex_path);

	ilGenImages(1,&tex);
	ilBindImage(tex);
	if (!ilLoadImage((ILstring)tex_path_char)) {
		cout << ilGetError() << endl;
		exit(1);
	}
	tex_w = ilGetInteger(IL_IMAGE_WIDTH);
	tex_h = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	if (ilGetError() != IL_NO_ERROR) {
		cout << "Devil get error: " << ilGetError() << endl;
	}
	
	glGenTextures(1, &tex_buffer);

	glBindTexture(GL_TEXTURE_2D, tex_buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_w, tex_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);

	glBindTexture(GL_TEXTURE_2D, 0);

}

void Model::drawVAO(Shader* shader) {
	
	GLuint p = shader->getProgramId();

	//glBindVertexArray(m_VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[POS_VBO]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[NOR_VBO]);
	glNormalPointer(GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[TEX_VBO]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glBindTexture(GL_TEXTURE_2D, tex_buffer);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	GLfloat position[] = { 200.0, 200.0, 200.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[IND_VBO]);

	//glUseProgram(p);
	//GLfloat viewmodel_mat[16], projection_mat[16];

	//glGetFloatv(GL_MODELVIEW, viewmodel_mat);
	//GLint viewModel = glGetUniformLocation(p, "m_viewModel");
	//glUniformMatrix4fv(viewModel, 1, GL_FALSE, viewmodel_mat);

	glDrawElements(GL_TRIANGLES, buffer_size[IND_VBO], GL_UNSIGNED_INT, (void*)0);

	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	//Unbind the VAO
	//glBindVertexArray(0);
	
}


void Model::draw() {
	//cout << "Vertices size: " << vertices.size() << "\n";
	//cout << "Faces size: " << faces.size() << "\n";
	/*
	for (vector<Face*>::iterator it = faces.begin(); it < faces.end(); ++it) {
		Face *face = (*it);
		glBegin(GL_TRIANGLES);

		vec3 position_indexes = face->get_position_index();

		vec3 pos1 = positions.at(position_indexes.x - 1);
		glVertex3f(pos1.x, pos1.y, pos1.z);
		vec3 pos2 = positions.at(position_indexes.y - 1);
		glVertex3f(pos2.x, pos2.y, pos2.z);
		vec3 pos3 = positions.at(position_indexes.z - 1);
		glVertex3f(pos3.x, pos3.y, pos3.z);
		
		glEnd();
	}
	*/
}

//Print for Debugging
void Model::print() {
	cout << name << "\n";
	cout << obj_path << "\n";
	cout << tex_path << "\n";
	/*
	cout << "Positions - Size: " << positions.size() << "\n";
	for (vector<vec3>::iterator it = positions.begin(); it != positions.end(); ++it) {
		cout << ((vec3)*it).x << " " << ((vec3)*it).y << " " << ((vec3)*it).z << "\n";
	}
	cout << "Normals - Size: " << normals.size() << "\n";
	for (vector<vec3>::iterator it = normals.begin(); it != normals.end(); ++it) {
		cout << ((vec3)*it).x << " " << ((vec3)*it).y << " " << ((vec3)*it).z << "\n";
	}
	cout << "Texture Coordinates - Size: " << textureCoords.size() << "\n";
	for (vector<vec2>::iterator it = textureCoords.begin(); it != textureCoords.end(); ++it) {
		cout << ((vec2)*it).x << " " << ((vec2)*it).y << "\n";
	}
	*/
	/*
	cout << "Faces - Size: " << faces.size() << "\n";
	for (vector<Face*>::iterator it = faces.begin(); it != faces.end(); ++it) {
		Face* f = (*it);
		vec3 pos = f->get_position_index();
		vec3 nor = f->get_normal_index();
		vec3 tex = f->get_texture_index();
		cout << "Pos: " << pos.x << " " << pos.y << " " << pos.z << "\n";
		cout << "Nor: " << nor.x << " " << nor.y << " " << nor.z << "\n";
		cout << "Tex: " << tex.x << " " << tex.y << " " << tex.z << "\n";
	}
	*/
}

string Model::getName() {
	return name;
}