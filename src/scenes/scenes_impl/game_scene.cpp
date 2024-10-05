#include "game_scene.hpp"

#include <algorithm>
#include <chrono>
#include <random>
#include <string>

#include "../../game_object/game_objects_impl/button.hpp"
#include "../../game_object/game_objects_impl/doodle.hpp"
#include "../../input_manager.hpp"
#include "../../system.hpp"
#include "../../utils/calc.hpp"

GameScene::GameScene(InputManager* inputMan, const RectangleF& box)
    : Scene(inputMan),
      doodle_(box) {
    objs_.push_back(new Button(RectangleF(363, 9, 14, 19), consts::PAUSE_BTN_IMG));
    sm_.readFromFile();

    std::vector<GameObject*> newObjs = chooseSeq();
    objs_.insert(objs_.end(), newObjs.begin(), newObjs.end());
}

std::vector<GameObject*> GameScene::chooseSeq() {
    static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::shuffle(sm_.seqs.begin(), sm_.seqs.end(), gen);

    for (int i = 0; i < sm_.seqs.size(); i++) {
        int start = sm_.seqs[i].start, end = sm_.seqs[i].end;

        if ((height_ + consts::WIN_HEIGHT >= start) && (height_ < end || end == -1)) {
            currSeqTotalHeight_ = sm_.seqs[i].totalHeight;
            currSeqLastObjHeight_ = sm_.seqs[i].entities.back().y;
            return sm_.seqs[i].toObject();
        }
    }

    return std::vector<GameObject*>();
}

bool GameScene::update(Window* win, System* sys) {
    if (!doodle_.isDead() && currSeqHeight_ + win->get_height() >= currSeqLastObjHeight_) {
        std::vector<GameObject*> newObjs = chooseSeq();

        int delta = -(currSeqTotalHeight_ - currSeqLastObjHeight_ + win->get_height() - objs_.back()->getY());

        for (GameObject* obj : newObjs) {
            obj->translateY(delta);
        }

        currSeqHeight_ = delta;

        objs_.insert(objs_.end(), newObjs.begin(), newObjs.end());
    }

    removeObjectsBelow(win);

    if (inputMan_->didMouseRelease(InputMouse::Lrelease)) {
        if (collided(inputMan_->getMousePos(), objs_[0])) {
            sys->changeScene(System::SceneType::pause);
            return true;
        }
    }

    if (inputMan_->didKeyPress(InputKeys::pause)) {
        sys->changeScene(System::SceneType::pause);
        return true;
    }

    doodle_.updateInputs(inputMan_);
    doodle_.update(win);

    for (GameObject* obj : objs_) {
        obj->update(win);
    }

    checkCollisions(win);

    if (doodle_.isDead()) {
        sys->changeScene(System::SceneType::gameover);
        moveUp(consts::MS_PER_UPDATE);
        return true;
    }

    if (doodle_.getY() < win->get_height() / 2 - 10) {
        moveDown(win->get_height() / 2 - 10 - doodle_.getY());
    }

    return true;
}

void GameScene::removeObjectsBelow(const Window* win) {
    unsigned i;
    for (i = 1; i < objs_.size(); i++) {
        if (objs_[i]->getY() > win->get_height() + 10) {
            delete objs_[i];
        }
        else break;
    }
    objs_.erase(objs_.begin() + 1, objs_.begin() + i);
}

void GameScene::moveDown(int translateY) {
    for (unsigned i = 1; i < objs_.size(); i++) {
        objs_[i]->translateY(translateY);
    }

    doodle_.translateY(translateY);
    height_ += translateY;
    currSeqHeight_ += translateY;
}

void GameScene::moveUp(int translateY) {
    for (unsigned i = 1; i < objs_.size(); i++) {
        objs_[i]->translateY(-translateY);
    }
    doodle_.translateY(-translateY);
}

void GameScene::draw(Window* win) {
    win->draw_img(consts::BACKGROUND_COVER);

    for (unsigned i = 1; i < objs_.size(); i++) {
        objs_[i]->draw(win);
    }

    doodle_.draw(win);

    // HUD
    win->draw_img(consts::TOPBAR_IMG, Rectangle(0, 0, win->get_width(), 0.09 * win->get_height()));
    win->show_text(std::to_string(height_), Point(16, 0), BLACK, consts::FONT, 28);
    objs_[0]->draw(win); // pause button
}

void GameScene::checkCollisions(Window* win) {
    for (GameObject* obj : objs_) {
        if (collided(&doodle_, obj)) {
            doodle_.collide(obj, win);
        }
    }
}

int GameScene::getScoreHeight() const { return height_; }
