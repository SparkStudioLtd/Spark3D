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
            GPUMaterial* material = new GPUMaterial();
            material->useLighting = true;
            material->texture = Spark::graphicsContext->createTexture("./res/burger.png");


            Renderer* renderer = new Renderer();
            renderer->setMaterial(material);
            renderer->setMesh(Spark::geometry->cube);


            //actor->addComponent(Spark::geometry->getCube(material));



            actor->addComponent(renderer);
            actor->addComponent(monkey);

        }
    }
};