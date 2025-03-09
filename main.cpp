/*
 * I could've write it in c, but I have to learn C++, so...
 */
#include "utils.h"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <thread>
#include <vector>

bool running = true;
int runtime = 0;
int score = 0;

Vec2 pos = Vec2();
Vec2 dir = Vec2(1, 0);
Vec2 applesPos = Vec2();

std::vector<Vec2> hist = {};

int main()
{
    srand(std::time(nullptr));

    // Some cool ncurses stuff
    initscr();
    clearok(stdscr, false);
    raw();
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    curs_set(0);

    hist.push_back(dir);

    applesPos.x = 4 + (rand() % ((COLS / 2) - 9));
    applesPos.y = 2 + (rand() % (LINES - 4));

    while (running)
    {
        erase();
        runtime++;

        int ch = getch();

        if (ch != ERR)
        {
            switch (ch)
            {
            case KEY_UP:
                dir = Vec2(0, -1);
                break;

            case 'w':
                dir = Vec2(0, -1);
                break;

            case 'k':
                dir = Vec2(0, -1);
                break;

            case KEY_RIGHT:
                dir = Vec2(1, 0);
                break;

            case 'd':
                dir = Vec2(1, 0);
                break;

            case 'l':
                dir = Vec2(1, 0);
                break;

            case KEY_DOWN:
                dir = Vec2(0, 1);
                break;

            case 's':
                dir = Vec2(0, 1);
                break;

            case 'j':
                dir = Vec2(0, 1);
                break;

            case KEY_LEFT:
                dir = Vec2(-1, 0);
                break;

            case 'a':
                dir = Vec2(-1, 0);
                break;

            case 'h':
                dir = Vec2(-1, 0);
                break;

            case 'q':
                running = false;
                break;

            case ' ':
                hist.push_back(pos);
                break;
            }
        }

        for (int i = hist.size() - 1; i > 0; i--)
        {
            hist.at(i) = hist.at(i - 1);
        }

        hist.at(0) = pos;

        pos = pos + dir;

        if (pos == applesPos)
        {
            applesPos.x = 4 + (rand() % ((COLS / 2) - 9));
            applesPos.y = 2 + (rand() % (LINES - 4));

            hist.push_back(pos);

            score += 1;
        }

        // Body
        for (int i = 0; i < hist.size(); i++)
        {
            drawAt(hist.at(i), '%');
        }

        // Head
        drawAt(pos, '@');

        drawAt(applesPos, '$');

        // Score
        mvprintw(0, 0, "Score: %d", score * 100);
        mvprintw(LINES - 1, 0, "Apples pos: %d:%d", applesPos.x, applesPos.y);
        mvprintw(LINES - 2, 0, "Screen size: %d:%d", COLS, LINES);

        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    endwin();
    return 0;
}
