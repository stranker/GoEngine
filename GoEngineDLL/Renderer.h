#pragma once
#include "Camera.h"
#include <vector>

class Window;
class Light;
class DirectionalLight;
class PointLight;
class SpotLight;
class SpatialMaterial;

using namespace std;

class ENGINEDLL_API Renderer
{
private:
	static Renderer* singleton;
	vector<DirectionalLight*> dirLights;
	vector<PointLight*> pointLights;
	vector<SpotLight*> spotLights;
protected:
	Window* window;
	Camera* camera;
	Camera* firstCamera;
public:
	enum Primitive {
		LINES = 0x0001,
		LINE_STRIP = 0x0003,
		TRIANGLES = 0x0004,
		TRIANGLE_STRIP = 0x0005
	};
	enum BufferType {
		ARRAY_BUFFER = 0x8892,
		ELEMENT_BUFFER = 0x8893
	};
	struct VertexData {
		unsigned int vbo;
		int attributeID;
		unsigned int dataCount;
		BufferType bufferType;
	};
	enum LightType {
		DIRECTIONAL,
		POINT,
		SPOT
	};
	bool Init();
	bool Destroy();
	unsigned int CreateVertexBuffer(float *data, size_t dataSize, BufferType bufferType);
	unsigned int CreateVertexBuffer(unsigned int *data, size_t dataSize, BufferType bufferType);
	unsigned int CreateTextureBuffer(unsigned char * data, int width, int height, int nrChannels);
	void UpdateVertexBuffer(unsigned int vbo, float *data, size_t dataSize, BufferType bufferType);
	void UpdateVertexBuffer(unsigned int vbo, unsigned int *data, size_t dataSize, BufferType bufferType);
	unsigned int CreateVertexArrayID();
	void BindBuffer(unsigned int bufferID, BufferType bufferType);
	void BindBufferWithAttribute(unsigned int bufferID, BufferType bufferType, int attributeID, unsigned int vertexCount);
	void BindVertexData(VertexData vertexData);
	void BindTexture(unsigned int textureBuffer);
	void BindVertexArray(unsigned int vertexArrayID);
	void SetAttributePointer(unsigned int attributeId, size_t dataCount);
	void SetTextureParameters(unsigned char* data, int width, int height);
	void SetClearColor(Color color);
	void ClearScreen();
	void SwapBuffers();
	void DisableBuffer(size_t attributeID);
	void DeleteBuffer(unsigned int bufferID);
	void Draw(Primitive _primitive, int vertexCount);
	void Draw(unsigned int vao, Primitive _primitive, int vertexCount, bool elementDraw);
	void DrawElements(Primitive _primitive, int vertexCount);
	void EnableClientState();
	void DisableClientState();
	void DestroyVertexData(vector<VertexData> data);
	static Renderer* GetSingleton();
	Camera* GetCamera();
	void SetCurrentCamera(Camera* _camera);
	void AddLight(Light* light);
	int GetDirLights() const;
	int GetPointLights() const;
	int GetSpotLights() const;
	void ProcessLighting(SpatialMaterial* material);
	Renderer(Window* _window);
	virtual ~Renderer();
};

