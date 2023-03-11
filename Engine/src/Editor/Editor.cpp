#include "Editor.h"
#include <imgui/imgui_internal.h>
#include <imgui/imgui_stdlib.h>


class Monkey : public Component {
public:
	virtual void BeginPlay(Actor* actor) {
	}
	virtual void Update(Actor* actor) {
        this->name = "Rotator";
	}
	virtual void Render(GPUContext* context, Actor* actor) {
        actor->transform->setRotation(actor->transform->getRotation() + 1.0f);
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

void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
{
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    ImGui::PushID(label.c_str());

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("X", buttonSize))
        values.x = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Y", buttonSize))
        values.y = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Z", buttonSize))
        values.z = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();

    ImGui::Columns(1);

    ImGui::PopID();
}


Actor* selectedActor = nullptr;

void renderViewport() {
    ImGui::Begin("Viewport");
    ImGui::Image((void*)std::any_cast<int>(Spark::graphicsContext->renderPasses[1]->framebuffer->unbaseVars["textureColorBuffer"]), ImGui::GetWindowSize(), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();

    ImGui::Begin("Scene");

    ImGuiTableFlags tableFlags = ImGuiTableFlags_NoPadInnerX
        | ImGuiTableFlags_Resizable
        | ImGuiTableFlags_Reorderable
        | ImGuiTableFlags_ScrollY
        | ImGuiTableFlags_RowBg; //*| ImGuiTableFlags_Sortable*/;


    ImGui::BeginTable("#hierarhy", 3, tableFlags);

    ImGui::TableSetupColumn("Name");
    ImGui::TableSetupColumn("Type");
    ImGui::TableSetupColumn("Select");


    ImGui::TableSetupScrollFreeze(ImGui::TableGetColumnCount(), 1);
    ImGui::TableNextRow(ImGuiTableRowFlags_Headers, 22.0f);
    for (int column = 0; column < ImGui::TableGetColumnCount(); column++)
    {
        ImGui::TableSetColumnIndex(column);
        const char* column_name = ImGui::TableGetColumnName(column);
        ImGui::TableHeader(column_name);
    }
    ImGui::SetCursorPosX(ImGui::GetCurrentTable()->OuterRect.Min.x);

    for (int index = 0; index < Spark::actors.size(); index++) {
        Actor* actor = Spark::actors[index];
        ImGui::TableNextColumn();
        ImGui::Text(actor->name.c_str());
        ImGui::TableNextColumn();
        ImGui::Text("");
        ImGui::TableNextColumn();
        if (ImGui::Button((std::string("Select##") + std::to_string(index)).c_str())) {
            selectedActor = actor;
        }
    }


    ImGui::EndTable();
    ImGui::End();

    ImGui::Begin("Actor");
    if (selectedActor == nullptr) {
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(120, 120, 120, 255));
        ImGui::SetWindowFontScale(0.945f);
        ImGui::Text("Select any actor");
        ImGui::PopStyleColor();
        ImGui::SetWindowFontScale(1.0f);
    }
    else {
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(120, 120, 120, 255));
        ImGui::SetWindowFontScale(0.945f);
        ImGui::Text("Name:");
        ImGui::PopStyleColor();
        ImGui::SetWindowFontScale(1.0f);
        ImGui::SameLine();
        ImGui::InputText("##actorName", &selectedActor->name);
        ImGui::NewLine();

        ImGui::Separator();
        for (Component* component : selectedActor->components) {
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(120, 120, 120, 255));
            ImGui::SetWindowFontScale(0.945f);
            ImGui::Text(component->name.c_str());
            ImGui::PopStyleColor();
            ImGui::SetWindowFontScale(1.0f);

            for (auto const& value : component->components) {
                ImGui::Text(value.first.c_str());

                ImGui::SameLine();

                std::string strType_identifier = "";
                int intType_identifier = 0;
                glm::vec3 vecType_identifier = glm::vec3(0, 0, 0);

                const char* strType = typeid(strType_identifier).name();
                const char* intType = typeid(intType_identifier).name();
                const char* vecType = typeid(vecType_identifier).name();

                const char* compomentValue = value.second.m_Handle.type().name();

                std::any finalVal = value.second;

                if (compomentValue == vecType) {
                    glm::vec3 valueVec = std::any_cast<glm::vec3>(value.second.m_Handle);
                    DrawVec3Control(value.first, valueVec);
                    if (valueVec != std::any_cast<glm::vec3>(value.second.m_Handle)) {
                        component->components[value.first].set<glm::vec3>(valueVec);
                    }
                }

            }
            ImGui::Separator();

        }
    }
    ImGui::End();

    ImGui::Begin("Content");
    for (Asset* asset : AssetManager::m_Assets) {
        ImGui::Text(asset->m_Name.c_str());
    }
    ImGui::End();

    ImGui::Begin("Toolbox");
    if (ImGui::Button("Cube")) {
        Actor* actor = Spark::CreateActorInQueue();

        actor->addComponent(Spark::geometry->getCube());
        actor->addComponent(new Monkey());

    }
    ImGui::End();

    ImGui::Begin("Performance");
    ImGui::Text((std::string("Actor Count: ") + std::to_string(Spark::actors.size())).c_str());
    ImGui::Text((std::string("Actor In Queue Count: ") + std::to_string(Spark::actorsQueue.size())).c_str());
    ImGui::Text((std::string("Frames Per Secound: ") + std::to_string(Spark::framesPerSecound)).c_str());
    if (Spark::graphicsVendor != "") {
        ImGui::Text((std::string("Graphics Vendor: ") + Spark::graphicsVendor).c_str());
        ImGui::Text((std::string("Graphics Renderer: ") + Spark::graphicsRendererVendor).c_str());
    }
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