#include "scene.hpp"

#include "../game_object/game_object.hpp"

Scene::Scene(InputManager* inputMan) : inputMan_(inputMan) {}

Scene::~Scene() {
    for (GameObject* obj : objs_) delete obj;
}

bool Scene::update(Window* win, System* sys) {
    for (GameObject* obj : objs_) obj->update(win);

    return true;
}

void Scene::draw(Window* win) {
    for (GameObject* obj : objs_) obj->draw(win);
}
