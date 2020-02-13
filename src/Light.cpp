#include "Light.h"

PresetLight::PresetLight() {
	l_pos = vec4(0.0, 0.0, 0.0, 0.0);
	l_dir = vec4(0.0, 0.0, 0.0, 0.0);
	l_color = vec4(0.0, 0.0, 0.0, 0.0);
}

PresetLight::PresetLight(vec4 l_pos, vec4 l_dir, vec4 l_color, char* preset) {
	this->l_pos = l_pos;
	this->l_dir = l_dir;
	this->l_color = l_color;
	this->preset = preset;
}

CustomLight::CustomLight() {
	l_pos = vec4(0.0, 0.0, 0.0, 0.0);
	l_dir = vec4(0.0, 0.0, 0.0, 0.0);
	l_color = vec4(0.0, 0.0, 0.0, 0.0);
}

CustomLight::CustomLight(vec4 l_pos, vec4 l_dir, vec4 l_color) {
	this->l_pos = l_pos;
	this->l_dir = l_dir;
	this->l_color = l_color;
}