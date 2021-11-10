#pragma once
#include "Utils.h"
#include "UILayer.h"
#include "Profiler.h"
#include "Camera.h"
#include "FrameBuffer.h"

class Window;
class Light;
class DirectionalLight;
class PointLight;
class SpotLight;
class Material;
class Shader;
class Camera3D;
class Quad;
class Texture;

class ENGINEDLL_API Renderer {
private:
	static Renderer* singleton;
	vector<DirectionalLight*> dirLights;
	vector<PointLight*> pointLights;
	vector<SpotLight*> spotLights;
	Camera3D* firstCamera;
	Camera3D* currentCamera;
	bool bboxDrawDebug = false;
	FrameBuffer gBuffer;
	SpatialMaterial* geometryPass;
	SpatialMaterial* dirLightPass;
	SpatialMaterial* pointLightPass;
	Quad* viewport;
	SpatialMaterial* viewportMaterial;
protected:
	Window* window;
public:
	enum Primitive {
		LINES = 0x0001,
		LINE_STRIP = 0x0003,
		TRIANGLES = 0x0004,
		TRIANGLE_STRIP = 0x0005,
		QUADS = 0x0007
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
	struct MeshVertexData {
		Vector3 position;
		Vector3 normal;
		Vector3 texCoords;
	};
	enum LightType {
		DIRECTIONAL,
		POINT,
		SPOT
	};
	bool Init();
	bool Destroy();
	unsigned int CreateVertexBuffer(void* data, size_t dataSize, BufferType bufferType);
	unsigned int CreateTextureBuffer(unsigned char* data, int width, int height, int nrChannels);
	void UpdateVertexBuffer(unsigned int vbo, void* data, size_t dataSize, BufferType bufferType);
	unsigned int CreateVertexArrayID();
	void BindBuffer(unsigned int bufferID, BufferType bufferType);
	void BindBufferWithAttribute(unsigned int bufferID, BufferType bufferType, int attributeID, unsigned int vertexCount);
	void BindVertexData(VertexData vertexData);
	void BindVertexArray(unsigned int vertexArrayID);
	void SetAttributePointer(unsigned int attributeId, size_t dataCount);
	void ActivateTexture(unsigned int index);
	void SetClearColor(Color color);
	void ClearScreen();
	void SwapBuffers();
	void DisableBuffer(size_t attributeID);
	void DeleteBuffer(unsigned int bufferID);
	void DeleteTexture(unsigned int textureID);
	void DeleteShader(unsigned int shaderID);
	void Draw(Primitive _primitive, int vertexCount);
	void Draw(unsigned int vao, Primitive _primitive, int vertexCount, bool elementDraw);
	void Draw(unsigned int vao, Primitive _primitive, int vertexCount, bool elementDraw, Transform* modelTransform);
	void Draw(unsigned int vao, Primitive _primitive, int vertexCount, bool elementDraw, Transform* modelTransform, SpatialMaterial* material);
	void Draw(Primitive _primitive, int vertexCount, bool elementDraw);
	void DrawElements(Primitive _primitive, int vertexCount);
	void EnableClientState();
	void DisableClientState();
	void DestroyVertexData(vector<VertexData> data);
	static Renderer* GetSingleton();
	Camera* GetCamera() const;
	Camera3D* GetCamera3D() const;
	void SetCurrentCamera(Camera3D* _camera);
	void AddLight(Light* light);
	int GetDirLights() const;
	int GetPointLights() const;
	int GetSpotLights() const;
	void ProcessLighting(Shader* shader);
	bool IsInsideFrustum(const Vector3& pos);
	bool IsInsideFrustum(const Transform& transform, const BoundingBox& bbox);
	bool IsInsideFrustum(const BoundingBox& bbox);
	bool GetBBoxDrawDebug() const;
	void EnableBBoxDrawDebug(bool enabled);
	void SetStencilID(unsigned int id);
	Transform* GetCameraTransform() const;
	void BeginRender();
	void EndRender();
	void DrawViewport();
	void DrawViewport(SpatialMaterial* material);
	Vector2 GetWindowSize();
	Renderer(Window* _window);
	virtual ~Renderer();
};

