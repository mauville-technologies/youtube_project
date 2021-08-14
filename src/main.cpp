#include <youtube_engine/platform/entry_point.h>
#include <youtube_engine/platform/game.h>

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
                .Func = [](InputSource source, int sourceIndex, float value) {
                    std::string direction {"NONE"};

                    if (value > 0.f) direction = "RIGHT";
                    if (value < 0.f) direction = "LEFT";
                    std::cout << "STRAFING " << direction << "\n";
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

        }
    }

protected:
    void Update(float deltaTime) override {
        //std::cout << "I'm updating!" << std::endl;
    }

private:
    void handleClick(float value) {
        std::cout << "Clicked " << value << "\n";
    }

    InputManager* _inputManager { nullptr };
};

// Runtime
Game* OZZ::CreateGame() {
    return new YoutubeGame("Youtube Game");
}

