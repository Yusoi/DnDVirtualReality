#include "Model.h"

#define POS_VBO 0 //Vertex Positions in VBO
#define NOR_VBO 1 //Normals in VBO
#define TEX_VBO 2 //Textures in VBO
#define IND_VBO 3 //Indexes in VBO

//Vertex
regex v("v +([-0-9.]+) +([-0-9.]+) +([-0-9.]+)(?: +[-0-9.]+)?");
//Vertex Normal
regex vn("vn +([-0-9.]+) +([-0-9.]+) +([-0-9.]+)");
//Vertex Texture Coordinate
regex vt("vt +([-0-9.]+) +([-0-9.]+)(?: +[-0-9.]+)?");
//Faces
regex f1("f +([0-9]+) +([0-9]+) +([0-9]+) +([0-9]+)?");
regex f2("f +([0-9]+)\\/([0-9]+) +([0-9]+)\\/([0-9]+) +([0-9]+)\\/([0-9]+) +([0-9]+)\\/([0-9]+)?");
regex f3("f +([0-9]+)\\/([0-9]+)\\/([0-9]+) +([0-9]+)\\/([0-9]+)\\/([0-9]+) +([0-9]+)\\/([0-9]+)\\/([0-9]+) +([0-9]+)\\/([0-9]+)\\/([0-9]+)?");
regex f4("f +([0-9]+)\\/\\/([0-9]+) +([0-9]+)\\/\\/([0-9]+) +([0-9]+)\\/\\/([0-9]+) +([0-9]+)\\/\\/([0-9]+)?");
//Smooth shading polygons (Not supported for now)
regex s("s +([0-9]+)");
//Group
regex g("g +(\\w+)");

Model::Model(char *name, char *path) {
	this->name = name;
	this->path = path;

	load_model(path);
}

void Model::load_model(char* path) {
	ifstream input_file;
	string line;

	input_file.open(path);

	smatch match;

	if (input_file.is_open()) {

		while (getline(input_file, line)) {

			//Vertex v x y z
			regex_search(line, match, v);
			if (!match.empty()) {
				positions.push_back(vec3(stof(match[1]), stof(match[2]), stof(match[3])));
			}

			//Vertex Normals vn x y z
			regex_search(line, match, vn);
			if (!match.empty()) {
				normals.push_back(vec3(stof(match[1]), stof(match[2]), stof(match[3])));
			}

			//Texture coordinates vt u v [w]
			regex_search(line, match, vt);
			if (!match.empty()) {
				textureCoords.push_back(vec2(stof(match[1]), stof(match[2])));
			}

			//Face format f v1 v2 v3 ...
			regex_search(line, match, f1);
			if (!match.empty()) {
				if (match.size() == 4) {
					Face* face = new Face();
					face->add_position(vec3(stoi(match[1]),stoi(match[2]),stoi(match[3])));
					faces.push_back(face);
				}
				else if (match.size() == 5) {
					Face* face1 = new Face();
					face1->add_position(vec3(stoi(match[1]), stoi(match[2]), stoi(match[3])));
					faces.push_back(face1);

					Face* face2 = new Face();
					face2->add_position(vec3(stoi(match[3]), stoi(match[4]), stoi(match[1])));
					faces.push_back(face2);
				}
			}

			//Face format f v1/vt1 v2/vt2 v3/vt3 ...
			regex_search(line, match, f2);
			if (!match.empty()) {
				if (match.size() == 7) {
					Face* face = new Face();
					face->add_position(vec3(stoi(match[1]), stoi(match[3]), stoi(match[5])));
					face->add_texture(vec3(stoi(match[2]), stoi(match[4]), stoi(match[6])));
					faces.push_back(face);
				}
				else if (match.size() == 9) {
					Face* face1 = new Face();
					face1->add_position(vec3(stoi(match[1]), stoi(match[3]), stoi(match[5])));
					face1->add_texture(vec3(stoi(match[2]), stoi(match[4]), stoi(match[6])));
					faces.push_back(face1);

					Face* face2 = new Face();
					face2->add_position(vec3(stoi(match[5]), stoi(match[7]), stoi(match[1])));
					face2->add_texture(vec3(stoi(match[6]), stoi(match[8]), stoi(match[2]))); 
					faces.push_back(face2);
				}
			}

			//Face format f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ...
			regex_search(line, match, f3);
			if (!match.empty()) {
				if (match.size() == 10) {
					Face* face = new Face();
					face->add_position(vec3(stoi(match[1]), stoi(match[4]), stoi(match[7])));
					face->add_texture(vec3(stoi(match[2]), stoi(match[5]), stoi(match[8])));
					face->add_normal(vec3(stoi(match[3]), stoi(match[6]), stoi(match[9])));
					faces.push_back(face);
				}
				else if (match.size() == 13) {
					Face* face1 = new Face();
					face1->add_position(vec3(stoi(match[1]), stoi(match[4]), stoi(match[7])));
					face1->add_texture(vec3(stoi(match[2]), stoi(match[5]), stoi(match[8])));
					face1->add_normal(vec3(stoi(match[3]), stoi(match[6]), stoi(match[9])));
					faces.push_back(face1);

					Face* face2 = new Face();
					face2->add_position(vec3(stoi(match[7]), stoi(match[10]), stoi(match[1])));
					face2->add_texture(vec3(stoi(match[8]), stoi(match[11]), stoi(match[2])));
					face2->add_normal(vec3(stoi(match[9]), stoi(match[12]), stoi(match[3])));
					faces.push_back(face2);
				}
				
			}

			//Face format f v1//vn1 v2//vn2 v3//vn3 ...
			regex_search(line, match, f4);
			if (!match.empty()) {
				if (match.size() == 7) {
					Face* face = new Face();
					face->add_position(vec3(stoi(match[1]), stoi(match[3]), stoi(match[5])));
					face->add_normal(vec3(stoi(match[2]), stoi(match[4]), stoi(match[6])));
					faces.push_back(face);
				}
				else if (match.size() == 9) {
					Face* face1 = new Face();
					face1->add_position(vec3(stoi(match[1]), stoi(match[3]), stoi(match[5])));
					face1->add_normal(vec3(stoi(match[2]), stoi(match[4]), stoi(match[6])));
					faces.push_back(face1);

					Face* face2 = new Face();
					face2->add_position(vec3(stoi(match[5]), stoi(match[7]), stoi(match[1])));
					face2->add_normal(vec3(stoi(match[6]), stoi(match[8]), stoi(match[2])));
					faces.push_back(face2);
				}
				
			}

			/* Not supported yet
			regex_search(line, match, s);
			if (!match.empty()) {
				cout << "s ";
				for (int i = 1; i < match.size(); i++) {
					cout << match[i] << " ";
				}
				cout << "\n";
			}*/

			/* Not supported yet
			regex_search(line, match, g);
			if (!match.empty()) {
				cout << "g ";
				for (int i = 1; i < match.size(); i++) {
					cout << match[i] << " ";
				}
				cout << "\n";
			}*/
		}
	}

	buffer_size[0] = positions.size();
	buffer_size[1] = normals.size();
	buffer_size[2] = textureCoords.size();
	buffer_size[3] = faces.size();

	prepare_vao();
}

void Model::prepare_vao() {
	//Provisóriamente o tamanho dos índices é igual ao tamanho de faces
	unsigned long long vertices_size = faces.size() * 3;

	float* positions_array = (float*)malloc(sizeof(float) * vertices_size * 3);
	float* textures_array = (float*)malloc(sizeof(float) * vertices_size * 2);
	float* normals_array = (float*)malloc(sizeof(float) * vertices_size * 3);
	int* indexes_array = (int*)malloc(sizeof(int) * vertices_size * 3);

	int pos_index = 0;
	int tex_index = 0;
	int norm_index = 0;
	int index = 0;

	for (vector<Face*>::iterator face_it = faces.begin(); face_it < faces.end(); ++face_it) {
		Face* face = (*face_it);
		vec3 pos_ind = face->get_position_index();
		vec3 tex_ind = face->get_texture_index();
		vec3 norm_ind = face->get_normal_index();

		vec3 pos_x = positions.at(pos_ind.x-1);
		vec3 pos_y = positions.at(pos_ind.y-1);
		vec3 pos_z = positions.at(pos_ind.z-1);

		vec2 tex_x = textureCoords.at(tex_ind.x-1);
		vec2 tex_y = textureCoords.at(tex_ind.y-1);
		vec2 tex_z = textureCoords.at(tex_ind.z-1);

		vec3 norm_x = normals.at(norm_ind.x-1);
		vec3 norm_y = normals.at(norm_ind.y-1);
		vec3 norm_z = normals.at(norm_ind.z-1);

		positions_array[pos_index++] = pos_x.x;
		positions_array[pos_index++] = pos_x.y;
		positions_array[pos_index++] = pos_x.z;
		positions_array[pos_index++] = pos_y.x;
		positions_array[pos_index++] = pos_y.y;
		positions_array[pos_index++] = pos_y.z;
		positions_array[pos_index++] = pos_z.x;
		positions_array[pos_index++] = pos_z.y;
		positions_array[pos_index++] = pos_z.z;

		textures_array[tex_index++] = tex_x.x;
		textures_array[tex_index++] = tex_x.y;
		textures_array[tex_index++] = tex_y.x;
		textures_array[tex_index++] = tex_y.y;
		textures_array[tex_index++] = tex_z.x;
		textures_array[tex_index++] = tex_z.y;

		normals_array[norm_index++] = norm_x.x;
		normals_array[norm_index++] = norm_x.y;
		normals_array[norm_index++] = norm_x.z;
		normals_array[norm_index++] = norm_y.x;
		normals_array[norm_index++] = norm_y.y;
		normals_array[norm_index++] = norm_y.z;
		normals_array[norm_index++] = norm_z.x;
		normals_array[norm_index++] = norm_z.y;
		normals_array[norm_index++] = norm_z.z;

		for (int i = index; index < i+9; index++) {
			indexes_array[index] = index;
		}
		
	}

	buffer_size[POS_VBO] = vertices_size * 3;
	buffer_size[TEX_VBO] = vertices_size * 2;
	buffer_size[NOR_VBO] = vertices_size * 3;
	buffer_size[IND_VBO] = vertices_size * 3;

	cout << "We out boys" << endl;
	cout << "Pos Index: " << pos_index << endl;
	cout << "Index: " << index << endl;
	cout << "Faces size: " << faces.size() << endl;
	cout << "Vertices size: " << vertices_size << endl;



	glGenVertexArrays(1,&m_VAO);
	glBindVertexArray(m_VAO);

	/**
	* Generates 4 buffers:
	* 1 - Vertex Positions
	* 2 - Vertex Textures
	* 3 - Vertex Normals
	* 4 - Indexes
	*/
	glGenBuffers(4, m_buffers);

	glBindBuffer(GL_ARRAY_BUFFER,m_buffers[POS_VBO]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_size * 3, positions_array, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[TEX_VBO]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_size * 2, textures_array, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[NOR_VBO]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_size * 3, normals_array, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[IND_VBO]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * vertices_size * 3, indexes_array, GL_STATIC_DRAW);

	//Unbind the VAO at the end;
	glBindVertexArray(0);

	free(positions_array);
	free(normals_array);
	free(textures_array);
	free(indexes_array);

}

void Model::drawVAO() {
	glBindVertexArray(m_VAO);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	GLfloat position[] = { 200.0, 200.0, 200.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	//glDrawArrays(GL_TRIANGLES, 0, buffer_size[POS_VBO] * 3);
	glDrawElements(GL_TRIANGLES, buffer_size[POS_VBO] * 3, GL_UNSIGNED_INT, 0);
	glDisable(GL_LIGHTING);
	
	//Unbind the VAO
	glBindVertexArray(0);
}

void Model::draw() {
	//cout << "Vertices size: " << vertices.size() << "\n";
	//cout << "Faces size: " << faces.size() << "\n";
	
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
}

//Print for Debugging
void Model::print() {
	cout << name << "\n";
	cout << path << "\n";
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
}