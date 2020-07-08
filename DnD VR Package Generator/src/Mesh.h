#include <vector>
#include <map>

#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "glm/glm.hpp"

using namespace std;
using namespace glm;

class Mesh {
private:
	multimap<vec3,Vertex> mesh;
	vector<vec3> indices;
public:
	void add_vertex(Vertex vertex);
	void create_vertex(vec3 coords, vec3 normals, vec3 textures);
};

class Vertex {
private:
	vec3 coords;
	vec3 normals;
	vec3 textures;
public:
	vec3 getCoords();
	vec3 getNormals();
	vec3 getTextures();
	void setCoords(vec3 coords);
	void setNormals(vec3 normals);
	void setTextures(vec3 textures);
};
