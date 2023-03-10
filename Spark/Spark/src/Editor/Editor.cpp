#include "Editor.h"

class Renderer : public Component {
public:
	GPUMesh* mesh;
	GPUMaterial* material;
	virtual void BeginPlay(Actor* actor) {

	}
	virtual void Update(Actor* actor) {

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

class Monkey : public Component {
public:
	virtual void BeginPlay(Actor* actor) {
	}
	virtual void Update(Actor* actor) {

	}
	virtual void Render(GPUContext* context, Actor* actor) {
		actor->transform->rotation += 1;
	}
};

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
	virtual void Render(GPUContext* context,Actor* actor) {
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

namespace Colours {
    namespace Theme
    {
        constexpr auto accent = IM_COL32(236, 158, 36, 255);
        constexpr auto highlight = IM_COL32(39, 185, 242, 255);
        constexpr auto niceBlue = IM_COL32(83, 232, 254, 255);
        constexpr auto compliment = IM_COL32(78, 151, 166, 255);
        constexpr auto background = IM_COL32(36, 36, 36, 255);
        constexpr auto backgroundDark = IM_COL32(26, 26, 26, 255);
        constexpr auto titlebar = IM_COL32(21, 21, 21, 255);
        constexpr auto propertyField = IM_COL32(15, 15, 15, 255);
        constexpr auto text = IM_COL32(192, 192, 192, 255);
        constexpr auto textBrighter = IM_COL32(210, 210, 210, 255);
        constexpr auto textDarker = IM_COL32(128, 128, 128, 255);
        constexpr auto muted = IM_COL32(77, 77, 77, 255);
        constexpr auto groupHeader = IM_COL32(47, 47, 47, 255);
        //constexpr auto selection				= IM_COL32(191, 177, 155, 255);
        //constexpr auto selectionMuted			= IM_COL32(59, 57, 45, 255);
        constexpr auto selection = IM_COL32(36, 163, 236, 255);
        constexpr auto selectionMuted = IM_COL32(36, 163, 236, 23);

        //constexpr auto backgroundPopup			= IM_COL32(63, 73, 77, 255); // in between
        //constexpr auto backgroundPopup			= IM_COL32(63, 77, 76, 255); // most green
        constexpr auto backgroundPopup = IM_COL32(50, 50, 50, 255); // most blue
    }
}

void UISetMorganStyle()
{
    auto& style = ImGui::GetStyle();
    auto& colors = ImGui::GetStyle().Colors;

    //========================================================
    /// Colours

    // Headers
    colors[ImGuiCol_Header] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::groupHeader);
    colors[ImGuiCol_HeaderHovered] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::groupHeader);
    colors[ImGuiCol_HeaderActive] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::groupHeader);

    // Buttons
    colors[ImGuiCol_Button] = ImColor(56, 56, 56, 200);
    colors[ImGuiCol_ButtonHovered] = ImColor(70, 70, 70, 255);
    colors[ImGuiCol_ButtonActive] = ImColor(56, 56, 56, 150);

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::propertyField);
    colors[ImGuiCol_FrameBgHovered] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::propertyField);
    colors[ImGuiCol_FrameBgActive] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::propertyField);

    // Tabs
    colors[ImGuiCol_Tab] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::titlebar);
    colors[ImGuiCol_TabHovered] = ImColor(255, 225, 135, 30);
    colors[ImGuiCol_TabActive] = ImColor(255, 225, 135, 60);
    colors[ImGuiCol_TabUnfocused] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::titlebar);
    colors[ImGuiCol_TabUnfocusedActive] = colors[ImGuiCol_TabHovered];

    // Title
    colors[ImGuiCol_TitleBg] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::titlebar);
    colors[ImGuiCol_TitleBgActive] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::titlebar);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Resize Grip
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.91f, 0.91f, 0.91f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.81f, 0.81f, 0.81f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.95f);

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.0f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.0f);

    // Check Mark
    colors[ImGuiCol_CheckMark] = ImColor(200, 200, 200, 255);

    // Slider
    colors[ImGuiCol_SliderGrab] = ImVec4(0.51f, 0.51f, 0.51f, 0.7f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.66f, 0.66f, 0.66f, 1.0f);

    // Text
    colors[ImGuiCol_Text] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::text);

    // Checkbox
    colors[ImGuiCol_CheckMark] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::text);

    // Separator
    colors[ImGuiCol_Separator] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::backgroundDark);
    colors[ImGuiCol_SeparatorActive] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::highlight);
    colors[ImGuiCol_SeparatorHovered] = ImColor(39, 185, 242, 150);

    // Window Background
    colors[ImGuiCol_WindowBg] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::titlebar);
    colors[ImGuiCol_ChildBg] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::background);
    colors[ImGuiCol_PopupBg] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::backgroundPopup);
    colors[ImGuiCol_Border] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::backgroundDark);

    // Tables
    colors[ImGuiCol_TableHeaderBg] = ImGui::ColorConvertU32ToFloat4(IM_COL32(26, 26, 26, 255));
    colors[ImGuiCol_TableRowBgAlt] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::backgroundDark);
    colors[ImGuiCol_TableRowBg] = ImGui::ColorConvertU32ToFloat4(Colours::Theme::groupHeader);
    colors[ImGuiCol_TableBorderLight] = ImGui::ColorConvertU32ToFloat4(IM_COL32(20, 20, 20, 255));

    // Menubar
    colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.0f, 0.0f, 0.0f, 0.0f };

    //========================================================
    /// Style
    style.FrameRounding = 2.5f;
    style.FrameBorderSize = 1.0f;
    style.IndentSpacing = 11.0f;
}

void Hook::imguiInit() {
    UISetMorganStyle();
    Asset* asset = AssetManager::getAsset("EditorContent_Fonts_Roboto");
    ImGui::GetIO().Fonts->AddFontFromMemoryTTF(&asset->m_LoadedAsset.blob[0], sizeof(&asset->m_LoadedAsset.blob[0]), 15);
}

void renderViewport() {
    ImGui::Begin("Viewport");
    ImGui::Image((void*)std::any_cast<int>(Spark::graphicsContext->renderPasses[1]->framebuffer->unbaseVars["textureColorBuffer"]), ImGui::GetWindowSize(), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();

    ImGui::Begin("Scene");
    ImGui::End();

    ImGui::Begin("Actor");
    ImGui::End();

    ImGui::Begin("Content");
    ImGui::End();

    ImGui::Begin("Toolbox");
    if (ImGui::Button("Cube")) {
        Actor* actor = Spark::CreateActor();
        Renderer* renderer = new Renderer();

    }
    ImGui::End();

    ImGui::Begin("Performance");
    ImGui::End();
}

void Hook::imguiRender() {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("Dockspace", nullptr, window_flags);
    {
        auto windowWidth = ImGui::GetWindowSize().x;
        auto textWidth = ImGui::CalcTextSize("Spark Engine a1").x;
        ImGui::SetCursorPos(ImVec2((windowWidth - textWidth) * 0.5f, 20));
        ImGui::Text("Spark Engine a1");

        ImGui::SetCursorPosY(64);
        ImGui::DockSpace(ImGui::GetID("MyDockspace"));
        renderViewport();
    }
    ImGui::End();
}