#include "system.hpp"

#include "assets/spritesheet.hpp"
#include "game_object/game_objects_impl//enemy_normal.hpp"
#include "game_object/game_objects_impl//platform_breakable.hpp"
#include "game_object/game_objects_impl//platform_movable.hpp"
#include "game_object/game_objects_impl//platform_normal.hpp"
#include "game_object/game_objects_impl//spring.hpp"

System::System(Window* win_) : win_(win_), menuScene_(&inputManager_), pauseScene_(&inputManager_) {
    FILE* file = fopen("record.txt", "r");

    char buffer[256];

    fgets(buffer, sizeof(buffer), file);

    recordHeight_ = atoi(buffer);

    fclose(file);

    scenes_.push_back(&menuScene_);
}

bool System::update() {
    inputManager_.reset();

    while (win_->has_pending_event()) {
        Event event = win_->poll_for_event();

        switch (event.get_type()) {
        case Event::EventType::QUIT: return false;

        case Event::EventType::KEY_PRESS:
            inputManager_.keyPressed(event.get_pressed_key());
            break;

        case Event::EventType::KEY_RELEASE:
            inputManager_.keyReleased(event.get_pressed_key());
            break;

        case Event::EventType::MMOTION:
            inputManager_.setMousePos(event.get_mouse_position());
            break;

        case Event::EventType::LCLICK:
            inputManager_.mousePressed(InputMouse::Lclick);
            break;

        case Event::EventType::LRELEASE:
            inputManager_.mousePressed(InputMouse::Lrelease);
            break;

        default: break;
        }
    }

    if (currScene == SceneType::gameover) scenes_[1]->update(win_, this);

    return scenes_.back()->update(win_, this);
}

void System::draw() {
    if (currScene == SceneType::pause || currScene == SceneType::gameover) {
        scenes_[1]->draw(win_);
    }

    scenes_.back()->draw(win_);
}

void System::changeScene(SceneType newScene) {
    switch (currScene) {
    case SceneType::menu:
        if (newScene == SceneType::game) {
            currScene = SceneType::game;
            initGameScene();
            scenes_.push_back(gameScene_);
        }
        break;

    case SceneType::game:
        if (newScene == SceneType::pause) {
            currScene = SceneType::pause;
            scenes_.push_back(&pauseScene_);
        }
        else if (newScene == SceneType::gameover) {
            currScene = SceneType::gameover;

            int height = gameScene_->getScoreHeight();
            if (height > recordHeight_) {
                recordHeight_ = height;
                FILE* recordFile = fopen("record.txt", "w");
                fprintf(recordFile, "%d", recordHeight_);
                fclose(recordFile);
            }

            gameoverScene_ = new GameoverScene(&inputManager_, height, recordHeight_);
            scenes_.push_back(gameoverScene_);
        }
        break;

    case SceneType::pause:
        if (newScene == SceneType::game) {
            currScene = SceneType::game;
            scenes_.pop_back();
        }
        break;

    case SceneType::gameover:
        if (newScene == SceneType::game) {
            currScene = SceneType::game;
            delete scenes_.back();
            scenes_.pop_back();
            delete scenes_.back();
            scenes_.pop_back();
            initGameScene();
            scenes_.push_back(gameScene_);
        }
        else if (newScene == SceneType::menu) {
            currScene = SceneType::menu;
            delete scenes_.back();
            scenes_.pop_back();
            delete scenes_.back();
            scenes_.pop_back();
        }
        break;
    }
}

void System::initGameScene() {
    int doodleWidth = sprite::doodle[sprite::Doodle::LEFT].w;
    int doodleHeight = sprite::doodle[sprite::Doodle::LEFT].h;
    gameScene_ = new GameScene(&inputManager_, RectangleF(win_->get_width() / 2 - doodleWidth / 2, win_->get_height() - doodleHeight, doodleWidth, doodleHeight));
}
