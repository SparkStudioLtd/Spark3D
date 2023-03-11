#include "../PanelManager.hpp"

class ActorInfoPanel : public Panel {
public:
	void render() {
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
                    float floatType_identifier = 0.0f;
                    glm::vec3 vecType_identifier = glm::vec3(0, 0, 0);

                    const char* strType = typeid(strType_identifier).name();
                    const char* intType = typeid(intType_identifier).name();
                    const char* floatType = typeid(floatType_identifier).name();
                    const char* vecType = typeid(vecType_identifier).name();

                    const char* compomentValue = value.second.m_Handle.type().name();

                    std::any finalVal = value.second;

                    if (compomentValue == vecType) {
                        glm::vec3 valueVec = std::any_cast<glm::vec3>(value.second.m_Handle);
                        Spark::DrawVec3Control(value.first, valueVec);
                        if (valueVec != std::any_cast<glm::vec3>(value.second.m_Handle)) {
                            component->components[value.first].set<glm::vec3>(valueVec);
                        }
                    }
                    else if (compomentValue == floatType) {
                        float valueFloat = std::any_cast<float>(value.second.m_Handle);
                        std::string strFromFloat = std::to_string(valueFloat);
                        ImGui::InputText("##ctor4", &strFromFloat);
                        if (strFromFloat != "") {
                            if (std::stof(strFromFloat) != std::any_cast<float>(value.second.m_Handle)) {
                                component->components[value.first].set<float>(std::stof(strFromFloat));
                            }
                        }
                    }

                }
                ImGui::Separator();

            }
        }
	}
};