class Monkey : public Component {
public:
    virtual void BeginPlay(Actor* actor) {
        std::cout << "xd" << std::endl;
        this->components["addCount"] = Obj();
        this->components["addCount"].set<float>(1.0f);
    }
    virtual void Update(Actor* actor) {
        this->name = "Rotator";
    }
    virtual void Render(GPUContext* context, Actor* actor) {
        actor->transform->setRotation(actor->transform->getRotation() + this->components["addCount"].get<float>());
    }
};

class ToolboxPanel : public Panel {
public:
    bool PropertyGridHeader(const std::string& name, bool openByDefault = true)
    {
        ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_Framed
            | ImGuiTreeNodeFlags_SpanAvailWidth
            | ImGuiTreeNodeFlags_AllowItemOverlap
            | ImGuiTreeNodeFlags_FramePadding;

        if (openByDefault)
            treeNodeFlags |= ImGuiTreeNodeFlags_DefaultOpen;

        bool open = false;
        const float framePaddingX = 6.0f;
        const float framePaddingY = 6.0f; // affects height of the header

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ framePaddingX, framePaddingY });

        //UI::PushID();
        ImGui::PushID(name.c_str());
        open = ImGui::TreeNodeEx("##dummy_id", treeNodeFlags, name.c_str());
        //UI::PopID();
        ImGui::PopStyleVar(2);
        ImGui::PopID();
        return open;
    }
    void render() {
        if (ImGui::Button("Cube")) {
            Actor* actor = Spark::CreateActorInQueue();
            Monkey* monkey = new Monkey();
            monkey->BeginPlay(actor);
            GPUMaterial* material = new GPUMaterial();
            material->useLighting = true;
            //material->texture = Spark::graphicsContext->createTexture("./res/burger.png");
            material->texture = nullptr;
            material->albedoColor = glm::vec3(1,0,0);
            Renderer* renderer = new Renderer();
            renderer->setMaterial(material);
            renderer->setMesh(Spark::geometry->cube);
            //actor->addComponent(Spark::geometry->getCube(material));
            actor->addComponent(renderer);
            actor->addComponent(monkey);
            actor->addComponent(ScriptManager::m_Scripts["TestComponent"]);
        }
        if (PropertyGridHeader("Bloom")) {
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(120, 120, 120, 255));
            ImGui::SetWindowFontScale(0.945f);
            ImGui::Text("Beta-Feature");
            ImGui::PopStyleColor();
            ImGui::SetWindowFontScale(1.0f);
            ImGui::Separator();
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(120, 120, 120, 255));
            ImGui::SetWindowFontScale(0.945f);
            ImGui::Text("Bloom Map Preview");
            ImGui::PopStyleColor();
            ImGui::SetWindowFontScale(1.0f);
            ImGui::Image((void*)std::any_cast<int>(Spark::graphicsContext->blurTechnique[1]->unbaseVars["textureColorBuffer"]), ImVec2(512, 512), ImVec2(0, 1), ImVec2(1, 0));
            ImGui::TreePop();
        }
    }
};