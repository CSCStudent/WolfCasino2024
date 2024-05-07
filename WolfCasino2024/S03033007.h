//
// Created by lily young on 5/6/2024.
//

#ifndef WOLFCASINO2024_S03033007_H
#define WOLFCASINO2024_S03033007_H

#include <iostream>

#ifndef _WIN32 // ensures the platform is windows
namespace S03033007 {
    class Snake {
    public:
        //Constructor
        Snake();

        static Snake* makeGame() {

        };

        //This plays the game
        void start() {
            std::cout << "Snake is not supported on your platform, snake is only supported on windows platforms" << std::endl;
        }
    };
}

#else

#include <windows.h>
#include "Casino.h"
#include <list>

namespace S03033007 {

    enum Direction {
        UP = 0,
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3,
    };

    class Pos {
    public:
        int x;
        int y;
    };

    struct GameState {
        bool gracePeriod = false;
        bool exiting = false;
        int game_tick_length;
        Pos fruit_pos = Pos{};
        list<Pos> snake_pos = {};

        Direction current_direction = Direction::RIGHT;
        bool has_buffered_keypress = false;
        bool next_keypress_buffers = false;
        Direction buffered_keypress;

        LONGLONG next_tick = 0;
        LONGLONG last_paint = 0;
        Pos grid_nudge;
        int height_px;
        int width_px;
        int height_tiles = 16;
        int width_tiles = 16;

        int tile_height;
        int tile_width;

        HPEN pen_snake;
        HPEN pen_fruit;
        HPEN pen_border;
        HBRUSH brush_background;
    };

    class Snake : public CSC2034::Casino {
    public:
        /**
         * constructs the game
         */
        Snake();

        /**
         * creates a new pointer to a new instance of the game
         */
        static Snake *makeGame() {
            return new Snake();
        }

        /**
         * starts the game
         */
        void start() override;

    private:
        GameState *gState;
        HWND window_handle;
        void do_gametic();
    };

}

#endif // _WIN32
#endif //WOLFCASINO2024_S03033007_H