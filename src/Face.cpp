#include "Face.h"

Face::Face(int type) {
	this->type = type;
}

void Face::add_vertex(int index) {
	vertex_index.push_back(index);
}

void Face::add_texture(int index) {
	texture_index.push_back(index);
}

void Face::add_normal(int index) {
	normal_index.push_back(index);
}

vector<int>* Face::get_vertex_index() {
	return &vertex_index;
}

vector<int>* Face::get_texture_index() {
	return &texture_index;
}

vector<int>* Face::get_normal_index() {
	return &normal_index;
}

int Face::getType() {
	return type;
}

int Face::size() {
	return vertex_index.size();
}