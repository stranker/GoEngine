#include "Renderer.h"
#include "GlInclude.h"
#include "Window.h"
#include "Light.h"
#include "Camera3D.h"
#include "Quad.h"
#include "Shader.h"

bool Renderer::Init(){
	if (!window) {
		return false;
	}
	if (glewInit() != GLEW_OK){
		return false;
	}
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	firstCamera = new Camera3D(window->GetSize().x, window->GetSize().y);
	currentCamera = firstCamera;

	viewport = new Quad();
	//viewportMaterial = ResourceManager::LoadSpatialMaterial("Shaders/Viewport.vs","Shaders/Viewport.fs","viewportMaterial");
	//viewport->SetMaterial(viewportMaterial);
	//viewportMaterial->SetInt("inputTexture", 0);
	UILayer::CreateContext(window);
	return true;
}

bool Renderer::Destroy(){
	if (!dirLights.empty()){
		dirLights.clear();
	}
	if (!pointLights.empty()) {
		pointLights.clear();
	}
	if (!spotLights.empty()) {
		spotLights.clear();
	}
	return true;
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
	GLenum format = GL_RED;
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
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	return textureID;
}

void Renderer::UpdateVertexBuffer(unsigned int vbo, void * data, size_t dataSize, BufferType bufferType) {
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

void Renderer::BindVertexArray(unsigned int vertexArrayID) {
	glBindVertexArray(vertexArrayID);
}

void Renderer::ActivateTexture(unsigned int index) {
	glActiveTexture(GL_TEXTURE0 + index);
}

void Renderer::SetClearColor(Color color) {
	glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::ClearScreen(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
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

void Renderer::DeleteTexture(unsigned int textureID) {
	glDeleteTextures(1, &textureID);
}

void Renderer::DeleteShader(unsigned int shaderID) {
	glDeleteProgram(shaderID);
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
	for (size_t i = 0; i < data.size(); i++){
		DeleteBuffer(data[i].vbo);
	}
}

Renderer* Renderer::singleton = NULL;

Renderer* Renderer::GetSingleton() {
	return singleton;
}

void Renderer::Draw(unsigned int vao, Primitive _primitive, int vertexCount, bool elementDraw) {
	BindVertexArray(vao);
	Draw(_primitive, vertexCount, elementDraw);
	Profiler::objectsDrawing++;
}

void Renderer::Draw(unsigned int vao, Primitive _primitive, int vertexCount, bool elementDraw, Transform* modelTransform) {
	Draw(vao, _primitive, vertexCount, elementDraw);
}

void Renderer::Draw(unsigned int vao, Primitive _primitive, int vertexCount, bool elementDraw, Transform* modelTransform, SpatialMaterial* material) {
	Draw(vao, _primitive, vertexCount, elementDraw);
}

void Renderer::Draw(Primitive _primitive, int vertexCount, bool elementDraw) {
	if (elementDraw) {
		DrawElements(_primitive, vertexCount);
	}
	else {
		Draw(_primitive, vertexCount);
	}
}

Camera* Renderer::GetCamera() const{
	return currentCamera;
}

Camera3D* Renderer::GetCamera3D() const {
	return currentCamera;
}

void Renderer::SetCurrentCamera(Camera3D* _camera){
	currentCamera = _camera;
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

void Renderer::ProcessLighting(Shader* shader) {
	shader->SetInt("dirLightSize", dirLights.size());
	shader->SetInt("pointLightSize", pointLights.size());
	shader->SetInt("spotLightSize", spotLights.size());
	for (size_t i = 0; i < dirLights.size(); i++){
		string dirArrayIdx = "dirLights[" + to_string(i) + "]";
		shader->SetVec3(dirArrayIdx + ".direction", dirLights[i]->GetTransform()->GetFoward());
		shader->SetVec3(dirArrayIdx + ".ambient", dirLights[i]->GetLightColor());
		shader->SetFloat(dirArrayIdx + ".specular", dirLights[i]->GetSpecular());
		shader->SetFloat(dirArrayIdx + ".energy", dirLights[i]->GetEnergy());
		shader->SetBool(dirArrayIdx + ".visible", dirLights[i]->IsVisible());
	}
	for (size_t i = 0; i < pointLights.size(); i++) {
		string dirArrayIdx = "pointLights[" + to_string(i) + "]";
		shader->SetVec3(dirArrayIdx + ".position", pointLights[i]->GetTransform()->GetPosition());
		shader->SetVec3(dirArrayIdx + ".ambient", pointLights[i]->GetLightColor());
		shader->SetFloat(dirArrayIdx + ".specular", pointLights[i]->GetSpecular());
		shader->SetFloat(dirArrayIdx + ".energy", pointLights[i]->GetEnergy());
		shader->SetFloat(dirArrayIdx + ".constant", pointLights[i]->GetAttenuation().x);
		shader->SetFloat(dirArrayIdx + ".linear", pointLights[i]->GetAttenuation().y);
		shader->SetFloat(dirArrayIdx + ".quadratic", pointLights[i]->GetAttenuation().z);
		shader->SetFloat(dirArrayIdx + ".range", pointLights[i]->GetRange());
		shader->SetBool(dirArrayIdx + ".visible", pointLights[i]->IsVisible());
	}
	for (size_t i = 0; i < spotLights.size(); i++) {
		string dirArrayIdx = "spotLights[" + to_string(i) + "]";
		shader->SetVec3(dirArrayIdx + ".direction", spotLights[i]->GetTransform()->GetFoward());
		shader->SetVec3(dirArrayIdx + ".position", spotLights[i]->GetTransform()->GetPosition());
		shader->SetVec3(dirArrayIdx + ".ambient", spotLights[i]->GetLightColor());
		shader->SetFloat(dirArrayIdx + ".specular", spotLights[i]->GetSpecular());
		shader->SetFloat(dirArrayIdx + ".energy", spotLights[i]->GetEnergy());
		shader->SetFloat(dirArrayIdx + ".constant", spotLights[i]->GetAttenuation().x);
		shader->SetFloat(dirArrayIdx + ".linear", spotLights[i]->GetAttenuation().y);
		shader->SetFloat(dirArrayIdx + ".quadratic", spotLights[i]->GetAttenuation().z);
		shader->SetFloat(dirArrayIdx + ".cutOff", glm::cos(glm::radians(spotLights[i]->GetCutOff())));
		shader->SetFloat(dirArrayIdx + ".outerCutOff", glm::cos(glm::radians(spotLights[i]->GetOuterCutOff())));
		shader->SetFloat(dirArrayIdx + ".range", spotLights[i]->GetRange());
		shader->SetBool(dirArrayIdx + ".visible", spotLights[i]->IsVisible());
	}
}

bool Renderer::IsInsideFrustum(const Vector3& pos) {
	return currentCamera->IsPointInFrustum(pos);
}

bool Renderer::IsInsideFrustum(const Transform& transform, const BoundingBox& bbox) {
	return currentCamera->IsBoxVisible(transform, bbox);
}

bool Renderer::IsInsideFrustum(const BoundingBox& bbox) {
	return currentCamera->IsBoxVisible(bbox);
}

bool Renderer::GetBBoxDrawDebug() const {
	return bboxDrawDebug;
}

void Renderer::EnableBBoxDrawDebug(bool enabled) {
	bboxDrawDebug = enabled;
}

void Renderer::SetStencilID(unsigned int id) {
	glStencilFunc(GL_ALWAYS, id, 0xFFFF);
}

Transform* Renderer::GetCameraTransform() const {
	return ((Camera3D*)currentCamera)->GetGlobalTransform();
}

void Renderer::BeginRender() {
	SetClearColor(Color().Black());
	ClearScreen();
	EnableClientState();
	glEnable(GL_DEPTH_TEST);
}

void Renderer::EndRender() {
	DisableClientState();
}

void Renderer::DrawViewport() {
	viewport->Draw();
}

void Renderer::DrawViewport(SpatialMaterial* material) {
	glDisable(GL_DEPTH_TEST);
	viewport->Draw();
}

Vector2 Renderer::GetWindowSize() {
	return window->GetSize();
}

Renderer::Renderer(Window* _window){
	window = _window;
	singleton = this;
}

Renderer::~Renderer(){
}
