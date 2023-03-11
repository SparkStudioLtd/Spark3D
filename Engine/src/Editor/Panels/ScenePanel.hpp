class ScenePanel : public Panel {
public:
    void render() {
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
    }
};