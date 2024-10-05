#define SDL_MAIN_HANDLED

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "RSDL/rsdl.hpp"
#include "assets/consts.hpp"
#include "system.hpp"

// clang++ -v -std=c++11 main.cpp -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -I/Library/Frameworks/SDL2_mixer.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers -F/Library/Frameworks -framework SDL2 -framework SDL2_mixer -framework SDL2_image -framework SDL2_ttf

// g++ -Wall -pedantic -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -I/Library/Frameworks/SDL2_mixer.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers -F/Library/Frameworks -framework SDL2 -framework SDL2_mixer -framework SDL2_image -framework SDL2_ttf build/obj/scenes/scenes_impl/gameover_scene.o build/obj/scenes/scene.o build/obj/scenes/scenes_impl/menu_scene.o build/obj/scenes/scenes_impl/pause_scene.o build/obj/scenes/scenes_impl/game_scene.o build/obj/game_object/game_objects_impl/platform_normal.o build/obj/game_object/game_objects_impl/platform_breakable.o build/obj/game_object/game_objects_impl/platform_movable.o build/obj/assets/spritesheet.o build/obj/game_object/game_objects_impl/button.o build/obj/sequence_manager.o build/obj/utils/calc.o build/obj/game_object/game_objects_impl/menu_ufo.o build/obj/game_object/game_object.o build/obj/system.o build/obj/game_object/game_objects_impl/spring.o build/obj/main.o build/obj/input_manager.o build/obj/RSDL/rsdl.o build/obj/game_object/game_objects_impl/enemy_normal.o build/obj/game_object/game_objects_impl/doodle.o -o build/bin/doodle_jump.exe -rpath /Library/Frameworks

void startGameLoop(Window* win) {
    System system(win);

    unsigned currTime = SDL_GetTicks();
    unsigned prevTime = currTime;
    unsigned lag = 0;
    bool canUpdate = true;

    while (canUpdate) {
        lag += currTime - prevTime;

        prevTime = currTime;

        while (canUpdate && lag >= consts::MS_PER_UPDATE) {
            lag -= consts::MS_PER_UPDATE;
            canUpdate = system.update();
        }

        win->clear();
        system.draw();
        win->update_screen();

        currTime = SDL_GetTicks();

        int delayTime = consts::MS_PER_UPDATE - (currTime - prevTime);

        if (delayTime < 0) delayTime = 0;

        currTime += delayTime;

        delay(delayTime);
    }
}

int main() {
    Window win(consts::WIN_WIDTH, consts::WIN_HEIGHT, consts::WIN_NAME);

    win.set_icon(consts::ICON);

    startGameLoop(&win);
}
