static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

void Node::sendSignal() {

}

class VisualScriptingPanel : public Panel {
public:
    void render() {
        if (selectedActor != nullptr)
        {
            if (selectedActor->m_Nodes.size() == 0) {
                Node* beginPlay = new Node();
                beginPlay->m_Name = "BeginPlay";
                beginPlay->m_Desc = "Start game event";

                NodeOutput* output = new NodeOutput();
                output->m_Name = "Signal";
                beginPlay->outputs.push_back(output);
                Node* update = new Node();
                update->m_Name = "Update";
                update->m_Desc = "Update game event";
                NodeOutput* outputUpdate = new NodeOutput();
                outputUpdate->m_Name = "Signal";
                update->outputs.push_back(outputUpdate);
                Node* render = new Node();
                render->m_Name = "Render";
                render->m_Desc = "Render game event";
                NodeOutput* outputRender = new NodeOutput();
                Node* printNode = new Node();
                printNode->m_Name = "Print";
                printNode->m_Desc = "Printing text";
                outputRender->connectedNode = printNode;
                outputRender->m_Name = "Signal";
                render->outputs.push_back(outputRender);

                selectedActor->m_Nodes.push_back(beginPlay);
                selectedActor->m_Nodes.push_back(printNode);
                selectedActor->m_Nodes.push_back(update);
                selectedActor->m_Nodes.push_back(render);
            }
            Actor* actor = selectedActor;
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
                ImGui::Button("Compile");
                float offsetA = 100;
                for (Node* node : selectedActor->m_Nodes) {
                    ImVec2 pos = ImGui::GetWindowPos() + ImVec2(100, offsetA);
                    ImGui::SetCursorScreenPos(pos);

                    float sizeY = 180;

                    float nodeInputSize = node->inputs.size() * 20;
                    float nodeOutputSize = node->outputs.size() * 20;
                    if (std::max(nodeInputSize, nodeOutputSize) == nodeInputSize) {
                        sizeY = nodeInputSize + 40;
                    }
                    else {
                        sizeY = nodeOutputSize + 40;
                    }

                    if (ImGui::InvisibleButton("node", ImVec2(200, sizeY))) {
                        std::cout << "click" << std::endl;
                    }

                    ImGui::GetWindowDrawList()->AddRectFilledMultiColor(pos, pos + ImVec2(200, 20), IM_COL32(28, 28, 28, 255), IM_COL32(32, 32, 32, 255), IM_COL32(32, 32, 32, 255), IM_COL32(28, 28, 28, 255));
                    ImGui::GetWindowDrawList()->AddRectFilled(pos + ImVec2(0, 20), pos + ImVec2(200, sizeY), IM_COL32(24, 24, 24, 255), 10.0f, ImDrawFlags_RoundCornersAll);
                    ImGui::SetCursorScreenPos(pos + ImVec2(4.5f, 2.5f));
                    ImGui::Text(node->m_Name.c_str());
                    ImGui::SetCursorScreenPos(pos + ImVec2(4.5f, 22.5f));
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(120, 120, 120, 255));
                    ImGui::SetWindowFontScale(0.945f);
                    ImGui::Text(node->m_Desc.c_str());
                    ImGui::PopStyleColor();
                    ImGui::SetWindowFontScale(1.0f);
                    float inputOffset = 0;
                    for (NodeInput* input : node->inputs) {
                        ImGui::GetWindowDrawList()->AddCircleFilled(pos + ImVec2(0, 40.0f + inputOffset), 6, IM_COL32(48, 48, 48, 255));
                        inputOffset += 20;
                    }
                    float outputOffset = 0;
                    for (NodeOutput* output : node->outputs) {
                        ImGui::GetWindowDrawList()->AddCircleFilled(pos + ImVec2(199.5f, 40.0f + outputOffset), 6, IM_COL32(48, 48, 48, 255));
                        ImGui::GetWindowDrawList()->AddBezierCurve(pos + ImVec2(199.5f, 40.0f + outputOffset), (pos + ImVec2(199.5f, 40.0f + outputOffset)) + ImVec2(+50, 0), (pos + ImVec2(300.5f, 90.0f + outputOffset)) + ImVec2(-50, 0), pos + ImVec2(300.5f, 90.0f + outputOffset), IM_COL32(255, 255, 255, 255), 3.0f);
                        outputOffset += 20;
                    }

                    offsetA += 100 + sizeY;
                }



            }
        }
    }
};