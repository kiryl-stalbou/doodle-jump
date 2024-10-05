#ifndef MENU_SCENE_HPP_INCLUDE
#define MENU_SCENE_HPP_INCLUDE

#include "../../assets/consts.hpp"
#include "../scene.hpp"

class InputManager;

class MenuScene : public Scene {
public:
    MenuScene(InputManager* inputMan);

    bool update(Window* win, System* sys) override;
    void draw(Window* win) override;

private:
    float doodleY_ = 400;
    float doodleVY_ = consts::DOODLE_VY;
};

#endif // MENU_SCENE_HPP_INCLUDE
