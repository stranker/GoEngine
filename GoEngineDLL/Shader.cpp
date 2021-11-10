#include "Shader.h"
#include "GlInclude.h"
#include "Renderer.h"

void Shader::LoadShader(const string& vertexShader, const string& fragmentShader) {
	// Crear los shaders
	unsigned int VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	unsigned int FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Leer el Vertex Shader desde archivo
	vertexCode = ConvertUberShader(vertexShader, VERTEX_SHADER);
	fragmentCode = ConvertUberShader(fragmentShader, FRAGMENT_SHADER);

	int Result = GL_FALSE;
	int InfoLogLength;

	char const* VertexSourcePointer = vertexCode.c_str();
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
	char const* FragmentSourcePointer = fragmentCode.c_str();
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

void Shader::Use() {
	glUseProgram(shaderID);
}

void Shader::Unbind() {
	glUseProgram(0);
}

void Shader::Destroy() {
	Unbind();
	glDeleteProgram(shaderID);
}

Shader::Shader() {
	shaderID = 0;
	resourceID = 0;
	SetDefaultName("Shader");
}

Shader::Shader(const string& vertexShader, const string& fragmentShader) : Shader() {
	LoadShader(vertexShader, fragmentShader);
}

Shader::~Shader() {
}

string Shader::ConvertUberShader(const string& filePath, ShaderType type) {
	string uberShader;
	fstream uberFile(type == FRAGMENT_SHADER ? spatialFragment : spatialVertex, ios::in);
	if (uberFile.is_open()) {
		stringstream sstr;
		sstr << uberFile.rdbuf();
		uberShader = sstr.str();
		uberFile.close();
	}

	if (filePath == spatialVertex || filePath == spatialFragment) { return uberShader; };

	string customShader;
	fstream file(filePath, ios::in);
	if (file.is_open()) {
		stringstream sstr;
		sstr << file.rdbuf();
		customShader = sstr.str();
		file.close();
	}
	uberShader = Utils::ReplaceString(uberShader, type == VERTEX_SHADER ? "void vertex(){};" : "void fragment(){};", customShader);
	uberShader =  Utils::ReplaceString(uberShader, "shader_type spatial;", "#define CUSTOM_ALBEDO");
	return uberShader;
}

void Shader::SetMat4(const string& property, glm::mat4 matrix) const {
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetVec2(const string& property, Vector2 vec) const {
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniform2f(location, vec.x, vec.y);
}

void Shader::SetVec3(const string& property, Vector3 vec) const {
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::SetVec4(const string& property, glm::vec4 value) const {
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::SetVec4(const string& property, Rect2 value) const {
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniform4f(location, value.x, value.y, value.width, value.height);
}

void Shader::SetBool(const string& property, bool value) const {
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniform1i(location, value);
}

void Shader::SetInt(const string& property, int value) const {
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniform1i(location, value);
}

void Shader::SetFloat(const string& property, float value) const {
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniform1f(location, value);
}

void Shader::SetTexture(const string& property, unsigned int textureId, unsigned int index) {
	unsigned int location = glGetUniformLocation(shaderID, property.c_str());
	glUniform1i(location, index);
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, textureId);
}
