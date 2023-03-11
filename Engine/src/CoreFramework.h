#include "pch.h"

//I'm only human after all
//I'm only human after all

//moved to one header cuz linker errors...

#include "Core/JSON.h"



class Spark;
class Hook;
class Job;
class RenderJob;
class InitalizeJob;
class AssetManager;
class Asset;
struct LoadedAsset;
enum AssetType;
struct Color;
class Geometry;
class Renderer;
class Obj;
class JobSystem;
class ModelLoader;
class Job;
enum JobSyncType;
enum JobExecuteType;
class Event;
enum EventType;
class ShaderManager;
class GPUSkybox;
class GPUMaterial;
class GPUWindow;
class GPUBuffer;
enum GPUBufferType;
class GPUDrawData;
class GPUMesh;
class Transform;
class GPUShader;
class GPURenderPass;
class GPUFramebuffer;
class GPUContext;
class CSG;
class GPUViewport;
class GPUTexture;
class Camera;
enum GPUFramebufferType;
enum CameraProjectionType;
struct Vertex;
class Component;
class Actor;

class Obj {
public:
	std::any m_Handle;
	Obj() {}
	Obj(std::any g_Handle) {
		this->m_Handle = g_Handle;
	}
	template<typename T> T get() {
		return std::any_cast<T>(this->m_Handle);
	};
	template<typename T> void set(T clazz) {
		this->m_Handle = clazz;
	}
};


struct Color {
public:
	float red, green, blue, alpha;
	Color() {

	}
	Color(float v1, float v2, float v3, float v4) : red(v1), green(v2), blue(v3), alpha(v4) {

	}
	glm::vec4 toVec4() {
		return glm::vec4(red, green, blue, alpha);
	}
	static Color get255Color(float v1, float v2, float v3, float v4) {
		return Color((int)v1 * 255, (int)v2 * 255, (int)v3 * 255, (int)v4 * 255);
	}
	static Color get1Color(float v1, float v2, float v3, float v4) {
		return Color((float)v1 / 255.0f, (float)v2 / 255.0f, (float)v3 / 255.0f, (float)v4 / 255.0f);
	}

};

struct ApplicationSpecification {
public:
	std::string Name;
	int Width;
	int Height;
};


class Spark {
public:
	static bool m_ApplicationRunning;

	static ApplicationSpecification applicationSpecification;
	static GPUContext* graphicsContext;
	static ShaderManager* shaderManager;
	static std::vector<Actor*> actors;
	static std::vector<Actor*> actorsQueue;

	static Geometry* geometry;

	static Actor* CreateActor();
	static Actor* CreateActorInQueue();

	static int framesPerSecound;

	static std::string graphicsVendor;
	static std::string graphicsRendererVendor;

	static void CreateCore();
	static void RegisterApplicationSpecification(ApplicationSpecification appSpec);
	static void EnterLoop();
	static void Shutdown();
};

class Component {
public:
	std::string name;
	std::map<std::string, Obj> components;
	bool priorityRendering = false;
	virtual void BeginPlay(Actor* actor);
	virtual void Update(Actor* actor);
	virtual void Render(GPUContext* context, Actor* actor);
};

class Actor {
public:
	std::string name = "Actor";
	Transform* transform;
	std::vector<Component*> components;
	void addComponent(Component* component);
};

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

class Transform : public Component {
public:
	glm::vec3 getPosition() {
		return components["Position"].get<glm::vec3>();
	}
	glm::vec3 getRotation() {
		return components["Rotation"].get<glm::vec3>();
	}
	glm::vec3 getScale() {
		return components["Scale"].get<glm::vec3>();
	}
	void setPosition(glm::vec3 position) {
		components["Position"].set<glm::vec3>(position);
	}
	void setRotation(glm::vec3 rotation) {
		components["Rotation"].set<glm::vec3>(rotation);
	}
	void setScale(glm::vec3 scale) {
		components["Scale"].set<glm::vec3>(scale);
	}
	void setTransform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
		this->setPosition(position);
		this->setRotation(rotation);
		this->setScale(scale);
	}

	virtual void BeginPlay(Actor* actor) {}
	virtual void Update(Actor* actor) {
	}
	virtual void Render(GPUContext* context, Actor* actor) {}
	glm::vec3 getForward() {
		glm::vec3 rotation = this->getRotation();
		return glm::vec3(cos(rotation.x) * sin(rotation.y), -sin(rotation.x), cos(rotation.x) * cos(rotation.y));
	}
	glm::vec3 getRight() {
		glm::vec3 rotation = this->getRotation();
		return glm::vec3(cos(rotation.y), 0, -sin(rotation.y));
	}
	glm::vec3 getUp() {
		return glm::cross(this->getForward(), this->getRight());
	}
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
	std::map<std::string, GPUShader*> shaders;
	GPUShader* shaderByName(std::string name) {
		return shaders[name];
	}
};


enum EventType {
	UPDATE,
	MOUSE,
	KEYBOARD
};

class Event {
public:
	EventType m_EventType;
};


enum JobExecuteType {
	ONCE,
	EVENTHANDLER
};

enum JobSyncType {
	ASYNC,
	SYNC
};

class Job {
public:
	std::string m_DebugName;
	JobExecuteType m_executeType;
	JobSyncType m_syncType;
	virtual void setup();
	virtual void execute(Event* event);
	virtual void clean();
	void log(std::string content);
};

class JobSystem {
public:
	static void AddJob(Job* job);
	static std::vector<Job*> m_Jobs;
	static void update();
	static void clean();
};

class ModelLoader {
public:
	static GPUMesh* loadMesh(GPUContext* context, std::string file);
};


class Renderer : public Component {
public:
	GPUMesh* mesh;
	GPUMaterial* material;
	virtual void BeginPlay(Actor* actor) {

	}
	virtual void Update(Actor* actor) {
		this->name = "Renderer";
	}
	virtual void Render(GPUContext* context, Actor* actor) {
		if (context->renderingToDepthMap) {
			context->drawQueue(this->mesh, Spark::shaderManager->shaderByName("ShadowPass"), actor->transform, this->material);
		}
		else {
			context->drawQueue(this->mesh, Spark::shaderManager->shaderByName("GBuffer"), actor->transform, this->material);
		}
	}
};

class Geometry {
public:
	void init();
	Renderer* getCube(GPUMaterial* material = nullptr);
private:
	GPUMesh* cube;
};



enum AssetType {
	FONT
};

struct LoadedAsset {
public:
	std::string description;
	std::vector<char> blob;
	char type[4];
	int version;
};

class Asset {
public:
	std::any m_Handle;
	AssetType m_AssetType;
	std::string m_ToSavePath;
	std::string m_Name;
	std::string m_AssetFilePath;
	nlohmann::json m_AssetInfo;
	LoadedAsset m_LoadedAsset;
	AssetType m_Type;
	void save();
	void load();
	void typeLoad();
	std::vector<char> getTypeShort();
	std::vector<char> getBlob();
	AssetType getEnum(std::vector<char> type);
	std::string getDescription();
};

class AssetManager {
public:
	static std::vector<Asset*> m_Assets;
	static void loadFromFolder();
	static Asset* getAsset(std::string m_Name);
};

class InitalizeJob : public Job {
public:
	void setup();
	void execute(Event* event);
	void clean();
};

class RenderJob : public Job {
public:
	bool firstUpdate = true;
	void setup();
	void execute(Event* event);
	void clean();
};


class Hook {
public:
	static void appReady();
	static void imguiInit();
	static void imguiRender();
};
