#include "Shader.h"

Shader::Shader(string vShader_path, string fShader_path) {
	ifstream vShader(vShader_path);
	string vShader_string((std::istreambuf_iterator<char>(vShader)),
		std::istreambuf_iterator<char>());
	const char* vShader_code = vShader_string.c_str();

	ifstream fShader(fShader_path);
	string fShader_string((std::istreambuf_iterator<char>(fShader)),
		std::istreambuf_iterator<char>());
	const char* fShader_code = fShader_string.c_str();

	vShader_id = glCreateShader(GL_VERTEX_SHADER);
	fShader_id = glCreateShader(GL_FRAGMENT_SHADER);

	if (vShader_id == 0 || fShader_id == 0) {
		cout << "Error creating shaders" << endl;
	}

	glShaderSource(vShader_id, 1, &vShader_code, NULL);
	glCompileShader(vShader_id);
	
	glShaderSource(fShader_id, 1, &fShader_code, NULL);
	glCompileShader(fShader_id);

	GLint compileStatus;

	glGetShaderiv(vShader_id, GL_COMPILE_STATUS, &compileStatus);

	if (!compileStatus) { // If compilation was not successful 
		int length;
		glGetShaderiv(vShader_id, GL_INFO_LOG_LENGTH, &length);
		char* cMessage = new char[length];

		// Get additional information 
		glGetShaderInfoLog(vShader_id, length, &length, cMessage);
		std::cout << "Cannot Compile Shader: " << cMessage;
		delete[] cMessage;
		glDeleteShader(vShader_id);

		return;
	}

	glGetShaderiv(fShader_id, GL_COMPILE_STATUS, &compileStatus);

	if (!compileStatus) { // If compilation was not successful 
		int length;
		glGetShaderiv(fShader_id, GL_INFO_LOG_LENGTH, &length);
		char* cMessage = new char[length];

		// Get additional information 
		glGetShaderInfoLog(fShader_id, length, &length, cMessage);
		std::cout << "Cannot Compile Shader: " << cMessage;
		delete[] cMessage;
		glDeleteShader(fShader_id);

		return;
	}

	//Linking the program
	program_id = glCreateProgram(); // create a program 

	if (program_id == 0) {
		std::cout << "Error Creating Shader Program";
		return;
	}

	// Attach both the shaders to it 
	glAttachShader(program_id, vShader_id);
	glAttachShader(program_id, fShader_id);

	// Create executable of this program 
	glLinkProgram(program_id);

	GLint linkStatus;

	// Get the link status for this program 
	glGetProgramiv(program_id, GL_LINK_STATUS, &linkStatus);

	if (!linkStatus) { // If the linking failed 
		std::cout << "Error Linking program";
		glDetachShader(program_id, vShader_id);
		glDetachShader(program_id, fShader_id);
		glDeleteProgram(program_id);

		return;
	}	

	glDeleteShader(vShader_id);
	glDeleteShader(fShader_id);
}

GLuint Shader::getProgramId() {
	return program_id;
}