#version 400

uniform sampler2D albedo;
uniform float shininess = 128;

in Data {
	vec4 eye;
	vec2 texCoord;
	vec3 normal;
	vec3 l_dir;
} DataIn;

out vec4 colorOut;

void main() {

	vec4 colorOut = texture(albedo,DataIn.texCoord);

	// set the specular term to black
	vec4 spec = vec4(0.0);

	// normalize both input vectors
	vec3 n = normalize(DataIn.normal);
	vec3 e = normalize(vec3(DataIn.eye));

	float intensity = max(dot(n,DataIn.l_dir), 0.0);

	// compute the half vector
	vec3 h = normalize(DataIn.l_dir + e);	

	// compute the specular intensity
	float intSpec = max(dot(h,n), 0.0);

	// compute the specular term into spec
	spec = vec4(1) * pow(intSpec,shininess);

	colorOut = max(intensity * colorOut + spec , colorOut * 0.40);
}