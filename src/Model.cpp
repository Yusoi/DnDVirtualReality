#include "Model.h"

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

	ifstream input_file;
	string line;

	input_file.open(path);

	smatch match;

	if (input_file.is_open()) {

		while (getline(input_file, line)) {

			//Vertex v x y z
			regex_search(line, match, v);
			if (!match.empty()) {
				vertices.push_back(vec3(stod(match[1]), stod(match[2]), stod(match[3])));
			}

			//Vertex Normals vn x y z
			regex_search(line, match, vn);
			if (!match.empty()) {
				normals.push_back(vec3(stod(match[1]), stod(match[2]), stod(match[3])));
			}

			//Texture coordinates vt u v [w]
			regex_search(line, match, vt);
			if (!match.empty()) {
				textureCoords.push_back(vec2(stod(match[1]), stod(match[2])));
			}

			//Face format f v1 v2 v3 ...
			regex_search(line, match, f1);
			if (!match.empty()) {
				Face *face = new Face(1);
				for (int i = 1; i < match.size(); i++) {
					face->add_vertex(stoi(match[i]));
				}
				faces.push_back(face);
			}

			//Face format f v1/vt1 v2/vt2 v3/vt3 ...
			regex_search(line, match, f2);
			if (!match.empty()) {
				Face *face = new Face(2);
				for (int i = 1; i < match.size(); i+=2) {
					face->add_vertex(stoi(match[i]));
					face->add_texture(stoi(match[i + 1]));
				}
				faces.push_back(face);
			}

			//Face format f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ...
			regex_search(line, match, f3);
			if (!match.empty()) {
				Face *face = new Face(3);
				for (int i = 1; i < match.size(); i+=3) {
					face->add_vertex(stoi(match[i]));
					face->add_texture(stoi(match[i + 1]));
					face->add_normal(stoi(match[i + 2]));
				}
				faces.push_back(face);
			}

			//Face format f v1//vn1 v2//vn2 v3//vn3 ...
			regex_search(line, match, f4);
			if (!match.empty()) {
				Face *face = new Face(4);
				for (int i = 1; i < match.size(); i+=2) {
					face->add_vertex(stoi(match[i]));
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
		}

		vector<int>* vertex_indexes = face->get_vertex_index();

		for (vector<int>::iterator vertex_it = vertex_indexes->begin(); vertex_it < vertex_indexes->end(); ++vertex_it) {
			int vertex_index = (*vertex_it);

			vec3 vertex = vertices.at(vertex_index-1);
			cout << "Vertex Index: " << vertex_index << " Vertex: " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
			glVertex3d(vertex.x,vertex.y,vertex.z);

		}

		glEnd();
	}
	
}

//Print for Debugging
void Model::print() {
	cout << name << "\n";
	cout << path << "\n";
	cout << "Vertices - Size: " << vertices.size() << "\n";
	for (vector<vec3>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
		cout << ((vec3)*it).x << " " << ((vec3)*it).y << " " << ((vec3)*it).z << "\n";
	}
	cout << "Texture Coordinates - Size: " << textureCoords.size() << "\n";
	for (vector<vec2>::iterator it = textureCoords.begin(); it != textureCoords.end(); ++it) {
		cout << ((vec2)*it).x << " " << ((vec2)*it).y << "\n";
	}
	cout << "Normals - Size: " << normals.size() << "\n";
	for (vector<vec3>::iterator it = normals.begin(); it != normals.end(); ++it) {
		cout << ((vec3)*it).x << " " << ((vec3)*it).y << " " << ((vec3)*it).z << "\n";
	}
}