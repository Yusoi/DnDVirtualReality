#include "Face.h"

Face::Face() {
}

void Face::add_position(vec3 index) {
	position_index = index;
}

void Face::add_texture(vec3 index) {
	texture_index = index;
}

void Face::add_normal(vec3 index) {
	normal_index = index;
}

vec3 Face::get_position_index() {
	return position_index;
}

vec3 Face::get_texture_index() {
	return texture_index;
}

vec3 Face::get_normal_index() {
	return normal_index;
}