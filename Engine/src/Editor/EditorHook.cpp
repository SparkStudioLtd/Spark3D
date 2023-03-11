#define SPARK_EDITOR

#ifdef SPARK_EDITOR
#include "Editor.h"
Editor* editor = new Editor();

class UI : public Component {
public:
	virtual void BeginPlay(Actor* actor) {
		Spark::graphicsContext->useGui = true;
		GLFWwindow* window = Spark::graphicsContext->window->unbaseVars["windowHandle"].get<GLFWwindow*>();
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::StyleColorsDark();
		Hook::imguiInit();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330 core");
	}
	virtual void Render(GPUContext* context, Actor* actor) {
		GLFWwindow* window = Spark::graphicsContext->window->unbaseVars["windowHandle"].get<GLFWwindow*>();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		Hook::imguiRender();

		ImGui::Render();
	}
	virtual void Update(Actor* actor) {
		this->priorityRendering = true;
	}
};


void Hook::appReady() {
	Actor* guiActor = Spark::CreateActor();
	guiActor->addComponent(new UI());
}
void Hook::imguiInit() {
	editor->init();
}
void Hook::imguiRender() {
	editor->render();
}
#endif