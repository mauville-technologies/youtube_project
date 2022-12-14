#include <youtube_engine/platform/entry_point.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <youtube_engine/core/entity.h>
#include <youtube_engine/core/components/mesh_component.h>
#include <youtube_engine/core/components/transform_component.h>

using namespace OZZ;

class YoutubeGame : public Game {
public:
    explicit YoutubeGame(std::string title) : Game(std::move(title)) {
        std::cout << "Hello, Youtube game!" << std::endl;

        _inputManager = ServiceLocator::GetInputManager();

        if (_inputManager) {
            // Map inputs
            _inputManager->MapInputToAction(InputKey::KEY_A, InputAction {
                .actionName = "strafe",
                .scale = -1.f
            });

            _inputManager->MapInputToAction(InputKey::KEY_D, InputAction {
                    .actionName = "strafe",
                    .scale = 1.f
            });
            _inputManager->MapInputToAction(InputKey::GAMEPAD_L_THUMB_X, InputAction {
                    .actionName = "strafe",
                    .scale = 1.f
            });
            _inputManager->MapInputToAction(InputKey::GAMEPAD_L_THUMB_Y, InputAction {
                    .actionName = "moveForward",
                    .scale = 1.f
            });

            _inputManager->MapInputToAction(InputKey::MOUSE_LEFT, InputAction {
                .actionName = "click",
                .scale = 1.f
            });

            _inputManager->RegisterActionCallback("strafe", InputManager::ActionCallback {
                .Ref = "YoutubeGame",
                .Func = [this](InputSource source, int sourceIndex, float value) {
//                    std::string direction {"NONE"};
//
//                    if (value > 0.f) direction = "RIGHT";
//                    if (value < 0.f) direction = "LEFT";
//                    std::cout << "STRAFING " << direction << "\n";
                    return true;
                }
            });

            _inputManager->RegisterActionCallback("moveForward", InputManager::ActionCallback {
                    .Ref = "YoutubeGame",
                    .Func = [](InputSource source, int sourceIndex, float value) {
                        std::string direction {"NONE"};

                        if (value > 0.f) direction = "UP";
                        if (value < 0.f) direction = "DOWN";
                        std::cout << "MOVING " << direction << "\n";
                        return true;
                    }
            });

            _inputManager->RegisterActionCallback("click", InputManager::ActionCallback {
               .Ref = "YoutubeGame",
               .Func = [this](InputSource source, int sourceIndex, float value) {
                   handleClick(value);
                   return true;
               }
            });

            SetupScene();
        }
    }

    void OnExit() override {

    }

    void SetupScene() {
        for (auto i : {1, 2, 3, 4, 5}) {
            entities.push_back(GetScene()->CreateEntity());
        }

        auto mesh = ServiceLocator::GetResourceManager()->Load<Mesh>("meshes/BasicCube/DiffuseOnly/BasicCube.glb");
        entities[0]->AddComponent<MeshComponent>(std::move(mesh));
        auto& transform = entities[0]->AddComponent<TransformComponent>();
        transform.Scale *= 0.5f;

        auto mesh2 = ServiceLocator::GetResourceManager()->Load<Mesh>("meshes/BasicCone.glb");
        entities[1]->AddComponent<MeshComponent>(std::move(mesh2));
        auto& transform2 = entities[1]->AddComponent<TransformComponent>();
        transform2.Translation = glm::vec3(-2.5f, 0.0f, 0.0f);

        auto mesh3 = ServiceLocator::GetResourceManager()->Load<Mesh>("meshes/BasicCube/DiffuseOnly/BasicCube.glb");
        entities[2]->AddComponent<MeshComponent>(std::move(mesh3));
        auto& transform3 = entities[2]->AddComponent<TransformComponent>();
        transform3.Scale *= 0.5f;
        transform3.Translation = glm::vec3(2.5f, 0.0f, 0.0f);

        auto mesh4 = ServiceLocator::GetResourceManager()->Load<Mesh>("meshes/BasicCone.glb");
        entities[3]->AddComponent<MeshComponent>(std::move(mesh4));
        auto& transform4 = entities[3]->AddComponent<TransformComponent>();
        transform4.Scale *= 0.5f;
        transform4.Translation = glm::vec3(0.0, 1.5f, 0.0f);
        glm::quat rotation = glm::quat(glm::vec3(M_PI / 2, 0, 0.0));
        transform4.Rotation = transform4.Rotation * rotation;
    }

protected:
    void Update(float deltaTime) override {

        auto& transform = entities[0]->GetComponent<TransformComponent>();

        glm::quat rotation = glm::quat(glm::vec3(0, ((M_PI * 2) / 3) * deltaTime, 0.0));
        transform.Rotation = transform.Rotation * rotation;

        auto& transform2 = entities[3]->GetComponent<TransformComponent>();

        glm::quat rotation2 = glm::quat(glm::vec3(0, 0, ((M_PI * 2) / 3) * deltaTime));
        transform2.Rotation = transform2.Rotation * rotation2;
    }

private:
    void handleClick(float value) {
        std::cout << "Clicked " << value << "\n";
    }

    InputManager* _inputManager { nullptr };

    std::vector<Entity*> entities {};
};

// Runtime
Game* OZZ::CreateGame() {
    return new YoutubeGame("Youtube Game");
}

