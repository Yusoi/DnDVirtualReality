#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>

#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"

using namespace std;
using namespace glm;

class Vertex {
private:
	vec3 coords;
	vec3 normals;
	vec2 textures;
	vector<int> indexes;
public:
	Vertex(vec3 coords, vec3 normals, vec2 textures);
	vec3 getCoords();
	vec3 getNormals();
	vec2 getTextures();
	vector<int> getIndexes();
	void setCoords(vec3 coords);
	void setNormals(vec3 normals);
	void setTextures(vec2 textures);
	void addIndex(int index);
	bool equals(Vertex vertex);
};

class Mesh {
private:
	unordered_multimap<string,Vertex> mesh;
public:
	Mesh();
	Vertex* add_vertex(Vertex vertex);
	Vertex* get_vertex(Vertex vertex);
	pair<unordered_multimap<string, Vertex>::iterator, unordered_multimap<string, Vertex>::iterator> getIterators();
	int getSize();
	
};

