#include "Renderer.h"
#include "GlInclude.h"
#include "Window.h"
#include "Light.h"
#include "SpatialMaterial.h"

bool Renderer::Init(){
	cout << "Renderer Init" << endl;
	if (!window) {
		cout << "Window ptr not created" << endl;
		return false;
	}
	if (glewInit() != GLEW_OK){
		cout << "Failed to init Glew" << endl;
		return false;
	}
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}

bool Renderer::Destroy(){
	cout << "Renderer Destroy" << endl;
	if (!dirLights.empty()){
		for (Light* light : dirLights) {
			light->Destroy();
			delete light;
		}
		dirLights.clear();
	}
	if (!pointLights.empty()) {
		for (Light* light : pointLights) {
			light->Destroy();
			delete light;
		}
		pointLights.clear();
	}
	if (!spotLights.empty()) {
		for (Light* light : spotLights) {
			light->Destroy();
			delete light;
		}
		spotLights.clear();
	}
	if (firstCamera){
		firstCamera->Destroy();
		delete firstCamera;
		firstCamera = NULL;
	}
	if (camera) {
		camera->Destroy();
		delete camera;
		camera = NULL;
	}
	return true;
}

unsigned int Renderer::CreateVertexBuffer(float *data, size_t dataSize, BufferType bufferType) {
	unsigned int vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer((GLenum)bufferType, vertexBuffer);
	glBufferData((GLenum)bufferType, dataSize, data, GL_STATIC_DRAW);
	return vertexBuffer;
}

unsigned int Renderer::CreateVertexBuffer(unsigned int * data, size_t dataSize, BufferType bufferType) {
	unsigned int vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer((GLenum)bufferType, vertexBuffer);
	glBufferData((GLenum)bufferType, dataSize, data, GL_STATIC_DRAW);
	return vertexBuffer;
}

unsigned int Renderer::CreateVertexBuffer(void* data, size_t dataSize, BufferType bufferType) {
	unsigned int vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer((GLenum)bufferType, vertexBuffer);
	glBufferData((GLenum)bufferType, dataSize, data, GL_STATIC_DRAW);
	return vertexBuffer;
}

unsigned int Renderer::CreateTextureBuffer(unsigned char * data, int width, int height, int nrChannels) {
	unsigned int textureID;
	glGenTextures(1, &textureID);
	GLenum format;
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	TextureImporter::FreeTexture(data);
	return textureID;
}

void Renderer::UpdateVertexBuffer(unsigned int vbo, float * data, size_t dataSize, BufferType bufferType) {
	glGenBuffers(1, &vbo);
	glBindBuffer((GLenum)bufferType, vbo);
	glBufferData((GLenum)bufferType, dataSize, data, GL_STATIC_DRAW);
}

void Renderer::UpdateVertexBuffer(unsigned int vbo, unsigned int * data, size_t dataSize, BufferType bufferType) {
	glGenBuffers(1, &vbo);
	glBindBuffer((GLenum)bufferType, vbo);
	glBufferData((GLenum)bufferType, dataSize, data, GL_STATIC_DRAW);
}

unsigned int Renderer::CreateVertexArrayID() {
	unsigned int vao;
	glGenVertexArrays(1, (&vao));
	glBindVertexArray(vao);
	return vao;
}

void Renderer::BindBuffer(unsigned int bufferID, BufferType bufferType){
	glBindBuffer((GLenum)bufferType, bufferID);
}

void Renderer::SetAttributePointer(unsigned int attributeId, size_t dataCount) {
	glVertexAttribPointer(attributeId, dataCount, GL_FLOAT, GL_FALSE, dataCount * sizeof(float), (void*)0);
	glEnableVertexAttribArray(attributeId);
}

void Renderer::BindBufferWithAttribute(unsigned int bufferID, BufferType bufferType, int attributeID, unsigned int vertexCount) {
	BindBuffer(bufferID, bufferType);
	if (attributeID != -1) { // Es un buffer que debo setearle atributos? /* NOTA: Index buffer no necesita setear atributos */
		SetAttributePointer(attributeID, vertexCount);
	}
}

void Renderer::BindVertexData(VertexData vertexData) {
	BindBufferWithAttribute(vertexData.vbo, vertexData.bufferType, vertexData.attributeID, vertexData.dataCount);
}

void Renderer::BindTexture(unsigned int textureBuffer) {
	glBindTexture(GL_TEXTURE_2D, textureBuffer);
}

void Renderer::BindVertexArray(unsigned int vertexArrayID) {
	glBindVertexArray(vertexArrayID);
}

void Renderer::SetTextureProperty(const char* propertyName, unsigned int id, unsigned int index) {
}

void Renderer::ActivateTexture(unsigned int index) {
	glActiveTexture(GL_TEXTURE0 + index);
}

void Renderer::SetClearColor(Color color) {
	glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::ClearScreen(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SwapBuffers(){
	glfwSwapBuffers((GLFWwindow*)window->GetWindowPtr());
}

void Renderer::DisableBuffer(size_t attributeID) {
	glDisableVertexAttribArray(attributeID);
}

void Renderer::DeleteBuffer(unsigned int _buffer) {
	glDeleteBuffers(1, &_buffer);
}

void Renderer::Draw(Primitive _primitive, int vertexCount) {
	glDrawArrays((GLenum)_primitive, 0, vertexCount);
}

void Renderer::DrawElements(Primitive _primitive, int vertexCount) {
	glDrawElements((GLenum)_primitive, vertexCount, GL_UNSIGNED_INT, 0);
}

void Renderer::EnableClientState() {
	glEnableClientState(GL_VERTEX_ARRAY);
}

void Renderer::DisableClientState() {
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Renderer::DestroyVertexData(vector<VertexData> data) {
	for (VertexData vertexData : data) {
		DeleteBuffer(vertexData.vbo);
	}
}

Renderer* Renderer::singleton = NULL;

Renderer* Renderer::GetSingleton() {
	return singleton;
}

void Renderer::Draw(unsigned int vao, Primitive _primitive, int vertexCount, bool elementDraw) {
	BindVertexArray(vao);
	Draw(_primitive, vertexCount, elementDraw);
}

void Renderer::Draw(Primitive _primitive, int vertexCount, bool elementDraw) {
	if (elementDraw) {
		DrawElements(_primitive, vertexCount);
	}
	else {
		Draw(_primitive, vertexCount);
	}
}

Camera * Renderer::GetCamera() {
	return camera;
}

void Renderer::SetCurrentCamera(Camera* _camera){
	camera = _camera;
}

void Renderer::AddLight(Light* light) {
	switch (light->GetType())
	{
	case LightType::DIRECTIONAL: dirLights.push_back((DirectionalLight*)light); break;
	case LightType::POINT: pointLights.push_back((PointLight*)light); break;
	case LightType::SPOT: spotLights.push_back((SpotLight*)light); break;
	default:
		break;
	}
}

int Renderer::GetDirLights() const {
	return dirLights.size();
}

int Renderer::GetPointLights() const {
	return pointLights.size();
}

int Renderer::GetSpotLights() const {
	return spotLights.size();
}

void Renderer::ProcessLighting(SpatialMaterial* material) {
	material->SetInt("dirLightSize", dirLights.size());
	material->SetInt("pointLightSize", pointLights.size());
	material->SetInt("spotLightSize", spotLights.size());
	for (size_t i = 0; i < dirLights.size(); i++){
		string dirArrayIdx = "dirLights[" + to_string(i) + "]";
		material->SetVec3(dirArrayIdx + ".direction", dirLights[i]->GetDirection());
		material->SetVec3(dirArrayIdx + ".color", dirLights[i]->GetLightColor());
		material->SetFloat(dirArrayIdx + ".specular", dirLights[i]->GetSpecular());
		material->SetFloat(dirArrayIdx + ".energy", dirLights[i]->GetEnergy());
	}
	for (size_t i = 0; i < pointLights.size(); i++) {
		string dirArrayIdx = "pointLights[" + to_string(i) + "]";
		material->SetVec3(dirArrayIdx + ".position", pointLights[i]->GetTransform()->GetPosition());
		material->SetVec3(dirArrayIdx + ".color", pointLights[i]->GetLightColor());
		material->SetFloat(dirArrayIdx + ".specular", pointLights[i]->GetSpecular());
		material->SetFloat(dirArrayIdx + ".energy", pointLights[i]->GetEnergy());
		material->SetFloat(dirArrayIdx + ".constant", pointLights[i]->GetAttenuation().x);
		material->SetFloat(dirArrayIdx + ".linear", pointLights[i]->GetAttenuation().y);
		material->SetFloat(dirArrayIdx + ".quadratic", pointLights[i]->GetAttenuation().z);
		material->SetFloat(dirArrayIdx + ".range", pointLights[i]->GetRange());
	}
	for (size_t i = 0; i < spotLights.size(); i++) {
		string dirArrayIdx = "spotLights[" + to_string(i) + "]";
		material->SetVec3(dirArrayIdx + ".direction", spotLights[i]->GetTransform()->GetFoward());
		material->SetVec3(dirArrayIdx + ".position", spotLights[i]->GetTransform()->GetPosition());
		material->SetVec3(dirArrayIdx + ".color", spotLights[i]->GetLightColor());
		material->SetFloat(dirArrayIdx + ".specular", spotLights[i]->GetSpecular());
		material->SetFloat(dirArrayIdx + ".energy", spotLights[i]->GetEnergy());
		material->SetFloat(dirArrayIdx + ".constant", spotLights[i]->GetAttenuation().x);
		material->SetFloat(dirArrayIdx + ".linear", spotLights[i]->GetAttenuation().y);
		material->SetFloat(dirArrayIdx + ".quadratic", spotLights[i]->GetAttenuation().z);
		material->SetFloat(dirArrayIdx + ".cutOff", spotLights[i]->GetCutOff());
		material->SetFloat(dirArrayIdx + ".outerCutOff", spotLights[i]->GetOuterCutOff());
		material->SetFloat(dirArrayIdx + ".range", spotLights[i]->GetRange());
	}
}

Renderer::Renderer(Window* _window){
	window = _window;
	firstCamera = new Camera(window->GetWidth(), window->GetHeight());
	camera = firstCamera;
	singleton = this;
}

Renderer::~Renderer(){
}
