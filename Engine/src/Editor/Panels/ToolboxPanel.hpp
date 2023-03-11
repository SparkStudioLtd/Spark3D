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
    void render() {
        if (ImGui::Button("Cube")) {
            Actor* actor = Spark::CreateActorInQueue();

            Monkey* monkey = new Monkey();
            monkey->BeginPlay(actor);
            actor->addComponent(Spark::geometry->getCube());
            actor->addComponent(monkey);

        }
    }
};