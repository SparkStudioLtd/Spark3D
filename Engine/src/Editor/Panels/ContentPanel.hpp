class ContentPanel : public Panel {
public:
    void render() {
        for (Asset* asset : AssetManager::m_Assets) {
            ImGui::Text(asset->m_Name.c_str());
        }
    }
};