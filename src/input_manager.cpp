#include "input_manager.hpp"

void InputManager::keyPressed(char key) {
    FILE* file = fopen("inputs.txt", "a+");
    fprintf(file, "%d\n", key);
    fclose(file);
    switch (key) {
    case consts::RIGHT_ARROW:
    case consts::RIGHT:
        keyInputs_ |= InputKeys::right;
        keyPresses_ |= InputKeys::right;
        break;
    case consts::LEFT_ARROW:
    case consts::LEFT:
        keyInputs_ |= InputKeys::left;
        keyPresses_ |= InputKeys::left;
        break;
    case consts::PAUSE:
        keyInputs_ |= InputKeys::pause;
        keyPresses_ |= InputKeys::pause;
        break;
    default: break;
    }
}

void InputManager::keyReleased(char key) {
    switch (key) {
    case consts::RIGHT_ARROW:
    case consts::RIGHT:
        keyInputs_ &= ~InputKeys::right;
        break;
    case consts::LEFT_ARROW:
    case consts::LEFT:
        keyInputs_ &= ~InputKeys::left;
        break;
    case consts::PAUSE:
        keyInputs_ &= ~InputKeys::pause;
        break;
    default: break;
    }
}

void InputManager::mousePressed(InputMouse::type state) {
    switch (state) {
    case InputMouse::Lclick:
        mouseInputs_ = InputMouse::Lclick;
        mousePresses_ = InputMouse::Lclick;
        break;
    case InputMouse::Lrelease:
        mouseInputs_ &= ~InputMouse::Lclick;
        mouseReleases_ = InputMouse::Lrelease;
        break;
    case InputMouse::Rclick:
        mouseInputs_ = InputMouse::Rclick;
        mousePresses_ = InputMouse::Rclick;
        break;
    case InputMouse::Rrelease:
        mouseInputs_ &= ~InputMouse::Rclick;
        mouseReleases_ = InputMouse::Rrelease;
        break;
    default: break;
    }
}

void InputManager::reset() {
    mouseReleases_ = 0;
    mousePresses_ = 0;
    keyPresses_ = 0;
    keyReleases_ = 0;
}

void InputManager::setMousePos(Point mousePos) { mousePos_ = mousePos; }

Point InputManager::getMousePos() const { return mousePos_; }

bool InputManager::isKeyPressed(InputKeys::type key) const {
    return (key & keyInputs_) != 0;
}

bool InputManager::didKeyPress(InputKeys::type key) const {
    return (key & keyPresses_) != 0;
}

bool InputManager::didKeyRelease(InputKeys::type key) const {
    return (key & keyReleases_) != 0;
}

bool InputManager::isMousePressed(InputMouse::type key) const {
    return (key & mouseInputs_) != 0;
}

bool InputManager::didMousePress(InputMouse::type key) const {
    return (key & mousePresses_) != 0;
}

bool InputManager::didMouseRelease(InputMouse::type key) const {
    return (key & mouseReleases_) != 0;
}
