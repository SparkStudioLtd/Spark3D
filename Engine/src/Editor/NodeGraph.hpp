#include "CoreFramework.h"


static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
class NodeGraph {
public:
	Actor* actor;
	void render() {
        float offsetX = 20;
        for (int i = 0; i < 50; i++) {
            ImGui::GetWindowDrawList()->AddLine(ImVec2(ImGui::GetWindowPos().x + offsetX, ImGui::GetWindowPos().y), ImVec2(ImGui::GetWindowPos().x + offsetX, ImGui::GetWindowPos().y + 1100), IM_COL32(32, 32, 32, 200), 2.0f);
            offsetX += 110;
        }
        float offsetY = 20;
        for (int i = 0; i < 50; i++) {
            ImGui::GetWindowDrawList()->AddLine(ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y + offsetY), ImVec2(ImGui::GetWindowPos().x + 2100, ImGui::GetWindowPos().y + offsetY), IM_COL32(32, 32, 32, 200), 2.0f);
            offsetY += 110;
        }
        if (actor == nullptr) {
            ImGui::Text("Debug: Select any object to render graph!");
        }
        else {
            if (ImGui::InvisibleButton("node", ImVec2(200, 200))) {
                std::cout << "click" << std::endl;
            }


            ImVec2 pos = ImGui::GetWindowPos() + ImVec2(100, 100);
            ImGui::SetCursorScreenPos(pos);

            ImGui::GetWindowDrawList()->AddRectFilledMultiColor(pos, pos + ImVec2(200, 20), IM_COL32(28, 28, 28, 255), IM_COL32(32, 32, 32, 255), IM_COL32(32, 32, 32, 255), IM_COL32(28, 28, 28, 255));
            ImGui::GetWindowDrawList()->AddRectFilled(pos + ImVec2(0, 20), pos + ImVec2(200, 180), IM_COL32(24, 24, 24, 255), 3.0f);
            ImGui::SetCursorScreenPos(pos + ImVec2(4.5f, 2.5f));
            ImGui::Text("BeginPlay");
            ImGui::SetCursorScreenPos(pos + ImVec2(4.5f, 22.5f));
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(120, 120, 120, 255));
            ImGui::SetWindowFontScale(0.945f);
            ImGui::Text("Started game event");
            ImGui::PopStyleColor();
            ImGui::SetWindowFontScale(1.0f);
            ImGui::GetWindowDrawList()->AddCircleFilled(pos + ImVec2(199.5f, 40.0f), 6, IM_COL32(48, 48, 48, 255));

        }
	}
};