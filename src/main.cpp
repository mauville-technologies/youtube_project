#include <youtube_engine/platform/entry_point.h>
#include <youtube_engine/platform/game.h>

class YoutubeGame : public Game {
public:
    explicit YoutubeGame(std::string title) : Game(std::move(title)) {
        std::cout << "Hello, Youtube game!" << std::endl;
    }

protected:
    void Update(float deltaTime) override {
        //std::cout << "I'm updating!" << std::endl;
    }
};

// Runtime
Game* CreateGame() {
    return new YoutubeGame("Youtube Game");
}

