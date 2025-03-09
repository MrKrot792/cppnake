/*
 * I could've write it in c, but I have to learn C++, so...
 */
#include <chrono>
#include <ncurses.h>
#include <thread>
#include <vector>

class Vec2
{
  public:
    int x, y;

    Vec2(int x = 0, int y = 0) : x(x), y(y)
    {
    }
};

bool running = true;
int runtime = 0;

Vec2 pos = Vec2();
Vec2 dir = Vec2(1, 0);

std::vector<Vec2> hist = {};

int main()
{
    initscr();
    clearok(stdscr, false);
    cbreak();
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    curs_set(0);

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

            case KEY_RIGHT:
                dir = Vec2(1, 0);
                break;

            case KEY_DOWN:
                dir = Vec2(0, 1);
                break;

            case KEY_LEFT:
                dir = Vec2(-1, 0);
                break;

            case 'q':
                running = false;
                break;

            case ' ':
                hist.push_back(dir);
                break;
            }
        }

        pos.x += dir.x * 2;
        pos.y += dir.y;

        for (int i = 0; i < hist.size(); i++)
        {
            Vec2 temp = Vec2();

            for (int j = 0; j < hist.size(); j++)
            {
                temp.x += hist.at(i).x;
                temp.y += hist.at(i).y;
            }

            mvaddch(temp.y + pos.y, temp.x + pos.x, '%');
            mvaddch(temp.y + pos.y, temp.x + pos.x + 1, '%');
        }

        mvaddch(pos.y, pos.x, '#');
        mvaddch(pos.y, pos.x + 1, '#');

        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    endwin();
    return 0;
}
