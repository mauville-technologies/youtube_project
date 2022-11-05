#include <youtube_engine/platform/entry_point.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <youtube_engine/core/entity.h>

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



                    for (auto* ent : entities) {
                        GetScene()->RemoveEntity(ent);
                    }
                    entities.clear();

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
        if (_triangleShader2) {
            _triangleShader2.reset();
            _triangleShader2 = nullptr;
        }

        if (_triangleBuffer) {
            _triangleBuffer.reset();
            _triangleBuffer = nullptr;
        }

        if (_triangleIndexBuffer) {
            _triangleIndexBuffer.reset();
            _triangleIndexBuffer = nullptr;
        }

        if (_triangle2Buffer) {
            _triangle2Buffer.reset();
            _triangle2Buffer = nullptr;
        }

        if (_triangle2IndexBuffer) {
            _triangle2IndexBuffer.reset();
            _triangle2IndexBuffer = nullptr;
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
    }
    void SetupScene() {
        ServiceLocator::GetResourceManager()->Load<Material>("materials/default_material.mat");

//        for (auto i : {1, 2, 3, 4, 5}) {
//            entities.push_back(GetScene()->CreateEntity());
//        }
//
//        auto renderer = ServiceLocator::GetRenderer();
//
//        _triangleTexture1 = renderer->CreateTexture();
//        _triangleTexture2 = renderer->CreateTexture();
//        _triangleTexture1->UploadData(ImageData("textures/bricks.png", true));
//        _triangleTexture2->UploadData(ImageData(50, 50, {1.f, 0.f, 0.f, 1.f}));
//
//        _triangleShader = renderer->CreateShader();
//        _triangleShader2 =  renderer->CreateShader();
//
//        _triangleShader->AddTexture(_triangleTexture2);
//        _triangleShader->AddTexture(_triangleTexture1);
//
//        _triangleShader2->AddTexture(_triangleTexture1);
//        _triangleShader2->AddTexture(_triangleTexture2);
//
//        _triangleShader->Load("basic.vert.spv", "basic.frag.spv");
//        _triangleShader2->Load("basic.vert.spv", "basic.frag.spv");
//
//        _triangleBuffer = renderer->CreateVertexBuffer();
//        _triangleBuffer->UploadData({
//                Vertex{
//                        .position = {0.75f, 0.75f, 0.f},
//                        .color = {1.f, 0.f, 0.f, 1.f},
//                        .uv = {1.f, 1.f}
//                },
//                Vertex{
//                        .position = {-0.75f, 0.75f, 0.f},
//                        .color = {0.f, 1.f, 0.f, 1.f},
//                        .uv = {0.f, 1.f}
//
//                },
//                Vertex{
//                        .position = {-0.75f, -0.75f, 0.f},
//                        .color = {0.f, 0.f, 1.f, 1.f},
//                        .uv = {0.f, 0.f}
//
//                },
//                Vertex{
//                        .position = {0.75f, -0.75f, 0.f},
//                        .color = {0.f, 0.f, 1.f, 1.f},
//                        .uv = {1.f, 0.f}
//                },
//        });
//
//        _triangleIndexBuffer = renderer->CreateIndexBuffer();
//        _triangleIndexBuffer->UploadData({0, 1, 2, 2, 3, 0});
//
//        _triangle2Buffer = renderer->CreateVertexBuffer();
//        _triangle2Buffer->UploadData({
//             Vertex{
//                     .position = {1.f, 1.f, 0.f},
//                     .color = {1.f, 1.f, 1.f, 1.f},
//                     .uv = {1.f, 0.f}
//             },
//             Vertex{
//                     .position = {-1.f, 1.f, 0.f},
//                     .color = {1.f, 1.f, 1.f, 1.f},
//                     .uv = { 0.f, 0.f}
//             },
//             Vertex{
//                     .position = {0.f, -1.f, 0.f},
//                     .color = {1.f, 1.f, 1.f, 1.f},
//                     .uv = {0.5, 1.f}
//             }
//        });
//
//        _triangle2IndexBuffer = renderer->CreateIndexBuffer();
//        _triangle2IndexBuffer->UploadData({0, 1, 2});
//
//        _triangleUniformBuffer = renderer->CreateUniformBuffer();
//
//        auto [width, height] = ServiceLocator::GetWindow()->GetWindowExtents();
//
//        UniformBufferObject uboObject{
//                glm::rotate(glm::mat4(1.0f), 1.f * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
//                glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
//                glm::perspective(glm::radians(45.0f), width / (float) height, 0.1f, 10.0f)
//        };
//
//        uboObject.proj[1][1] *= -1;
//
//        _triangleUniformBuffer->UploadData(uboObject);
//
//        _triangleShader->AddUniformBuffer(_triangleUniformBuffer);
//
//        auto buffer = renderer->CreateUniformBuffer();
//
//        auto translation = glm::translate(glm::mat4{1.f}, glm::vec3 {0.0, -1, -5});
//        UniformBufferObject uboObject2{
//                glm::rotate(translation, 1.f * glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
//                glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
//                glm::perspective(glm::radians(45.0f), width / (float) height, 0.1f, 999.0f)
//        };
//
//        uboObject2.proj[1][1] *= -1;
//
//        buffer->UploadData(uboObject2);
//        _triangleShader2->AddUniformBuffer(buffer);
    }

protected:
    void Update(float deltaTime) override {
//        auto [width, height] = ServiceLocator::GetWindow()->GetWindowExtents();
//
//        if (width == 0 || height == 0) return;
//
//        static auto startTime = std::chrono::high_resolution_clock::now();
//
//        auto currentTime = std::chrono::high_resolution_clock::now();
//        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
//
//        UniformBufferObject uboObject{
//                glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.5f, 1.0f)),
//                glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
//                glm::perspective(glm::radians(45.0f), (float)width / (float) height, 0.1f, 999.0f)
//        };
//
//        uboObject.proj[1][1] *= -1;
//
//        _triangleUniformBuffer->UploadData(uboObject);
    }

    void Render() override {
//        auto renderer = ServiceLocator::GetRenderer();
//        _triangleShader->Bind();
//
//        _triangle2Buffer->Bind();
//        _triangle2IndexBuffer->Bind();
//
//        renderer->DrawIndexBuffer(_triangle2IndexBuffer.get());
//        _triangleShader2->Bind();
//
//        _triangleBuffer->Bind();
//        _triangleIndexBuffer->Bind();
//        renderer->DrawIndexBuffer(_triangleIndexBuffer.get());
    }

private:
    void handleClick(float value) {
        std::cout << "Clicked " << value << "\n";
    }

    InputManager* _inputManager { nullptr };

    /*
     * NON-RENDERING Objects
     */
    std::shared_ptr<Shader> _triangleShader { nullptr };
    std::shared_ptr<Shader> _triangleShader2 { nullptr };

    std::shared_ptr<VertexBuffer> _triangleBuffer { nullptr };
    std::shared_ptr<IndexBuffer> _triangleIndexBuffer { nullptr };
    std::shared_ptr<UniformBuffer> _triangleUniformBuffer { nullptr };

    std::shared_ptr<VertexBuffer> _triangle2Buffer { nullptr };
    std::shared_ptr<IndexBuffer> _triangle2IndexBuffer { nullptr };
    std::shared_ptr<Texture> _triangleTexture1 { nullptr };
    std::shared_ptr<Texture> _triangleTexture2 { nullptr };

    std::vector<Entity*> entities {};
};

// Runtime
Game* OZZ::CreateGame() {
    return new YoutubeGame("Youtube Game");
}

