class PerformancePanel : public Panel {
public:
    void render() {
        ImGui::Text((std::string("Actor Count: ") + std::to_string(Spark::actors.size())).c_str());
        ImGui::Text((std::string("Actor In Queue Count: ") + std::to_string(Spark::actorsQueue.size())).c_str());
        ImGui::Text((std::string("Frames Per Secound: ") + std::to_string(Spark::framesPerSecound)).c_str());
        if (Spark::graphicsVendor != "") {
            ImGui::Text((std::string("Graphics Vendor: ") + Spark::graphicsVendor).c_str());
            ImGui::Text((std::string("Graphics Renderer: ") + Spark::graphicsRendererVendor).c_str());
        }
    }
};