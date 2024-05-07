//
// Created by lily young on 5/6/2024.
//

#include "S03033007.h"

#ifdef _WIN32

#include <windows.h>
#include <chrono>
#include <list>

using namespace S03033007;

void randomise_fruit_pos(GameState *gState) {
    gState->fruit_pos.y = rand() % (gState->height_tiles-1) + 1;
    gState->fruit_pos.x = rand() % (gState->width_tiles-1) + 1;
    for (auto snek:gState->snake_pos) {
        if(gState->fruit_pos.y == snek.y && gState->fruit_pos.x == snek.x) {
            // note: this will cause a stack overflow if someone manages to fill every tile of the board with snek... I'm not going to consider this a problem...
            randomise_fruit_pos(gState);
        }
    }
}

void reset_game(GameState *gState) {
    gState->snake_pos = {Pos{.x = 6, .y = 4},Pos{.x = 5, .y = 4}, Pos{.x = 4, .y = 4}};
    gState->current_direction = Direction::RIGHT;
    gState->game_tick_length = 250000000;
    gState->has_buffered_keypress = false;
    gState->next_keypress_buffers = false;
    randomise_fruit_pos(gState);
}

Pos grid_pos_to_px(GameState *gState, Pos pos) {
    Pos res = Pos{};
    res.x = (gState->tile_width * pos.x) + gState->grid_nudge.x;
    res.y = (gState->tile_height * pos.y) + gState->grid_nudge.y;
    return res;
}

void store_state(LPARAM lParam, HWND hwnd) {
    auto *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
    auto pState = reinterpret_cast<GameState *>(pCreate->lpCreateParams);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR) pState);
}

void draw_snake(GameState *gState, HDC hdc, PAINTSTRUCT ps) {
    SelectObject(hdc, gState->pen_snake);
    auto drawPos = grid_pos_to_px(gState, gState->snake_pos.front());
    MoveToEx(hdc, drawPos.x, drawPos.y, nullptr);

    for (auto pos: gState->snake_pos) {
        drawPos = grid_pos_to_px(gState, pos);
        LineTo(hdc, drawPos.x, drawPos.y);
    }
}

void draw_fruit(GameState *gState, HDC hdc, PAINTSTRUCT ps) {
    SelectObject(hdc, gState->pen_fruit);
    auto drawPos = grid_pos_to_px(gState, gState->fruit_pos);
    MoveToEx(hdc, drawPos.x, drawPos.y, nullptr);
    LineTo(hdc, drawPos.x, drawPos.y);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            cout << "setting up state";
            store_state(lParam, hwnd);
            return 0;
        case WM_SIZE: {
            LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
            auto *gState = reinterpret_cast<GameState *>(ptr);
            UINT width = LOWORD(lParam);
            UINT height = HIWORD(lParam);
            gState->width_px = width;
            gState->height_px = height;
            gState->tile_width = width / gState->width_tiles;
            gState->tile_height = height / gState->height_tiles;

            int tile_inner_size;
            if (gState->tile_height > gState->tile_width) {
                tile_inner_size = gState->tile_width - (gState->tile_width / 10);
            } else {
                tile_inner_size = gState->tile_height - (gState->tile_height / 10);
            }

            gState->pen_snake = CreatePen(PS_SOLID, tile_inner_size, RGB (255, 255, 255));
            gState->pen_fruit = CreatePen(PS_SOLID, tile_inner_size + 10, RGB (255, 0, 0));
            gState->pen_border = CreatePen(PS_SOLID, tile_inner_size, RGB (150, 150, 150));
            return 0;
        }
        case WM_KEYDOWN: {
            LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
            if (ptr == 0) {
                return 0;
            }
            auto *gState = reinterpret_cast<GameState *>(ptr);
            // keypress started
            Direction keypress;
            switch (wParam) {
                case VK_LEFT:
                    if (gState->current_direction != Direction::RIGHT)
                        keypress = Direction::LEFT;
                    break;
                case VK_RIGHT:
                    if (gState->current_direction != Direction::LEFT)
                        keypress = Direction::RIGHT;
                    break;
                case VK_UP:
                    if (gState->current_direction != Direction::DOWN)
                        keypress = Direction::UP;
                    break;
                case VK_DOWN:
                    if (gState->current_direction != Direction::UP)
                        keypress = Direction::DOWN;
                    break;
                case VK_SPACE:
                    reset_game(gState);
                    gState->next_tick = 0;
                    return 0;
                default:
                    return 0;
            }

            if(gState->has_buffered_keypress) {
                return 0;
            }

            if(gState->next_keypress_buffers) {
                gState->buffered_keypress = keypress;
                gState->has_buffered_keypress = true;
                return 0;
            }

            gState->next_keypress_buffers = true;
            gState->current_direction = keypress;

            return 0;
        }
        case WM_DESTROY: {
            LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
            auto *gState = reinterpret_cast<GameState *>(ptr);
            gState->exiting = true;
            PostQuitMessage(0);
            return 0;
        }
        case WM_PAINT:
        case WM_DISPLAYCHANGE: {

            LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
            auto *gState = reinterpret_cast<GameState *>(ptr);

            {
                LONGLONG now = (std::chrono::system_clock::now().time_since_epoch().count());
                if (gState->last_paint + 1000 > now) {
                    return 0;
                }
                gState->last_paint = now;
            }

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            SelectObject(hdc, gState->brush_background);
            SelectObject(hdc, gState->pen_border);
            Rectangle(hdc, 0, 0, gState->width_px, gState->height_px);

            draw_snake(gState, hdc, ps);
            draw_fruit(gState, hdc, ps);
            EndPaint(hwnd, &ps);
            return 0;
        }
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

S03033007::Snake::Snake() {

    gState = new GameState{};

    // Register the window class.
    const char *CLASS_NAME = "Snake Window";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandleA(nullptr);
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    window_handle = CreateWindowEx(
            0,                              // Optional window styles.
            CLASS_NAME,                     // Window class
            "Snake",    // Window text
            WS_OVERLAPPEDWINDOW,            // Window style

            // Size and position
            50, 50, 850, 850,

            nullptr,       // Parent window
            nullptr,       // Menu
            wc.hInstance,  // Instance handle
            gState        // Additional application data
    );

    if (window_handle == nullptr) {
        return;
    }

    {
        LONGLONG now = (std::chrono::system_clock::now().time_since_epoch().count());
        gState->next_tick = now + 1000;
        gState->last_paint = now;
    }

    {
        RECT rect;
        GetWindowRect(window_handle, &rect);
        gState->width_px = rect.right - rect.left;
        gState->height_px = rect.bottom - rect.top;
    }

    gState->tile_height = gState->height_px / gState->height_tiles;
    gState->tile_width = gState->width_px / gState->width_tiles;

    int tile_inner_size;
    if (gState->tile_height > gState->tile_width) {
        tile_inner_size = gState->tile_width - (gState->tile_width / 10);
    } else {
        tile_inner_size = gState->tile_height - (gState->tile_height / 10);
    }

    gState->pen_snake = CreatePen(PS_SOLID, tile_inner_size, RGB (255, 255, 255));
    gState->pen_fruit = CreatePen(PS_SOLID, tile_inner_size + 10, RGB (255, 0, 0));
    gState->pen_border = CreatePen(PS_SOLID, tile_inner_size, RGB (150, 150, 150));
    gState->brush_background = CreateSolidBrush(RGB(20, 20, 20));

}


void S03033007::Snake::start() {
    ShowWindow(window_handle, 10);

    reset_game(gState);

    cout << "created window";
    Sleep(1000);

    // Main message loop
    MSG msg = {};
    while (WM_QUIT != msg.message && WM_DESTROY != msg.message) {
        if (PeekMessage(&msg, window_handle, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            LONGLONG now = (std::chrono::system_clock::now().time_since_epoch().count());
            if (gState->next_tick < now) {
                if(gState->exiting) {
                    return;
                }
                do_gametic();
                InvalidateRect(window_handle, nullptr, FALSE);
                gState->next_tick = now + gState->game_tick_length;
                gState -> game_tick_length = gState->game_tick_length * 0.999;
            }
        }
    }

}

void Snake::do_gametic() {
    auto headPos = gState->snake_pos.front();
    Pos newPos = Pos{};
    switch (gState->current_direction) {
        case UP:
            newPos.x = headPos.x;
            newPos.y = headPos.y - 1;
            break;
        case DOWN:
            newPos.x = headPos.x;
            newPos.y = headPos.y + 1;
            break;
        case LEFT:
            newPos.x = headPos.x - 1;
            newPos.y = headPos.y;
            break;
        case RIGHT:
            newPos.x = headPos.x + 1;
            newPos.y = headPos.y;
            break;
    }

    if (newPos.x >= gState->width_tiles || newPos.y >= gState->height_tiles || newPos.x <= 0 || newPos.y <= 0) {
        if(!gState->gracePeriod) {
            gState->gracePeriod = true;
            return;
        }
        reset_game(gState);
        return;
    }

    for (auto snakeBody: gState->snake_pos) {
        if (newPos.x == snakeBody.x && newPos.y == snakeBody.y) {
            if(!gState->gracePeriod) {
                gState->gracePeriod = true;
                return;
            }
            reset_game(gState);
            return;
        }
    }

    gState->gracePeriod = false;
    gState->next_keypress_buffers = false;

    if(gState->has_buffered_keypress) {
        gState->current_direction = gState->buffered_keypress;
        gState->has_buffered_keypress = false;
    }

    gState->snake_pos.push_front(newPos);

    if (newPos.x == gState->fruit_pos.x && newPos.y == gState->fruit_pos.y) {
        randomise_fruit_pos(gState);
        return;
    }

    gState->snake_pos.pop_back();

}


#endif

