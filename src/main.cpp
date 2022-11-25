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

        if (_triangleShader) {
            _triangleShader.reset();
            _triangleShader = nullptr;
        }

        if (_triangleUniformBuffer) {
            _triangleUniformBuffer.reset();
            _triangleUniformBuffer = nullptr;
        }

        if (_triangleTexture1) {
            _triangleTexture1.reset();
            _triangleTexture1 = nullptr;
        }
        if (_triangleTexture2) {
            _triangleTexture2.reset();
            _triangleTexture2 = nullptr;
        }

        _mesh.reset();
    }
    void SetupScene() {
        for (auto i : {1, 2, 3, 4, 5}) {
            entities.push_back(GetScene()->CreateEntity());
        }


        auto mesh = ServiceLocator::GetResourceManager()->Load<Mesh>("meshes/BasicCube/DiffuseOnly/BasicCube.glb");
        entities[0]->AddComponent<MeshComponent>(std::move(mesh));
        auto& transform = entities[0]->AddComponent<TransformComponent>();
//        transform._rotation = glm::rotate(transform._rotation, glm::vec3{0.f, 45.f, 0.0f});

    }

protected:
    void Update(float deltaTime) override {
        auto& transform = entities[0]->GetComponent<TransformComponent>();
        static float i = 0.01f;

        i += 0.01f;

        if (i > 360.f) i = 0.0f;
        glm::quat rotation = glm::quat(glm::vec3(0, 0.01, 0.0));
        transform._rotation = transform._rotation * rotation;
    }

private:
    void handleClick(float value) {
        std::cout << "Clicked " << value << "\n";
    }


    InputManager* _inputManager { nullptr };

    /*
     * NON-RENDERING Objects
     */

    std::shared_ptr<Mesh> _mesh;
    std::shared_ptr<Shader> _triangleShader { nullptr };
    std::shared_ptr<UniformBuffer> _triangleUniformBuffer { nullptr };

    std::shared_ptr<Texture> _triangleTexture1 { nullptr };
    std::shared_ptr<Texture> _triangleTexture2 { nullptr };

    std::vector<Entity*> entities {};
};

// Runtime
Game* OZZ::CreateGame() {
    return new YoutubeGame("Youtube Game");
}

