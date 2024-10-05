#include "menu_scene.hpp"

#include "../../RSDL/rsdl.hpp"
#include "../../game_object//game_objects_impl/button.hpp"
#include "../../game_object//game_objects_impl/menu_ufo.hpp"
#include "../../game_object/game_object.hpp"
#include "../../input_manager.hpp"
#include "../../system.hpp"
#include "../../utils/calc.hpp"

MenuScene::MenuScene(InputManager* inputMan)
    : Scene(inputMan) {
    objs_.push_back(new Button(RectangleF(58, 150, sprite::button[sprite::Button::PLAY].w, sprite::button[sprite::Button::PLAY].h), sprite::BUTTON_FILE, sprite::button[sprite::Button::PLAY]));
    objs_.push_back(new Button(RectangleF(245, 385, sprite::button[sprite::Button::QUIT].w, sprite::button[sprite::Button::QUIT].h), sprite::BUTTON_FILE, sprite::button[sprite::Button::QUIT]));
    objs_.push_back(new MenuUfo(RectangleF(260, 40, sprite::enemy[sprite::Enemy::UFO_OFF].w, sprite::enemy[sprite::Enemy::UFO_OFF].h)));
}

void MenuScene::draw(Window* win) {
    win->draw_img(consts::MENU_COVER);

    for (GameObject* obj : objs_) {
        obj->draw(win);
    }

    win->draw_img(sprite::DOODLE_FILE, Rectangle(50, doodleY_, sprite::doodle[sprite::Doodle::LEFT].w, sprite::doodle[sprite::Doodle::LEFT].h), sprite::doodle[sprite::Doodle::RIGHT]);
}

bool MenuScene::update(Window* win, System* sys) {
    doodleY_ -= doodleVY_ * consts::MS_PER_UPDATE;
    doodleVY_ -= consts::G * consts::MS_PER_UPDATE;
    if (doodleY_ > 400) doodleVY_ = consts::DOODLE_VY;

    for (GameObject* obj : objs_) {
        obj->update(win);
    }

    if (inputMan_->didMouseRelease(InputMouse::Lrelease)) {
        if (collided(inputMan_->getMousePos(), objs_[0])) { // play button
            sys->changeScene(System::SceneType::game);
            return true;
        }
        else if (collided(inputMan_->getMousePos(), objs_[1])) { // quit button
            return false;
        }
    }

    return true;
}
