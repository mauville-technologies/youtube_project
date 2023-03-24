#include <youtube_engine/platform/entry_point.h>
#include <glm/glm.hpp>

#include <youtube_engine/core/entity.h>
#include <youtube_engine/core/components/mesh_component.h>
#include <youtube_engine/core/components/transform_component.h>
#include <numbers>

using namespace OZZ;

class YoutubeGame : public Game {
public:
    explicit YoutubeGame(std::string title) : Game(std::move(title)) {
        std::cout << "Hello, Youtube game!" << std::endl;


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
        transform.SetScale(glm::vec3{1.f} * 0.5f);
//
        auto mesh2 = ServiceLocator::GetResourceManager()->Load<Mesh>("meshes/BasicCone.glb");
        entities[1]->AddComponent<MeshComponent>(std::move(mesh2));
        auto& transform2 = entities[1]->AddComponent<TransformComponent>();
        transform2.SetPosition({-2.5f, 0.0f, 0.0f});
//
        auto mesh3 = ServiceLocator::GetResourceManager()->Load<Mesh>("meshes/BasicCube/DiffuseOnly/BasicCube.glb");
        entities[2]->AddComponent<MeshComponent>(std::move(mesh3));
        auto& transform3 = entities[2]->AddComponent<TransformComponent>();
        transform3.SetScale({0.5, 0.5, 0.5});
        transform3.SetPosition({2.5f, 0.0f, 0.0f});

        auto mesh4 = ServiceLocator::GetResourceManager()->Load<Mesh>("meshes/BasicCone.glb");
        entities[3]->AddComponent<MeshComponent>(std::move(mesh4));
        auto& transform4 = entities[3]->AddComponent<TransformComponent>();
        transform4.SetScale(glm::vec3{1.f} * 0.5f);
        transform4.SetPosition({0.0, 1.5f, 0.0f});
        glm::quat rotation = glm::quat(glm::vec3(std::numbers::pi / 2, 0, 0.0));
        transform4.RotateBy(0, 90.f, 0);

        camera = GetScene()->CreateEntity();
        auto& camTransform = camera->AddComponent<TransformComponent>();
        camTransform.SetPosition({0, 0, 5});

        auto& camComponent = camera->AddComponent<CameraComponent>();
        camComponent.SetActive(true);
        camComponent.FieldOfView = 75.f;
    }

protected:
    void Init() override {
        _inputManager = ServiceLocator::GetInputManager();

        if (_inputManager) {
            // Map inputs
            _inputManager->MapInputToAction(InputKey::KeyEscape, InputAction {
                    .ActionName = "quit",
                    .Scale = -1.f
            });

            _inputManager->MapInputToAction(InputKey::KeyF11, InputAction {
                    .ActionName = "toggleFullscreen",
                    .Scale = -1.f
            });

            _inputManager->MapInputToAction(InputKey::KeyA, InputAction {
                    .ActionName = "strafe",
                    .Scale = -1.f
            });

            _inputManager->MapInputToAction(InputKey::KeyD, InputAction {
                    .ActionName = "strafe",
                    .Scale = 1.f
            });
            _inputManager->MapInputToAction(InputKey::ControllerAxisLeftX, InputAction {
                    .ActionName = "strafe",
                    .Scale = 1.f
            });
            _inputManager->MapInputToAction(InputKey::ControllerAxisLeftY, InputAction {
                    .ActionName = "moveForward",
                    .Scale = -1.f
            });

            _inputManager->MapInputToAction(InputKey::KeyW, InputAction {
                    .ActionName = "moveForward",
                    .Scale = 1.f
            });

            _inputManager->MapInputToAction(InputKey::KeyS, InputAction {
                    .ActionName = "moveForward",
                    .Scale = -1.f
            });

            _inputManager->MapInputToAction(InputKey::KeyF10, InputAction {
                    .ActionName = "resetRenderer",
                    .Scale = 1.f
            });


            _inputManager->MapInputToAction(InputKey::ControllerAxisRightX, InputAction {
                    .ActionName = "lookX",
                    .Scale = -0.25f
            });

            _inputManager->RegisterActionCallback("resetRenderer", InputManager::ActionCallback {
                    .Ref = "YoutubeGame",
                    .Func = [this](InputSource source, int sourceIndex, float value) {
                        if (value != 0)
                            ResetRenderer();
                        return true;
                    }
            });

            _inputManager->RegisterActionCallback("quit", InputManager::ActionCallback {
                    .Ref = "YoutubeGame",
                    .Func = [this](InputSource source, int sourceIndex, float value) {
                        Quit();
                        return true;
                    }
            });

            _inputManager->RegisterActionCallback("toggleFullscreen", InputManager::ActionCallback {
                    .Ref = "YoutubeGame",
                    .Func = [this](InputSource source, int sourceIndex, float value) {
                        if (value == 0) return true;
                        auto* configuration = ServiceLocator::GetConfiguration();
                        auto& engineConfiguration = configuration->GetEngineConfiguration();

                        switch (engineConfiguration.WinDisplayMode) {
                            case WindowDisplayMode::Windowed:
                                std::cout << "Going borderless";
                                ServiceLocator::GetConfiguration()->SetEngineSetting(EngineSetting::WindowDisplayMode, WindowDisplayMode::BorderlessWindowed);
                                break;
                            case WindowDisplayMode::BorderlessWindowed:
                                std::cout << "Going full";

                                ServiceLocator::GetConfiguration()->SetEngineSetting(EngineSetting::WindowDisplayMode, WindowDisplayMode::Fullscreen);
                                break;
                            case WindowDisplayMode::Fullscreen:
                                std::cout << "Going windowed";

                                ServiceLocator::GetConfiguration()->SetEngineSetting(EngineSetting::WindowDisplayMode, WindowDisplayMode::Windowed);
                                break;
                        }
                        return true;
                    }
            });
        }

        SetupScene();
    }
    void Update(float deltaTime) override {

        auto& transform = entities[0]->GetComponent<TransformComponent>();
        transform.RotateBy((360.f / 3) * deltaTime, 0, 0.0);

        auto& transform2 = entities[3]->GetComponent<TransformComponent>();
        transform2.RotateBy((-360.f / 3) * deltaTime, 0, 0);

        auto& cameraTransform = camera->GetComponent<TransformComponent>();
        auto& cameraComponent = camera->GetComponent<CameraComponent>();

        auto moveForwardAmount = _inputManager->GetActionValue("moveForward");

        auto scaledSpeed = movementSpeed * deltaTime;
        if (std::abs(moveForwardAmount) > 0.05f) {
            cameraTransform.Translate(MoveDirection::Forward, moveForwardAmount * scaledSpeed);
        }

        auto strafeAmount = _inputManager->GetActionValue("strafe");
        if (std::abs(strafeAmount) > 0.05f) {
            cameraTransform.Translate(MoveDirection::Right, strafeAmount * scaledSpeed);
        }


        auto scaledLookSpeed = lookSpeed * deltaTime;

        auto lookXAmount = _inputManager->GetActionValue("lookX");
        if (std::abs(lookXAmount) > 0.05f && std::abs(lookXAmount) < 10.f) {
            cameraTransform.RotateBy(0.f, lookXAmount * scaledLookSpeed);
        }
//
//        auto lookYAmount = _inputManager->GetActionValue("lookY");
//        if (std::abs(lookYAmount) > 0.05f && std::abs(lookYAmount) < 10.f) {
//            cameraTransform.RotateBy(0.f, lookYAmount * scaledLookSpeed, 0, true);
//        }
    }

private:
    void handleClick(float value) {
        std::cout << "Clicked " << value << "\n";
    }

    InputManager* _inputManager { nullptr };

    std::vector<Entity*> entities {};
    Entity* camera { nullptr };
    float movementSpeed = 10.f;
    float lookSpeed = 180.f;
};

// Runtime
Game* OZZ::CreateGame() {
    return new YoutubeGame("Youtube Game");
}

