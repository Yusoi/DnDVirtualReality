#include "Mesh.h"

Vertex::Vertex(vec3 coords, vec3 normals, vec2 textures) {
	this->coords = coords;
	this->normals = normals;
	this->textures = textures;
}

vec3 Vertex::getCoords() {
	return coords;
}

vec3 Vertex::getNormals() {
	return normals;
}

vec2 Vertex::getTextures() {
	return textures;
}

vector<int> Vertex::getIndexes() {
	return indexes;
}

void Vertex::setCoords(vec3 coords) {
	this->coords = coords;
}

void Vertex::setNormals(vec3 normals) {
	this->normals = normals;
}

void Vertex::setTextures(vec2 textures) {
	this->textures = textures;
}

void Vertex::addIndex(int index) {
	indexes.push_back(index);
}

bool Vertex::equals(Vertex vertex) {
	return all(equal(this->coords, vertex.coords)) &&
		all(equal(this->normals, vertex.normals)) &&
		all(equal(this->textures, vertex.textures));
}

Mesh::Mesh() {
}

Vertex* Mesh::add_vertex(Vertex vertex) {
	return &mesh.insert(pair<vec3,Vertex>(vertex.getCoords(), vertex))->second;
}

Vertex* Mesh::get_vertex(Vertex vertex) {
	pair<multimap<vec3, Vertex>::iterator,multimap<vec3, Vertex>::iterator> equal_map 
		= mesh.equal_range(vertex.getCoords());

	for (multimap<vec3, Vertex>::iterator it = equal_map.first; it != equal_map.second; ++it) {
		if (it->second.equals(vertex)) {
			return &it->second;
		}
	}

	return nullptr;
}

multimap<vec3, Vertex>::iterator Mesh::getBegin(){
	return mesh.begin();
}

multimap<vec3, Vertex>::iterator Mesh::getEnd() {
	return mesh.end();
}

int Mesh::getSize() {
	return mesh.size();
}
