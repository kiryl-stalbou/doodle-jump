#ifndef SYSTEM_HPP_INCLUDE
#define SYSTEM_HPP_INCLUDE

#include <vector>

#include "input_manager.hpp"
#include "scenes/scene.hpp"
#include "scenes/scenes_impl/game_scene.hpp"
#include "scenes/scenes_impl/gameover_scene.hpp"
#include "scenes/scenes_impl/menu_scene.hpp"
#include "scenes/scenes_impl/pause_scene.hpp"

class System {
public:
    System(Window* win);

    enum class SceneType {
        menu,
        game,
        pause,
        gameover
    };

    bool update();
    void draw();
    void changeScene(SceneType to);

private:
    void initGameScene();

    int recordHeight_ = 0;

    SceneType currScene = SceneType::menu;

    Window* win_;
    InputManager inputManager_;

    std::vector<Scene*> scenes_;
    MenuScene menuScene_;
    PauseScene pauseScene_;
    GameScene* gameScene_ = nullptr;
    GameoverScene* gameoverScene_ = nullptr;
};

#endif // SYSTEM_HPP_INCLUDE
