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
				Face* face = new Face(1);
				for (int i = 1; i < match.size(); i++) {
					face->add_position(stoi(match[i]));
				}
				faces.push_back(face);
			}

			//Face format f v1/vt1 v2/vt2 v3/vt3 ...
			regex_search(line, match, f2);
			if (!match.empty()) {
				Face* face = new Face(2);
				for (int i = 1; i < match.size(); i += 2) {
					face->add_position(stoi(match[i]));
					face->add_texture(stoi(match[i + 1]));
				}
				faces.push_back(face);
			}

			//Face format f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ...
			regex_search(line, match, f3);
			if (!match.empty()) {
				Face* face = new Face(3);
				for (int i = 1; i < match.size(); i += 3) {
					face->add_position(stoi(match[i]));
					face->add_texture(stoi(match[i + 1]));
					face->add_normal(stoi(match[i + 2]));
				}
				faces.push_back(face);
			}

			//Face format f v1//vn1 v2//vn2 v3//vn3 ...
			regex_search(line, match, f4);
			if (!match.empty()) {
				Face* face = new Face(4);
				for (int i = 1; i < match.size(); i += 2) {
					face->add_position(stoi(match[i]));
					face->add_normal(stoi(match[i + 1]));
				}
				faces.push_back(face);
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
}

void Model::prepare_vao() {
	unsigned long long positions_array_size = sizeof(float) * buffer_size[POS_VBO] * 3;
	unsigned long long normals_array_size = sizeof(float) * buffer_size[NOR_VBO] * 3;
	unsigned long long textures_array_size = sizeof(float) * buffer_size[TEX_VBO] * 2;
	unsigned long long indexes_array_size = sizeof(float) * buffer_size[IND_VBO] * 3;
	
	float* positions_array = (float*) malloc(positions_array_size);
	float* normals_array = (float*) malloc(normals_array_size);
	float* textures_array = (float*) malloc(textures_array_size);
	float* indexes_array = (float*) malloc(indexes_array_size);


	int index = 0;
	for (vector<vec3>::iterator pos_it = positions.begin(); pos_it < positions.end(); ++pos_it) {
		positions_array[index] = (float)(*pos_it).x;
		positions_array[index+1] = (float)(*pos_it).y;
		positions_array[index + 2] = (float)(*pos_it).z;
		index += 3;
	}

	index = 0;
	for (vector<vec3>::iterator norm_it = normals.begin(); norm_it < normals.end(); ++norm_it) {
		normals_array[index] = (float)(*norm_it).x;
		normals_array[index + 1] = (float)(*norm_it).y;
		normals_array[index + 2] = (float)(*norm_it).z;
		index += 3;
	}

	index = 0;
	for (vector<vec2>::iterator tex_it = textureCoords.begin(); tex_it < textureCoords.end(); ++tex_it) {
		textures_array[index] = (float)(*tex_it).x;
		textures_array[index + 1] = (float)(*tex_it).y;
		index += 2;
	}

	index = 0;
	for (vector<vec3>::iterator norm_it = normals.begin(); norm_it < normals.end(); ++norm_it) {
		normals_array[index] = (float)(*norm_it).x;
		normals_array[index + 1] = (float)(*norm_it).y;
		normals_array[index + 2] = (float)(*norm_it).z;
		index += 3;
	}

	glGenVertexArrays(1,&m_VAO);
	glBindVertexArray(m_VAO);


	glGenBuffers(4, m_buffers);
	glBindBuffer(GL_ARRAY_BUFFER,m_buffers[POS_VBO]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions_array[0]) * positions_array_size, positions_array, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[NOR_VBO]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals_array[0]) * normals_array_size, normals_array, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_buffers[TEX_VBO]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textures_array[0]) * textures_array_size, textures_array, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[IND_VBO]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes_array[0]) * indexes_array_size, indexes_array, GL_STATIC_DRAW);




	//Unbind the VAO at the end;
	glBindVertexArray(0);

	free(positions_array);
	free(normals_array);
	free(textures_array);
	free(indexes_array);

}

void Model::drawVAO() {
	glBindVertexArray(m_VAO);

	/*
	glDrawElementsBaseVertex(GL_TRIANGLES,
							 faces.size(),
							 GL_UNSIGNED_INT,
							 indexe)*/

	//glDrawElements(GL_TRIANGLES, faces.size(), GL_UNSIGNED_INT, );

	//Unbind the VAO
	glBindVertexArray(0);
}

void Model::draw() {
	//cout << "Vertices size: " << vertices.size() << "\n";
	//cout << "Faces size: " << faces.size() << "\n";
	
	for (vector<Face*>::iterator it = faces.begin(); it < faces.end(); ++it) {
		Face *face = (*it);
		switch (face->size()) {
		case 3:
			glBegin(GL_TRIANGLES);
			break;
		case 4:
			glBegin(GL_QUADS);
			break;
		default:
			cout << "No\n";
		}

		vector<int>* vertex_indexes = face->get_position_index();

		for (vector<int>::iterator vertex_it = vertex_indexes->begin(); vertex_it < vertex_indexes->end(); ++vertex_it) {
			int vertex_index = (*vertex_it);

			vec3 vertex = positions.at(vertex_index-1);
			glVertex3f(vertex.x,vertex.y,vertex.z);

		}

		glEnd();
	}
}

//Print for Debugging
void Model::print() {
	cout << name << "\n";
	cout << path << "\n";
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
}