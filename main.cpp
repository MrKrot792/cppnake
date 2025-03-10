/*
 * I could've write it in c, but I have to learn C++, so...
 */
#include "utils.h"
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ncurses.h>
#include <thread>
#include <vector>

bool running = true;
bool gameOver = false;
int runtime = 0;
int score = 0;

Vec2 pos = Vec2();
Vec2 dir = Vec2(0, -1);
Vec2 applesPos = Vec2();

std::vector<Vec2> hist = {};

int main()
{
    srand(std::time(nullptr));

    // Some cool ncurses stuff
    initscr();
    start_color();
    clearok(stdscr, false);
    raw();
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    curs_set(0);

    hist.push_back(dir);

    applesPos.x = 4 + (rand() % ((COLS / 2) - 9));
    applesPos.y = 2 + (rand() % (LINES - 4));

    pos = Vec2(COLS / 4, LINES / 2);

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

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

            case 'g':
                gameOver = true;
                running = false;
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
        else
        {
            for (int i = 0; i < hist.size(); i++)
            {
                if (pos == hist.at(i))
                {
                    running = false;
                    gameOver = true;
                }
            }
        }

        if (pos.y >= LINES - 1 || pos.y <= 0 || pos.x >= (COLS) / 2 - 1 || pos.x <= 0)
        {
            running = false;
            gameOver = true;
        }

        // Body
        attron(COLOR_PAIR(2));
        for (int i = 0; i < hist.size(); i++)
        {
            drawAt(hist.at(i), '%');
        }

        // Head
        drawAt(pos, '@');
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(1));
        drawAt(applesPos, '$');
        attroff(COLOR_PAIR(1));

        // Score
        mvprintw(0, 0, "Score: %d", score * 100);
        mvprintw(LINES - 1, 0, "Apples pos: %d:%d", applesPos.x, applesPos.y);
        mvprintw(LINES - 2, 0, "Screen size: %d:%d", COLS, LINES);

        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    if (gameOver)
    {
        size_t s1 = std::strlen("GAME OVER"); // GAME OVER
        size_t s2 = snprintf(nullptr, 0, "Your score is: %d", score * 100);

        erase();
        mvprintw(LINES / 2, COLS / 2 - s1 / 2, "GAME OVER");
        mvprintw(LINES / 2 + 1, COLS / 2 - s2 / 2, "Your score is: %d", score * 100);
        refresh();

        nodelay(stdscr, false);

        int a = getch();
    }

    endwin();
    return 0;
}
