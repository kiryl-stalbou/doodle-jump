#ifndef BUTTON_HPP_INCLUDE
#define BUTTON_HPP_INCLUDE

#include <string>

#include "../../assets/spritesheet.hpp"
#include "../game_object.hpp"

class Window;

class Button : public GameObject {
public:
    Button(const RectangleF& box, const RectangleF& hitBox, const std::string& img, const Rectangle& spriteCut);
    Button(const RectangleF& box, const std::string& img, const Rectangle& spriteCut);
    Button(const RectangleF& box, const RectangleF& hitBox, const std::string& img);
    Button(const RectangleF& box, const std::string& img);

    void update(Window* win) override;
    void draw(Window* win, const PointF& offset = {0, 0}) const override;
    CollisionType collide(GameObject* col, Window* win) override;

private:
    static CollisionType collideType_;

    std::string img_;
    bool spriteIsCut_;
    sprite::Tile spriteCut_;
};

#endif // BUTTON_HPP_INCLUDE
