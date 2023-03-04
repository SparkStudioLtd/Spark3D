#pragma once
#include "pch.h"

#include "Core/Types.h"
#include "Core/Obj.h"
#include "Core/Components/Transform.h"

class GPUContext;
class GPUWindow;
class GPUAdapter;
class GPUMesh;
class GPUShader;
class GPUDrawData;
class GPUTexture;
class ShaderManager;
enum GPUBufferType;
class GPUBuffer;
class GPUMaterial;
class Camera;
class GPUFramebuffer;
class GPURenderPass;
class GPUSkybox;
class GPUViewport;
class GUI;


struct Vertex {
	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
};


enum CameraProjectionType {
	PERSPECTIVE,
	ORTHO
};

enum GPUFramebufferType {
	COLORMAP,
	DEPTHMAP
};

class Camera {
public:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0);

	glm::quat getOrientation() {
		return glm::quat(glm::vec3(rotation.x, rotation.y, rotation.z));
	}

	glm::vec3 getForward() {
		//glm::quat rotation = this->getOrientation();
		//glm::vec3 vector = glm::vec3(0, 0, 1);
		//return MathExtVecCalc::transformQuaT(vector, rotation);
		//TODO
		return glm::vec3(0, 0, 0);
	}
	glm::vec3 getRight() {
		return glm::vec3(cos(this->rotation.y), 0, -sin(this->rotation.y));
	}
	glm::vec3 getUp() {
		return glm::cross(this->getForward(), this->getRight());
	}

	bool firstMouse = true;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float lastX = 800.0f / 2.0;
	float lastY = 600.0 / 2.0;
	float fov = 45.0f;

	CameraProjectionType cameraProjectionType;
	bool allowDrone = true;
	glm::mat4 getProjectionMatrix(GPUContext* context);
	glm::mat4 getViewMatrix(GPUContext* context);
	void update(GPUContext* context);
};

class GPUTexture {
public:
	std::map<std::string, std::any> unbaseVars;
};

class GPUViewport {
public:
	glm::vec2 position;
	glm::vec2 scale;
};

class CSG {
public:
	static GPUMesh* createBox(GPUContext* context);
};


class GPUContext {
public:
	GPUContext() {}
	std::string toName() {
		return "GPUContext";
	}
	bool useGui = false;
	int frameCount = 0;
	std::map<std::string, std::any> unbaseVars;
	GPUWindow* window;
	GPUSkybox* skybox = nullptr;
	GPUFramebuffer* shadowFramebuffer;
	GPUFramebuffer* mainFramebuffer;
	bool renderingToDepthMap = false;
	Camera* camera = new Camera();
	GPUViewport* viewport;
	std::vector<GPUDrawData*> drawQueueList;
	std::vector<GPURenderPass*> renderPasses;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	Color clearColor = Color(0.0f, 0.0f, 0.0f, 1.0f);


	void createAdapterAndContext();
	GPUBuffer* createBuffer(GPUBufferType bufferType, const void* data, int size);
	GPUMesh* createMesh(Vertex vertices[], int verticesSize, int indices[], int indicesSize);
	GPUShader* createShader(std::string vertex, std::string fragment);
	GPURenderPass* createRenderPass(bool mainRenderPass, GPUFramebuffer* framebuffer, bool disallowRenderToNotPriorityItems);
	GPUFramebuffer* createFramebuffer(GPUFramebufferType type);
	GPUTexture* createTexture(std::string filepath);
	void createAtmosphere();
	void drawQueue(GPUMesh* mesh, GPUShader* shader, Transform* transform, GPUMaterial* material);
	void begin();
	void end();
};


class GPUFramebuffer {
public:
	std::map<std::string, std::any> unbaseVars;
	GPUFramebufferType type;
	void bind();
	static void unbind();
};

class GPURenderPass {
public:
	std::map<std::string, std::any> unbaseVars;
	bool useFramebuffer;
	glm::vec2 customViewport = glm::vec2(0.0f, 0.0f);
	GPUFramebuffer* framebuffer;
	bool disallowToRenderNotPriorityItems;
	void begin(GPUContext* context);
	void end(GPUContext* context);
};

class GPUShader {
public:
	std::map<std::string, std::any> unbaseVars;
	void bind();
	void shaderInputDataMat4(std::string name, glm::mat4 val);
	void shaderInputDataFloat(std::string name, float val);
	void shaderInputDataInt(std::string name, int val);
	void shaderInputDataVec3(std::string name, glm::vec3 val);
	static void unbind();
};

class GPUMesh {
public:
	std::map<std::string, std::any> unbaseVars;
	GPUBuffer* vertexBuffer;
	GPUBuffer* indexBuffer;
	int vertexCount;
	void drawDirect(GPUContext* context, GPUShader* shader, GPUMaterial* material, Transform* transform);
};

class GPUDrawData {
public:
	GPUShader* shader;
	GPUMesh* mesh;
	GPUMaterial* material;
	Transform* transform;
};

enum GPUBufferType {
	VERTEXBUFFER,
	INDEXBUFFER,
	SHADERINPUTBUFFER
};

class GPUBuffer {
public:
	GPUBufferType bufferType;
	std::map<std::string, std::any> unbaseVars;
	void bind(GPUContext* context);
	void uploadData(GPUContext* context, const void* copyData, int size);
	void unbind();
};

class GPUWindow {
public:
	std::map<std::string, Obj> unbaseVars;
	std::string title;
	int width, height;
	void createWindow(std::string title, int width, int height);
};

class GPUMaterial {
public:
	GPUTexture* texture;
	glm::vec3 albedoColor = glm::vec3(1, 1, 1);
	bool useLighting = true;
};

class GPUSkybox {
public:
	GPUMesh* cubeMesh;
	void update(GPUContext* context);
};

class ShaderManager {
public:
	std::map<std::string,GPUShader*> shaders;
	GPUShader* shaderByName(std::string name) {
		return shaders[name];
	}
};