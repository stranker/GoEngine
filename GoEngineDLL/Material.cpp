#include "Material.h"
#include "GlInclude.h"
#include "Renderer.h"

void Material::SetMat4(string const& property, glm::mat4 matrix) const{
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Material::SetVec2(string const& property, Vector2 vec) const {
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniform2f(location, vec.x, vec.y);
}

void Material::SetVec3(string const& property, Vector3 vec) const {
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void Material::SetVec4(string const& property, glm::vec4 value) const {
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Material::SetVec4(string const& property, Rect2 value) const {
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniform4f(location, value.x, value.y, value.width, value.height);
}

void Material::SetBool(string const& property, bool value) const {
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniform1i(location, value);
}

void Material::SetInt(string const& property, int value) const {
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniform1i(location, value);
}

void Material::SetFloat(string const& property, float value) const {
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniform1f(location, value);
}

void Material::SetTexture(string const& property, unsigned int textureId, unsigned int index) {
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Material::Use(){
	glUseProgram(shaderID);
}

unsigned int Material::GetID() {
	return shaderID;
}

void Material::LoadShaders(string const& vertex_file_path, string const& fragment_file_path){
	// Crear los shaders
	unsigned int VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	unsigned int FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Leer el Vertex Shader desde archivo
	string VertexShaderCode;
	ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
	}

	string FragmentShaderCode;
	ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	int Result = GL_FALSE;
	int InfoLogLength;

	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Revisar Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Revisar Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}
	
	shaderID = glCreateProgram();
	glAttachShader(shaderID, VertexShaderID);
	glAttachShader(shaderID, FragmentShaderID);
	glLinkProgram(shaderID);

	glGetProgramiv(shaderID, GL_LINK_STATUS, &Result);
	glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(shaderID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(shaderID, VertexShaderID);
	glDetachShader(shaderID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
}

void Material::ResetTextureActive() {
	glActiveTexture(GL_TEXTURE0);
}

Material::Material() {
	SetDefaultName("Material");
}
