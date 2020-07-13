#include "ObjToVbo.h"

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

void ObjToVbo::import_obj_file(char* obj_path) {
	ifstream input_file;
	string line;

	input_file.open(obj_path, fstream::out);

	smatch match;

	if (input_file.is_open()) {

		while (getline(input_file, line)) {

			//Vertex v x y z
			regex_search(line, match, v);
			if (!match.empty()) {
				positions_vec.push_back(vec3(stof(match[1]), stof(match[2]), stof(match[3])));
			}

			//Vertex Normals vn x y z
			regex_search(line, match, vn);
			if (!match.empty()) {
				normals_vec.push_back(vec3(stof(match[1]), stof(match[2]), stof(match[3])));
			}

			//Texture coordinates vt u v [w]
			regex_search(line, match, vt);
			if (!match.empty()) {
				textures_vec.push_back(vec2(stof(match[1]), stof(match[2])));
			}

			//Face format f v1 v2 v3 ...
			regex_search(line, match, f1);
			if (!match.empty()) {
				if (match.size() == 4) {
					Face* face = new Face();
					face->add_position(vec3(stoi(match[1]), stoi(match[2]), stoi(match[3])));
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
		}
	}
}

void ObjToVbo::load_mesh() {
	int index_count = 0;

	for (vector<Face*>::iterator it = faces.begin(); it != faces.end(); ++it) {
		Face* face = (*it);

		vec3 coords_ind = face->get_position_index();
		vec3 normals_ind = face->get_normal_index();
		vec3 textures_ind = face->get_texture_index();

		vec3 coords, normals;
		vec2 textures;
		Vertex* vertex_on_map;

		//Insert first vertex in face
		coords = positions_vec.at(coords_ind.x-1);
		normals = normals_vec.at(normals_ind.x-1);
		textures = textures_vec.at(textures_ind.x-1);

		Vertex ver1 = Vertex(coords, normals, textures);
		vertex_on_map = mesh.get_vertex(ver1);
		if (vertex_on_map == nullptr) {
			vertex_on_map = mesh.add_vertex(ver1);
		}
		vertex_on_map->addIndex(index_count++);

		//Insert second vertex in face
		coords = positions_vec.at(coords_ind.y-1);
		normals = normals_vec.at(normals_ind.y-1);
		textures = textures_vec.at(textures_ind.y-1);

		Vertex ver2 = Vertex(coords, normals, textures);
		vertex_on_map = mesh.get_vertex(ver2);
		if (vertex_on_map == nullptr) {
			vertex_on_map = mesh.add_vertex(ver2);
		}
		vertex_on_map->addIndex(index_count++);

		//Insert third vertex in face
		coords = positions_vec.at(coords_ind.z-1);
		normals = normals_vec.at(normals_ind.z-1);
		textures = textures_vec.at(textures_ind.z-1);

		Vertex ver3 = Vertex(coords, normals, textures);
		vertex_on_map = mesh.get_vertex(ver3);
		if (vertex_on_map == nullptr) {
			vertex_on_map = mesh.add_vertex(ver3);
		}
		vertex_on_map->addIndex(index_count++);
	}
}

void ObjToVbo::export_vbo_file(char* project_path) {
	ofstream vbo_file;
	vbo_file.open(project_path);

	int vertex_size = mesh.getSize();
	int index_size = faces.size() * 3;

	float *position_buffer, *normals_buffer, *textures_buffer;
	int* indexes_buffer;

	position_buffer = (float*)malloc(vertex_size * 3 * sizeof(float));
	normals_buffer = (float*)malloc(vertex_size * 3 * sizeof(float));
	textures_buffer = (float*)malloc(vertex_size * 2 * sizeof(float));
	indexes_buffer = (int*)malloc(index_size * sizeof(int));

	int vertex_count = 0;
	int normal_count = 0;
	int texture_count = 0;

	pair<unordered_multimap<string, Vertex>::iterator, unordered_multimap<string, Vertex>::iterator> mesh_its = mesh.getIterators();

	for (unordered_multimap<string, Vertex>::iterator it = mesh_its.first; it != mesh_its.second; ++it) {		
		Vertex v = it->second;

		vec3 position = v.getCoords();
		vec3 normal = v.getNormals();
		vec2 texture = v.getTextures();

		position_buffer[vertex_count++] = position.x;
		position_buffer[vertex_count++] = position.y;
		position_buffer[vertex_count++] = position.z;

		normals_buffer[normal_count++] = normal.x;
		normals_buffer[normal_count++] = normal.y;
		normals_buffer[normal_count++] = normal.z;

		textures_buffer[texture_count++] = texture.x;
		textures_buffer[texture_count++] = texture.y;

		vector<int> indexes_vector = v.getIndexes();
		
		for (auto vertex_it = indexes_vector.begin(); vertex_it != indexes_vector.end(); ++vertex_it) {
			indexes_buffer[*vertex_it] = (vertex_count-1)/3;
		}
	}

	vbo_file << "(" << vertex_size << "," << index_size << ")" << endl;

	for (int i = 0; i < vertex_count; i+=3) {
		vbo_file << position_buffer[i] << ":" << position_buffer[i + 1] << ":" << position_buffer[i + 2] << ":";
	}

	vbo_file << endl;

	for (int i = 0; i < normal_count; i += 3) {
		vbo_file << normals_buffer[i] << ":" << normals_buffer[i + 1] << ":" << normals_buffer[i + 2] << ":";
	}

	vbo_file << endl;

	for (int i = 0; i < texture_count; i += 2) {
		vbo_file << textures_buffer[i] << ":" << textures_buffer[i + 1] << ":";
	}

	vbo_file << endl;

	for (int i = 0; i < index_size; i++) {
		vbo_file << indexes_buffer[i] << ":" ;
	}

	vbo_file << endl;

	vbo_file.close();
}