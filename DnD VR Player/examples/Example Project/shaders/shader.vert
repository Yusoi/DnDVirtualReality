#version 400

uniform	mat4 m_pvm;
uniform	mat4 m_viewModel;
uniform	mat4 m_view;
uniform	mat3 m_normal;

uniform	vec4 l_dir;	   // global space

layout(location = 0) in vec4 position;	// local space
layout(location = 1) in vec2 texCoord0;
layout(location = 2) in vec3 normal;		// local space

// the data to be sent to the fragment shader
out Data {
	vec4 eye;
	vec2 texCoord;
	vec3 normal;
	vec3 l_dir;
} DataOut;

void main () {
	DataOut.texCoord = texCoord0;
	DataOut.normal = normalize(m_normal * normal);
	DataOut.eye = -(m_viewModel * position);
	DataOut.l_dir = normalize(vec3(m_view * -l_dir));

	gl_Position = m_pvm * position;	
}